#include "QBbgRequestResponseWorker.h"
#include "QBbgRequestResponseWorker_p.h"
#include "QBbgReferenceDataResponse.h"
#include <QSet>
#include "QBbgRequestGroup.h"
#include "QBbgAbstractFieldRequest.h"
#include "QBbgOverride.h"
#include "QbbgReferenceDataRequest.h"
namespace QBbgLib {
    QBbgRequestResponseWorkerPrivate::QBbgRequestResponseWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& options)
        :QBbgAbstractWorkerPrivate(q, options)
    {}
    QBbgRequestResponseWorkerPrivate::~QBbgRequestResponseWorkerPrivate()
    {
        for (QHash<qint64, QList<qint64>* >::iterator i = Groups.begin(); i != Groups.end(); ++i)
            delete i.value();
    }
    qint64 QBbgRequestResponseWorkerPrivate::CorrelationForService(const QString& a) const
    {
        return -static_cast<qint64>(QBbgAbstractRequest::stringToServiceType(a));
    }
    void QBbgRequestResponseWorkerPrivate::handleResponseEvent(const BloombergLP::blpapi::Event& event)
    {
        BloombergLP::blpapi::MessageIterator iter(event);
        while (iter.next()) {
            BloombergLP::blpapi::Message message = iter.message();
            const QList<qint64>* CurrentGroup = Groups.value(message.correlationId().asInteger(), nullptr);
            Q_ASSERT_X(CurrentGroup, "QBbgRequestResponseWorkerPrivate::handleResponseEvent", "Recieving response from unknown request");
            if (message.hasElement("responseError")) {
                for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                    SetError(*SingleReq, QBbgAbstractResponse::ResponseError);
                }
                return;
            }
            switch (QBbgAbstractResponse::stringToResponseType(message.messageType().string())) {
            case QBbgAbstractResponse::ReferenceDataResponse:
            {
                BloombergLP::blpapi::Element secDataArray = message.getElement("securityData"); //securityData[]
                for (size_t secIter = 0; secIter < secDataArray.numValues(); ++secIter) {
                    QString CurrentSecurity = secDataArray.getValueAsElement(secIter).getElementAsString("security");
                    BloombergLP::blpapi::Element fieldExcepArray = secDataArray.getValueAsElement(secIter).getElement("fieldExceptions"); //fieldExceptions[]
                    for (size_t fieldExcIter = 0; fieldExcIter < fieldExcepArray.numValues(); ++fieldExcIter) {
                        QString CurrentField = fieldExcepArray.getValueAsElement(fieldExcIter).getElementAsString("fieldId");
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractFieldRequest* const FoundRequ = dynamic_cast<const QBbgAbstractFieldRequest*>(m_Requests.request(*SingleReq));
                            Q_ASSERT(FoundRequ);
                            if (FoundRequ->security().fullName() == CurrentSecurity && FoundRequ->field() == CurrentField) {
                                SetError(*SingleReq, QBbgAbstractResponse::FieldError);
                            }
                        }
                    }
                    if (secDataArray.getValueAsElement(secIter).hasElement("securityError")) {
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractRequest* const FoundRequ = m_Requests.request(*SingleReq);
                            if (FoundRequ->security().fullName() == CurrentSecurity) {
                                SetError(*SingleReq, QBbgAbstractResponse::SecurityError);
                            }
                        }
                    }
                    else {
                        BloombergLP::blpapi::Element fieldDataArray = secDataArray.getValueAsElement(secIter).getElement("fieldData"); //fieldData[]
                        if (fieldDataArray.numElements() == 0) {
                            for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                                const QBbgAbstractRequest* const FoundRequ = m_Requests.request(*SingleReq);
                                if (FoundRequ->security().fullName() == CurrentSecurity) {
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData);
                                }
                            }
                        }
                        else {
                            for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                                const QBbgAbstractFieldRequest* const FoundRequ = dynamic_cast<const QBbgAbstractFieldRequest*>(m_Requests.request(*SingleReq));
                                Q_ASSERT(FoundRequ);
                                if (!fieldDataArray.hasElement(FoundRequ->field().toLatin1().data())) {
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData);
                                }
                                else {
                                    BloombergLP::blpapi::Element fieldDataValue = fieldDataArray.getElement(FoundRequ->field().toLatin1().data());
                                    if (fieldDataValue.isArray()) {
                                        if (fieldDataValue.numValues() == 0) {
                                            SetError(*SingleReq, QBbgAbstractResponse::NoData);
                                        }
                                        else {
                                            size_t NumCols = fieldDataValue.getValueAsElement(0).numElements();
                                            if (NumCols == 0) {
                                                SetError(*SingleReq, QBbgAbstractResponse::NoData);
                                            }
                                            else {
                                                QList<QVariant> CurrentRow;
                                                QList<QString> CurrentHead;
                                                for (size_t RowIter = 0; RowIter < fieldDataValue.numValues(); ++RowIter) {
                                                    CurrentRow.clear();
                                                    CurrentHead.clear();
                                                    for (size_t ColIter = 0; ColIter < NumCols; ++ColIter) {
                                                        CurrentRow.append(elementToVariant(fieldDataValue.getValueAsElement(RowIter).getElement(ColIter)));
                                                        CurrentHead.append(fieldDataValue.getValueAsElement(RowIter).getElement(ColIter).name().string());
                                                    }
                                                    DataRowRecieved(*SingleReq, CurrentRow, CurrentHead);
                                                }
                                                HeaderRecieved(*SingleReq, FoundRequ->field());
                                                DataRecieved(*SingleReq);
                                            }
                                        }
                                    }
                                    else{
                                        DataPointRecieved(*SingleReq, elementToVariant(fieldDataValue), FoundRequ->field());
                                    }
                                }
                            }
                        }

                    }
                }
            }
                break;
            default:
                Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::handleResponseEvent", "Unhandled Response Type");
            }
        }

    }

    bool QBbgRequestResponseWorkerPrivate::processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession)
    {
        Q_Q(QBbgRequestResponseWorker);
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
                    q->started(); // Emit signal
                }
                else if (MessageType == "SessionConnectionUp") continue;
                else if (MessageType == "SessionConnectionDown") continue;
                else if (MessageType == "SessionTerminated") {
                    m_SessionRunning = false;
                    q->finished();
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

    void QBbgRequestResponseWorkerPrivate::SetError(qint64 RequestID, QBbgAbstractResponse::BbgErrorCodes Err)
    {
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
        DataRecieved(RequestID);
    }
    void QBbgRequestResponseWorkerPrivate::DataPointRecieved(qint64 RequestID, const QVariant& Value, const QString& Header)
    {
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
        DataRecieved(RequestID);
    }
    void QBbgRequestResponseWorkerPrivate::HeaderRecieved(qint64 RequestID, const QString& Header)
    {
        if (!m_Results.contains(RequestID)) return;
        QBbgAbstractFieldResponse* res = dynamic_cast<QBbgAbstractFieldResponse*>(m_Results[RequestID]);
        Q_ASSERT_X(res, "QBbgRequestResponseWorkerPrivate::HeaderRecieved", "Setting header for non-fielded data");
        res->setHeader(Header);
    }
    void QBbgRequestResponseWorkerPrivate::DataRecieved(qint64 RequestID)
    {
        Q_Q(QBbgRequestResponseWorker);
        QHash<qint64, QBbgAbstractResponse*>::iterator i = m_Results.find(RequestID);
        Q_ASSERT(i != m_Results.end());
        q->dataRecieved(RequestID, i.value());
        m_Results.erase(i);        
        q->progress((100 * ++m_ResurnedResults) / m_Requests.size());
        if (m_ResurnedResults == m_Requests.size()) {
                m_session->stopAsync();
        }
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
    void QBbgRequestResponseWorkerPrivate::SendRequ(QBbgAbstractRequest::ServiceType serv)
    {
        QSet<QString> UsedSecur;
        QSet<QString> UsedFields;
        BloombergLP::blpapi::Service refDataSvc = m_session->getService(QBbgAbstractRequest::serviceTypeToString(serv).toLatin1().data());
        for (QHash<qint64, QList<qint64>* >::const_iterator ReqIter = Groups.constBegin(); ReqIter != Groups.constEnd(); ++ReqIter) {
            QBbgAbstractRequest::RequestType reqType = m_Requests.request(ReqIter.value()->first())->requestType();
            if (QBbgAbstractRequest::serviceForRequest(reqType) != serv) continue;
            BloombergLP::blpapi::CorrelationId requestId(ReqIter.key());
            BloombergLP::blpapi::Request request = refDataSvc.createRequest(QBbgAbstractRequest::requestTypeToString(reqType).toLatin1().data());
            UsedSecur.clear();
            UsedFields.clear();
            for (QList<qint64>::const_iterator GroupIter = ReqIter.value()->constBegin(); GroupIter != ReqIter.value()->constEnd(); ++GroupIter) {
                const QBbgAbstractRequest* CurrentSingle = m_Requests.request(*GroupIter);
                Q_ASSERT_X(CurrentSingle, "QBbgRequestResponseWorkerPrivate::SendRequ", "trying to send NULL request");
                if (!CurrentSingle->isValidReq()) {
                    SetError(*GroupIter, QBbgAbstractResponse::InvalidInputs);
                }
                if (!UsedSecur.contains(CurrentSingle->security().fullName())) {
                    request.append("securities", CurrentSingle->security().fullName().toLatin1().data());
                    UsedSecur.insert(CurrentSingle->security().fullName());
                }
                if (reqType & QBbgAbstractRequest::FirstFielded) {
                    const QBbgAbstractFieldRequest* CurrentSingleFielded = dynamic_cast<const QBbgAbstractFieldRequest*>(CurrentSingle);
                    Q_ASSERT(CurrentSingleFielded);
                    if (!UsedFields.contains(CurrentSingle->security().fullName())) {
                        request.append("fields", CurrentSingleFielded->field().toLatin1().data());
                        UsedFields.insert(CurrentSingleFielded->field());
                    }
                    if (GroupIter == ReqIter.value()->constBegin()) {
                        CurrentSingleFielded->overrides().addOverrideToRequest(request);
                    }
                    if (reqType == QBbgAbstractRequest::ReferenceData) {
                        const QBbgReferenceDataRequest* CurrentSingleRefData = dynamic_cast<const QBbgReferenceDataRequest*>(CurrentSingle);
                        Q_ASSERT(CurrentSingleRefData);
                        request.set("useUTCTime", CurrentSingleRefData->useUTCtime());
                    }
                }
            }
            m_session->sendRequest(request, requestId);
        }
    }

    void QBbgRequestResponseWorker::start(const QBbgRequestGroup& req)
    {
        Q_D(QBbgRequestResponseWorker);
        setRequest(req);
        start();
    }

    void QBbgRequestResponseWorker::start()
    {
        Q_D(QBbgRequestResponseWorker);
        if (d->m_SessionRunning) return;
        d->m_SessionRunning = true;
        d->m_ResurnedResults = 0;
        d->m_session->startAsync();
    }

    const QBbgAbstractResponse* QBbgRequestResponseWorker::result(qint64 id) const
    {
        Q_D(const QBbgRequestResponseWorker);
        return d->m_Results.value(id, NULL);
    }

    QBbgRequestResponseWorker::QBbgRequestResponseWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent)
        :QBbgAbstractWorker(new QBbgRequestResponseWorkerPrivate(this,option),parent)
    {}

    void QBbgRequestResponseWorker::setRequest(const QBbgRequestGroup& req)
    {
        Q_D(QBbgRequestResponseWorker);
        if (d->m_SessionRunning) return;
        d->m_Requests = req;
        d->m_Requests.RequestGroups(d->Groups);
    }

}