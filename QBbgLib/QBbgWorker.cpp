#include "QBbgWorker.h"
#include "QBbgWorker_p.h"
#include <blpapi_correlationid.h>
#include <blpapi_event.h>
#include <blpapi_message.h>
#include <blpapi_request.h>
#include <blpapi_session.h>
#include "QSingleBbgRequest.h"
namespace QBbgLib {
    void QBbgWorker::setServerAddress(const QString& val)
    {
        Q_D(QBbgWorker);
        d->ServerAddress = val.trimmed();
    }
    QBbgWorkerPrivate::QBbgWorkerPrivate(QBbgWorker* q)
        :q_ptr(q)
        , ServerAddress("localhost")
        , ServerPort(8194)
        , m_UseSyncronous(false)
    {
        m_SessionFinished = false;
    }
    QBbgWorker::QBbgWorker(QObject* parent)
        : QObject(parent)
        , d_ptr(new QBbgWorkerPrivate(this))
    {}

    void QBbgWorkerPrivate::RunRequest()
    {
        if (session) return;
        m_SessionFinished = false;
        SetGlobalError(NoErrors);
        for (QMap<qint64, QSingleBbgResult* >::iterator i = m_Results.begin(); i != m_Results.end(); i++)
            delete (i.value());
        m_Results.clear();
        if (!m_Requests.IsValidReq()) {
            SetGlobalError(InvalidInputs);
            return;
        }
        m_Requests.RequestGroups(Groups);
        BloombergLP::blpapi::SessionOptions sessionOptions;
        sessionOptions.setServerHost(ServerAddress.toLatin1().data());
        sessionOptions.setServerPort(ServerPort);
        sessionOptions.setMaxPendingRequests(INT_MAX - 2);
        if (m_UseSyncronous) {
            session.reset(new BloombergLP::blpapi::Session(sessionOptions));
            if (!session->start()) {
                SetGlobalError(SessionError);
                return;
            }
            if (!session->openService("//blp/refdata")) {
                SetGlobalError(ServiceError);
                return;
            }
            Send();
        }
        else {
            session.reset(new BloombergLP::blpapi::Session(sessionOptions, this));
            if (!session->startAsync()) {
                SetGlobalError(SessionError);
                return;
            }
        }
    }

    void QBbgWorkerPrivate::Send()
    {
        QList<QString> UsedSecur;
        QList<QString> UsedField;
        BloombergLP::blpapi::Service refDataSvc = session->getService("//blp/refdata");
        for (QHash<qint64, QList<qint64>* >::const_iterator ReqIter = Groups.constBegin(); ReqIter != Groups.constEnd(); ReqIter++) {
            BloombergLP::blpapi::CorrelationId requestId(ReqIter.key());
            BloombergLP::blpapi::Request request = refDataSvc.createRequest("ReferenceDataRequest");
            const QList<qint64>* CurrentList = ReqIter.value();
            UsedSecur.clear();
            UsedField.clear();
            for (QList<qint64>::const_iterator GroupIter = CurrentList->constBegin(); GroupIter != CurrentList->constEnd(); GroupIter++) {
                const QSingleBbgRequest* CurrentSingle = m_Requests.FindRequest(*GroupIter);
                if (!CurrentSingle) continue;
                if (!CurrentSingle->IsValidReq()) {
                    if (SetError(ReqIter.key(), *GroupIter, InvalidInputs))
                        return EndOfProcess(); //All Invalid Inputs
                }
                if (!UsedSecur.contains(CurrentSingle->GetSecurity())) {
                    request.append("securities", CurrentSingle->GetFullSecurity().toLatin1().data());
                    UsedSecur.append(CurrentSingle->GetSecurity());
                }
                if (!UsedField.contains(CurrentSingle->GetField())) {
                    request.append("fields", CurrentSingle->GetField().toLatin1().data());
                    UsedField.append(CurrentSingle->GetField());
                }
                if (GroupIter == CurrentList->begin()) {
                    for (auto OvrIter = CurrentSingle->GetOverrides().constBegin(); OvrIter != CurrentSingle->GetOverrides().constEnd(); OvrIter++) {
                        BloombergLP::blpapi::Element CurrentOverrides = request.getElement("overrides").appendElement();
                        CurrentOverrides.setElement("fieldId", OvrIter.key().toLatin1().data());
                        CurrentOverrides.setElement("value", OvrIter.value().toLatin1().data());
                    }
                }
            }
            session->sendRequest(request, requestId);
            bool ContinueToLoop = m_UseSyncronous;
            while (ContinueToLoop) {
                BloombergLP::blpapi::Event event = session->nextEvent();
                if (event.eventType() == BloombergLP::blpapi::Event::RESPONSE || event.eventType() == BloombergLP::blpapi::Event::PARTIAL_RESPONSE) {
                    ContinueToLoop = event.eventType() != BloombergLP::blpapi::Event::RESPONSE;
                    handleResponseEvent(event);
                }
            }
        }
        bool ContinueToLoop = m_UseSyncronous;
        while (ContinueToLoop) {
            BloombergLP::blpapi::Event event = session->nextEvent();
            if (event.eventType() == BloombergLP::blpapi::Event::SESSION_STATUS) {
                BloombergLP::blpapi::MessageIterator iter(event);
                while (iter.next()) {
                    BloombergLP::blpapi::Message message = iter.message();
                    if (QString(message.messageType().string()) == "SessionTerminated") {
                        ContinueToLoop = false;
                    }
                }
            }
        }
        if (m_UseSyncronous) return EndOfProcess();
    }

