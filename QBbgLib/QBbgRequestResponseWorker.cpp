#include "QBbgRequestResponseWorker.h"
#include "QBbgRequestResponseWorker_p.h"
#include "QBbgReferenceDataResponse.h"
namespace QBbgLib {
    QBbgRequestResponseWorkerPrivate::QBbgRequestResponseWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& options)
        :QBbgAbstractWorkerPrivate(q, options)
    {}
    QBbgRequestResponseWorkerPrivate::~QBbgRequestResponseWorkerPrivate()
    {
        for (QHash<qint64, QList<qint64>* >::iterator i = Groups.begin(); i != Groups.end(); ++i)
            delete i.value();
        Groups.clear();
        for (QHash<qint64, QBbgAbstractResponse* >::iterator i = m_Results.begin(); i != m_Results.end(); ++i)
            delete i.value();
        m_Results.clear();
    }
    qint64 QBbgRequestResponseWorkerPrivate::CorrelationForService(const QString& a) const
    {
        return -static_cast<qint64>(QBbgAbstractRequest::stringToServiceType(a));
    }
    void QBbgRequestResponseWorkerPrivate::handleResponseEvent(const BloombergLP::blpapi::Event& event)
    {

    }

    bool QBbgRequestResponseWorkerPrivate::processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession)
    {
        switch (event.eventType()) {
        case BloombergLP::blpapi::Event::SESSION_STATUS: {
            BloombergLP::blpapi::MessageIterator iter(event);
            while (iter.next()) {
                BloombergLP::blpapi::Message message = iter.message();
                QString MessageType = message.messageType().string();
                if (MessageType == "SessionStarted") {
                    QList<QString> servicesToOpen = m_Requests.differentServices();
                    for (QList<QString>::const_iterator rqIter = servicesToOpen.constBegin(); rqIter != servicesToOpen.constEnd(); ++rqIter) {
                        CurrentSession->openServiceAsync(rqIter->toLatin1().data(), BloombergLP::blpapi::CorrelationId(CorrelationForService(*rqIter)));
                    }
                    //q->Started(); // Emit signal
                }
                else if (MessageType == "SessionConnectionUp") continue;
                else if (MessageType == "SessionConnectionDown") continue;
                else if (MessageType == "SessionTerminated") {
                    //EndOfProcess();
                }
                else /*if (MessageType == "SessionStartupFailure")*/ {
                    const QList<qint64> allRq = m_Requests.IDList();
                    for (QList<qint64>::const_iterator i = allRq.constBegin(); i != allRq.constEnd(); ++i)
                        SetError(*i, QBbgAbstractResponse::SessionError);
                }
            }
            break;
        }
        case BloombergLP::blpapi::Event::SERVICE_STATUS: {
            BloombergLP::blpapi::MessageIterator iter(event);
            while (iter.next()) {
                BloombergLP::blpapi::Message message = iter.message();
                QBbgAbstractRequest::ServiceType currentService = static_cast<QBbgAbstractRequest::ServiceType>(-message.correlationId().asInteger());
                if (QString(message.messageType().string()) == "ServiceOpened") {
                    SendRequ(currentService);
                }
                else {
                    const QList<qint64> allRq = m_Requests.IDList();
                    for (QList<qint64>::const_iterator i = allRq.constBegin(); i != allRq.constEnd(); ++i) {
                        if (QBbgAbstractRequest::serviceForRequest(m_Requests.request(*i)->requestType()) == currentService)
                            SetError(*i, QBbgAbstractResponse::ServiceError);
                    }
                }
            }
            break;
        }
        case BloombergLP::blpapi::Event::PARTIAL_RESPONSE:
        case BloombergLP::blpapi::Event::RESPONSE:
            handleResponseEvent(event);
            break;
        default:{
            const QList<qint64> allRq = m_Requests.IDList();
            for (QList<qint64>::const_iterator i = allRq.constBegin(); i != allRq.constEnd(); ++i)
                SetError(*i, QBbgAbstractResponse::UnknownError);
        }
        }
        return true;
    }

    bool QBbgRequestResponseWorkerPrivate::SetError(qint64 RequestID, QBbgAbstractResponse::BbgErrorCodes Err)
    {
        if (m_Results.contains(RequestID)) return false;
        QBbgAbstractResponse* TempRes=NULL;
        switch (m_Requests.request(RequestID)->requestType()) {
        case QBbgAbstractRequest::ReferenceData:
            TempRes = new QBbgReferenceDataResponse();
            break;
        default:
            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::SetError", "Unhandled request type");
            break;
        }
        setResponseID(TempRes, RequestID);
        setResponseError(TempRes, Err);
        m_Results.insert(RequestID, TempRes);
        return DataRecieved(RequestID);
    }
    bool QBbgRequestResponseWorkerPrivate::DataPointRecieved(qint64 RequestID, const QVariant& Value, const QString& Header)
    {
        if (m_Results.contains(RequestID)) return false;
        QBbgAbstractResponse* resToAdd = NULL;
        switch (m_Requests.request(RequestID)->requestType()) {
        case QBbgAbstractRequest::ReferenceData:{
            QBbgReferenceDataResponse *TempRes = new QBbgReferenceDataResponse();
            TempRes->setValue(Value, Header);
            resToAdd = TempRes;
            break;
        }
        case QBbgAbstractRequest::PortfolioData:
            //TODO
        default:
            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::DataPointRecieved", "Only ReferenceData and PortfolioData can recieve Data Ponts");
            break;
        }
        setResponseID(resToAdd, RequestID);
        m_Results.insert(RequestID, resToAdd);
        return DataRecieved(RequestID);
    }
    bool QBbgRequestResponseWorkerPrivate::HeaderRecieved(qint64 RequestID, const QString& Header)
    {
        if (!m_Results.contains(RequestID)) return false;
        QBbgAbstractFieldResponse* res = dynamic_cast<QBbgAbstractFieldResponse*>(m_Results[RequestID]);
        Q_ASSERT_X(res, "QBbgRequestResponseWorkerPrivate::HeaderRecieved", "Setting header for non-fielded data");
        res->setHeader(Header);
    }
    bool QBbgRequestResponseWorkerPrivate::DataRecieved(qint64 RequestID)
    {
        //q->Recieved(RequestID);
        //q->Progress((100 * m_Results.size()) / m_Requests.size());
        if (m_Results.size() == m_Requests.size()) {
                //q->Finished();
                m_session->stopAsync();
            return true;
        }
        return false;
    }
    void QBbgRequestResponseWorkerPrivate::DataRowRecieved(qint64 RequestID, const QList<QVariant>& Value, const QList<QString>& Header)
    {
        QHash<qint64, QBbgAbstractResponse* >::iterator TempIter = m_Results.find(RequestID);
        Q_ASSERT_X(TempIter == m_Results.end() || (TempIter != m_Results.end() && TempIter.value()->responseType() == m_Requests.request(RequestID)->requestType()), "QBbgRequestResponseWorkerPrivate::DataRowRecieved", "Adding Row to response of different type");
        switch (m_Requests.request(RequestID)->requestType()) {
        case QBbgAbstractRequest::ReferenceData:{
            if (TempIter == m_Results.end()) {
                TempIter = m_Results.insert(RequestID, new QBbgReferenceDataResponse());
            }
            dynamic_cast<QBbgReferenceDataResponse*>(TempIter.value())->addValueRow(Value, Header);
            break;
        }
        case QBbgAbstractRequest::PortfolioData:
            //TODO
        default:
            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::DataRowRecieved", "Only ReferenceData and PortfolioData can recieve Data Rows");
            break;
        }
    }
}