    bool QBbgWorkerPrivate::processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession)
    {
        Q_Q(QBbgWorker);
        switch (event.eventType()) {
        case BloombergLP::blpapi::Event::SESSION_STATUS: {
            BloombergLP::blpapi::MessageIterator iter(event);
            while (iter.next()) {
                BloombergLP::blpapi::Message message = iter.message();
                QString MessageType = message.messageType().string();
                if (MessageType == "SessionStarted") {
                    CurrentSession->openServiceAsync("//blp/refdata", BloombergLP::blpapi::CorrelationId(-1i64));
                    q->Started(); // Emit signal
                }
                else if (MessageType == "SessionConnectionUp") continue;
                else if (MessageType == "SessionConnectionDown") continue;
                else if (MessageType == "SessionTerminated") {
                    EndOfProcess();
                }
                else /*if (MessageType == "SessionStartupFailure")*/ {
                    SetGlobalError(SessionError);
                }
            }
            break;
        }
        case BloombergLP::blpapi::Event::SERVICE_STATUS: {
            BloombergLP::blpapi::MessageIterator iter(event);
            while (iter.next()) {
                BloombergLP::blpapi::Message message = iter.message();
                if (message.correlationId().asInteger() == -1 && QString(message.messageType().string()) == "ServiceOpened") {
                    Send();
                }
                else {
                    SetGlobalError(ServiceError);
                }
            }
            break;
        }
        case BloombergLP::blpapi::Event::PARTIAL_RESPONSE:
        case BloombergLP::blpapi::Event::RESPONSE:
            handleResponseEvent(event);
            break;
        default:
            SetGlobalError(UnknownError);
        }
        return true;
    }

    void QBbgWorkerPrivate::handleResponseEvent(const BloombergLP::blpapi::Event& event)
    {
        BloombergLP::blpapi::MessageIterator iter(event);
        qint32 NumVals, NumFieldExep;
        while (iter.next()) {
            BloombergLP::blpapi::Message message = iter.message();
            //message.print(std::cout);
            const QList<qint64>* CurrentGroup = Groups.value(message.correlationId().asInteger(), nullptr);
            if (CurrentGroup) {
                if (message.hasElement("responseError")) {
                    for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                        if (SetError(message.correlationId().asInteger(), *SingleReq, ResponseError))return;
                    }
                    return;
                }
                if (QString(message.messageType().string()) == "ReferenceDataResponse") {
                    NumVals = message.getElement("securityData").numValues();
                    for (qint32 i = 0; i < NumVals; i++) {
                        NumFieldExep = message.getElement("securityData").getValueAsElement(i).getElement("fieldExceptions").numValues();
                        for (qint32 j = 0; j < NumFieldExep; j++) {
                            for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                                const QSingleBbgRequest* FoundRequ = m_Requests.FindRequest(*SingleReq);
                                QString CurrentSecurity = message.getElement("securityData").getValueAsElement(i).getElementAsString("security");
                                QString CurrentField = message.getElement("securityData").getValueAsElement(i).getElement("fieldExceptions").getValueAsElement(j).getElementAsString("fieldId");
                                if (
                                    FoundRequ->GetFullSecurity() == CurrentSecurity
                                    && FoundRequ->GetField() == CurrentField
                                    ) {
                                    if (SetError(message.correlationId().asInteger(), *SingleReq, FieldError))return;
                                }
                            }
                        }
                        if (message.getElement("securityData").getValueAsElement(i).hasElement("securityError")) {
                            QString CurrentSecurity = message.getElement("securityData").getValueAsElement(i).getElementAsString("security");
                            for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                                const QSingleBbgRequest* FoundRequ = m_Requests.FindRequest(*SingleReq);
                                if ((FoundRequ->GetFullSecurity()) == CurrentSecurity) {
                                    if (SetError(message.correlationId().asInteger(), *SingleReq, SecurityError))return;
                                }
                            }
                        }
                        else {
                            QString CurrentSecurity = message.getElement("securityData").getValueAsElement(i).getElementAsString("security");
                            for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                                const QSingleBbgRequest* FoundRequ = m_Requests.FindRequest(*SingleReq);
                                if ((FoundRequ->GetFullSecurity()) == CurrentSecurity) {
                                    if (message.getElement("securityData").getValueAsElement(i).getElement("fieldData").numElements() != 0) {
                                        if (message.getElement("securityData").getValueAsElement(i).getElement("fieldData").hasElement(FoundRequ->GetField().toLatin1().data())) {
                                            if (!message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElement(FoundRequ->GetField().toLatin1().data()).isArray()) {
                                                if (DataRecieved(message.correlationId().asInteger(), *SingleReq
                                                    , message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElementAsString(FoundRequ->GetField().toLatin1().data())
                                                    , FoundRequ->GetField()
                                                    )) return;
                                            }
                                            else {
                                                QList<QString> CurrentRow, CurrentHead;
                                                const qint32 NumResults =
                                                    message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElement(FoundRequ->GetField().toLatin1().data()).numValues();
                                                const qint32 NumCols =
                                                    message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElement(FoundRequ->GetField().toLatin1().data()).getValueAsElement(0).numElements();
                                                for (qint32 TableIter = 0; TableIter < NumResults; TableIter++) {
                                                    CurrentRow.clear(); CurrentHead.clear();
                                                    for (qint32 ColIter = 0; ColIter < NumCols; ColIter++) {
                                                        CurrentRow.append(message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElement(FoundRequ->GetField().toLatin1().data()).getValueAsElement(TableIter).getElement(ColIter).getValueAsString());
                                                        CurrentHead.append(message.getElement("securityData").getValueAsElement(i).getElement("fieldData").getElement(FoundRequ->GetField().toLatin1().data()).getValueAsElement(TableIter).getElement(ColIter).name().string());
                                                    }
                                                    DataRowRecieved(message.correlationId().asInteger(), *SingleReq, CurrentRow, CurrentHead);
                                                }
                                                if (DataRecieved(message.correlationId().asInteger(), *SingleReq, FoundRequ->GetField())) return;
                                            }
                                        }
                                        else {
                                            if (SetError(message.correlationId().asInteger(), *SingleReq, NoData))return;
                                        }
                                    }
                                    else {
                                        if (SetError(message.correlationId().asInteger(), *SingleReq, NoData)) return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    bool QBbgWorkerPrivate::SetError(qint64 GroupID, qint64 RequestID, BbgErrorCodes Err)
    {
        Q_Q(QBbgWorker);
        if (GroupID < 0) {
            m_Requests.SetErrorCode(Err);
            if (Err != NoErrors) {
                m_SessionFinished = true;
                if (m_UseSyncronous)
                    if (Err != SessionError) session->stop();
                    else {
                        q->Progress(100);
                        q->Finished();
                        if (Err != SessionError) session->stopAsync();
                    }
                    return true;
            }
            return false;
        }
        else {
            if (m_Results.contains(RequestID)) return false;
            QSingleBbgResult* TempRes = new QSingleBbgResult();
            TempRes->SetErrorCode(Err);
            m_Results.insert(RequestID, TempRes);
            return DataRecieved(GroupID, RequestID);
        }
    }

    bool QBbgWorkerPrivate::DataRecieved(qint64 GroupID, qint64 RequestID, const QString& Value, const QString& Header)
    {
        if (m_Results.contains(RequestID)) return false;
        QSingleBbgResult* TempRes = new QSingleBbgResult();
        TempRes->SetValue(Value, Header);
        m_Results.insert(RequestID, TempRes);
        return DataRecieved(GroupID, RequestID);
    }

    bool QBbgWorkerPrivate::DataRecieved(qint64 GroupID, qint64 RequestID, const QString& Header)
    {
        Q_Q(QBbgWorker);
        if (!Header.isEmpty() && m_Results.contains(RequestID)) {
            m_Results[RequestID]->SetHeader(Header);
        }
        if (!m_UseSyncronous) {
            q->Recieved(RequestID);
            q->Progress((100 * m_Results.size()) / m_Requests.NumRequests());
        }
        if (m_Results.size() == m_Requests.NumRequests()) {
            m_SessionFinished = true;
            if (m_UseSyncronous) {
                session->stop();
            }
            else {
                q->Finished();
                session->stopAsync();
            }
            return true;
        }
        return false;
    }

    void QBbgWorkerPrivate::DataRowRecieved(qint64 GroupID, qint64 RequestID, const QList<QString>&  Value, const QList<QString>&  Header)
    {
        QMap<qint64, QSingleBbgResult* >::iterator TempIter = m_Results.find(RequestID);
        if (TempIter == m_Results.end()) {
            QSingleBbgResult* TempRes = new QSingleBbgResult();
            TempRes->AddValueRow(Value, Header);
            m_Results.insert(RequestID, TempRes);
        }
        else {
            TempIter.value()->AddValueRow(Value, Header);
        }
        //DataRecieved(GroupID, RequestID);
    }

    void QBbgWorkerPrivate::EndOfProcess()
    {
        Q_Q(QBbgWorker);
        if (!session) return;
        m_SessionFinished = false;
        session.reset();
        if (m_UseSyncronous && (m_Requests.GetErrorCode() & SessionStopped)) {
            q->Stopped();
        }

    }
    void QBbgWorker::StopRequest()
    {
        Q_D(QBbgWorker);
        if (d->m_SessionFinished || d->m_UseSyncronous) return;
        if (d->session) {
            d->m_SessionFinished = true;
            d->m_Requests.SetErrorCode(SessionStopped);
            d->session->stopAsync();
        }
    }
    QBbgWorker::~QBbgWorker()
    {
        delete d_ptr;
    }
    QBbgWorkerPrivate::~QBbgWorkerPrivate()
    {
        if (session) {
            session->stop();
        }
        while (!m_Results.empty()) {
            delete (m_Results.begin().value());
            m_Results.erase(m_Results.begin());
        }
        while (!Groups.empty()) {
            delete (Groups.begin().value());
            Groups.erase(Groups.begin());
        }
    }
    const QString& QBbgWorker::serverAddress() const
    {
        Q_D(const QBbgWorker);
        return d->ServerAddress;
    }

    unsigned short QBbgWorker::serverPort() const
    {
        Q_D(const QBbgWorker);
        return d->ServerPort;
    }

    void QBbgWorker::setServerPort(unsigned short val)
    {
        Q_D(QBbgWorker);
        d->ServerPort = val;
    }

    void QBbgWorker::setRequest(const QBbgRequest& a)
    {
        Q_D(QBbgWorker);
        if (!d->session)
            d->m_Requests = a;
    }

    void QBbgWorker::startRequestSync()
    {
        Q_D(QBbgWorker);
        if (d->session) return;
        d->m_UseSyncronous = true;
        d->RunRequest();
    }

    void QBbgWorker::startRequestSync(const QBbgRequest& a)
    {
        setRequest(a);
        startRequestSync();
    }

    const QSingleBbgResult* QBbgWorker::GetResult(qint64 ID) const
    {
        Q_D(const QBbgWorker);
        return d->m_Results.value(ID, NULL);
    }

    const QBbgRequest& QBbgWorker::GetRequest() const
    {
        Q_D(const QBbgWorker);
        return d->m_Requests;
    }
    bool QBbgWorker::isRunning() const
    {
        Q_D(const QBbgWorker);
        return d->session && !d->m_SessionFinished;
    }

    void QBbgWorker::StartRequestAsync()
    {
        Q_D(QBbgWorker);
        if (d->session) return;
        d->m_UseSyncronous = false;
        d->RunRequest();
    }

    void QBbgWorker::StartRequestAsync(const QBbgRequest& a)
    {
        setRequest(a);
        StartRequestAsync();
    }

    void QBbgWorkerPrivate::SetGlobalError(BbgErrorCodes Err)
    {
        SetError(-1i64, -1i64, Err);
    }
}