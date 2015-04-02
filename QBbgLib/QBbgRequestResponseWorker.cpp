#include "QBbgRequestResponseWorker.h"
#include "QBbgRequestResponseWorker_p.h"
#include "QBbgReferenceDataResponse.h"
#include <QSet>
#include "QBbgRequestGroup.h"
#include "QBbgAbstractFieldRequest.h"
#include "QBbgOverride.h"
#include "QbbgReferenceDataRequest.h"
#include "QBbgPortfolioDataRequest.h"
#include "QBbgPortfolioDataRequest.h"
#include "QBbgPortfolioDataResponse.h"
#include "QBbgHistoricalDataRequest.h"
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
#ifdef PRINT_RESPONSE_MESSAGE
            message.print(std::cout);
#endif // _DEBUG
            const QList<qint64>* CurrentGroup = Groups.value(message.correlationId().asInteger(), NULL);
            Q_ASSERT_X(CurrentGroup, "QBbgRequestResponseWorkerPrivate::handleResponseEvent", "Recieving response from unknown request");
            if (message.hasElement("responseError")) {
                for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                    SetError(*SingleReq, QBbgAbstractResponse::ResponseError, message.getElement("responseError").getElementAsString("message"));
                }
                return;
            }

            switch (QBbgAbstractResponse::stringToResponseType(message.messageType().string())) {
            case QBbgAbstractResponse::PortfolioDataResponse:
            {
                BloombergLP::blpapi::Element secDataArray = message.getElement("securityData"); //securityData[]
                for (size_t secIter = 0; secIter < secDataArray.numValues(); ++secIter) {
                    QString CurrentSecurity = secDataArray.getValueAsElement(secIter).getElementAsString("security");
                    BloombergLP::blpapi::Element fieldExcepArray = secDataArray.getValueAsElement(secIter).getElement("fieldExceptions"); //fieldExceptions[]

                    if (secDataArray.getValueAsElement(secIter).hasElement("securityError")) {
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractRequest* const FoundRequ = m_Requests.request(*SingleReq);
                            if (FoundRequ->security().fullName() == CurrentSecurity) {
                                SetError(*SingleReq, QBbgAbstractResponse::SecurityError, secDataArray.getValueAsElement(secIter).getElement("securityError").getElementAsString("message"));
                            }
                        }
                    }
                    else {
                        BloombergLP::blpapi::Element fieldDataArray = secDataArray.getValueAsElement(secIter).getElement("fieldData"); //fieldData[]
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractFieldRequest* const FoundRequ = dynamic_cast<const QBbgAbstractFieldRequest*>(m_Requests.request(*SingleReq));
                            Q_ASSERT(FoundRequ);
                            if (!fieldDataArray.hasElement(FoundRequ->field().toLatin1().data())) {
                                bool foundExp = false;
                                for (size_t fieldExcIter = 0; fieldExcIter < fieldExcepArray.numValues() && !foundExp; ++fieldExcIter) {
                                    QString CurrentField = fieldExcepArray.getValueAsElement(fieldExcIter).getElementAsString("fieldId");
                                    if (FoundRequ->security().fullName() == CurrentSecurity && FoundRequ->field() == CurrentField) {
                                        SetError(*SingleReq, QBbgAbstractResponse::FieldError, fieldExcepArray.getValueAsElement(fieldExcIter).getElement("errorInfo").getElementAsString("message"));
                                        foundExp = true;
                                    }
                                }
                                if (!foundExp)
                                    //continue;
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData, "Field not found in response");
                            }
                            else {
                                BloombergLP::blpapi::Element fieldDataValue = fieldDataArray.getElement(FoundRequ->field().toLatin1().data());
                                if (fieldDataValue.numValues() == 0) {
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData, "Table response with 0 rows");
                                }
                                else if (fieldDataValue.getValueAsElement(0).numElements() == 0) {
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData, "Table response with 0 columns");
                                }
                                else {
                                    QString tempSec;
                                    double tmpPos, tmpMkVal, tmpCst, tmpCstFx, tmpWei;
                                    QDate tmpCstDt;
                                    bool oneSent = false;
                                    for (size_t RowIter = 0; RowIter < fieldDataValue.numValues(); ++RowIter) {
                                        if (!fieldDataValue.getValueAsElement(RowIter).hasElement("Security")) continue;
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Position")) tmpPos = fieldDataValue.getValueAsElement(RowIter).getElementAsFloat64("Position");
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Market Value")) tmpMkVal = fieldDataValue.getValueAsElement(RowIter).getElementAsFloat64("Market Value");
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Cost")) tmpCst = fieldDataValue.getValueAsElement(RowIter).getElementAsFloat64("Cost");
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Cost Fx Rate")) tmpCstFx = fieldDataValue.getValueAsElement(RowIter).getElementAsFloat64("Cost Fx Rate");
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Weight")) tmpWei = fieldDataValue.getValueAsElement(RowIter).getElementAsFloat64("Weight");
                                        if (fieldDataValue.getValueAsElement(RowIter).hasElement("Cost Date")) tmpCstDt = elementToVariant(fieldDataValue.getValueAsElement(RowIter).getElement("Cost Date")).toDate();
                                        PortfolioDataRecieved(
                                            *SingleReq
                                            , fieldDataValue.getValueAsElement(RowIter).getElementAsString("Security")
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Position") ? (&tmpPos) : static_cast<double*>(NULL)
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Market Value") ? (&tmpMkVal) : static_cast<double*>(NULL)
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Cost") ? (&tmpCst) : static_cast<double*>(NULL)
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Cost Date") ? (&tmpCstDt) : static_cast<QDate*>(NULL)
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Cost Fx Rate") ? (&tmpCstFx) : static_cast<double*>(NULL)
                                            , fieldDataValue.getValueAsElement(RowIter).hasElement("Weight") ? (&tmpWei) : static_cast<double*>(NULL)
                                            );
                                        oneSent = true;
                                    }
                                    if (oneSent) {
                                        HeaderRecieved(*SingleReq, FoundRequ->field());
                                        DataRecieved(*SingleReq);
                                    }
                                    else {
                                        SetError(*SingleReq, QBbgAbstractResponse::NoData, "No security found");
                                    }
                                }
                            }
                        }


                    }
                }
            }
            break;
            case QBbgAbstractResponse::ReferenceDataResponse:
            {
                BloombergLP::blpapi::Element secDataArray = message.getElement("securityData"); //securityData[]
                for (size_t secIter = 0; secIter < secDataArray.numValues(); ++secIter) {
                    QString CurrentSecurity = secDataArray.getValueAsElement(secIter).getElementAsString("security");
                    BloombergLP::blpapi::Element fieldExcepArray = secDataArray.getValueAsElement(secIter).getElement("fieldExceptions"); //fieldExceptions[]

                    if (secDataArray.getValueAsElement(secIter).hasElement("securityError")) {
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractRequest* const FoundRequ = m_Requests.request(*SingleReq);
                            if (FoundRequ->security().fullName() == CurrentSecurity) {
                                SetError(*SingleReq, QBbgAbstractResponse::SecurityError, secDataArray.getValueAsElement(secIter).getElement("securityError").getElementAsString("message"));
                            }
                        }
                    }
                    else {
                        BloombergLP::blpapi::Element fieldDataArray = secDataArray.getValueAsElement(secIter).getElement("fieldData"); //fieldData[]
                        for (QList<qint64>::const_iterator SingleReq = CurrentGroup->constBegin(); SingleReq != CurrentGroup->constEnd(); SingleReq++) {
                            const QBbgAbstractFieldRequest* const FoundRequ = dynamic_cast<const QBbgAbstractFieldRequest*>(m_Requests.request(*SingleReq));
                            Q_ASSERT(FoundRequ);
                            if (!fieldDataArray.hasElement(FoundRequ->field().toLatin1().data())) {
                                bool foundExp = false;
                                for (size_t fieldExcIter = 0; fieldExcIter < fieldExcepArray.numValues() && !foundExp; ++fieldExcIter) {
                                    QString CurrentField = fieldExcepArray.getValueAsElement(fieldExcIter).getElementAsString("fieldId");
                                    if (FoundRequ->security().fullName() == CurrentSecurity && FoundRequ->field() == CurrentField) {
                                        SetError(*SingleReq, QBbgAbstractResponse::FieldError, fieldExcepArray.getValueAsElement(fieldExcIter).getElement("errorInfo").getElementAsString("message"));
                                        foundExp = true;
                                    }
                                }
                                if (!foundExp)
                                    //continue;
                                    SetError(*SingleReq, QBbgAbstractResponse::NoData, "Field not found in response");
                            }
                            else {
                                BloombergLP::blpapi::Element fieldDataValue = fieldDataArray.getElement(FoundRequ->field().toLatin1().data());
                                if (fieldDataValue.isArray()) {
                                    if (fieldDataValue.numValues() == 0) {
                                        SetError(*SingleReq, QBbgAbstractResponse::NoData, "Table response with 0 rows");
                                    }
                                    else {
                                        size_t NumCols = fieldDataValue.getValueAsElement(0).numElements();
                                        if (NumCols == 0) {
                                            SetError(*SingleReq, QBbgAbstractResponse::NoData, "Table response with 0 columns");
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
                                else {
                                    DataPointRecieved(*SingleReq, elementToVariant(fieldDataValue), FoundRequ->field());
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
                        SetError(*i, QBbgAbstractResponse::SessionError, "Impossible to connect to BBG");
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
                            SetError(*i, QBbgAbstractResponse::ServiceError, "Failed to open required BBG service");
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
                SetError(*i, QBbgAbstractResponse::UnknownError, QString());
        }
        }
        return true;
    }

    void QBbgRequestResponseWorkerPrivate::SetError(qint64 RequestID, QBbgAbstractResponse::BbgErrorCodes Err, const QString& errMsg)
    {
        QBbgAbstractResponse* TempRes = NULL;
        switch (m_Requests.request(RequestID)->requestType()) {
        case QBbgAbstractRequest::ReferenceData:
            TempRes = new QBbgReferenceDataResponse();
            break;
        case QBbgAbstractRequest::PortfolioData:
            TempRes = new QBbgPortfolioDataResponse();
            break;
        default:
            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::SetError", "Unhandled request type");
            break;
        }
        setResponseID(TempRes, RequestID);
        setResponseError(TempRes, Err, errMsg);
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
        default:
            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::DataPointRecieved", "Only ReferenceData can recieve Data Points");
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
        Q_ASSERT_X(m_ResurnedResults <= m_Requests.size(), "QBbgRequestResponseWorkerPrivate::HeaderRecieved", "Too many results returned");
        if (m_ResurnedResults == m_Requests.size()) {
            m_session->stopAsync();
        }
    }
    void QBbgRequestResponseWorkerPrivate::DataRowRecieved(qint64 RequestID, const QList<QVariant>& Value, const QList<QString>& Header)
    {
        QHash<qint64, QBbgAbstractResponse* >::iterator TempIter = m_Results.find(RequestID);
        if (m_Requests.request(RequestID)->requestType() == QBbgAbstractRequest::ReferenceData) {
            if (TempIter == m_Results.end()) {
                TempIter = m_Results.insert(RequestID, new QBbgReferenceDataResponse());
            }
            dynamic_cast<QBbgReferenceDataResponse*>(TempIter.value())->addValueRow(Value, Header);
            return;
        }
        Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::DataRowRecieved", "Only ReferenceData can recieve Data Rows");
    }
    void QBbgRequestResponseWorkerPrivate::PortfolioDataRecieved(qint64 RequestID, const QString& Sec, const double* pos, const double* mkVal, const double* cst, const QDate* cstDt, const double* cstFx, const double* wei)
    {
        QHash<qint64, QBbgAbstractResponse* >::iterator TempIter = m_Results.find(RequestID);
        if (m_Requests.request(RequestID)->requestType() == QBbgAbstractRequest::PortfolioData) {
            if (TempIter == m_Results.end()) {
                TempIter = m_Results.insert(RequestID, new QBbgPortfolioDataResponse());
            }
            QBbgPortfolioDataResponse* currRes = dynamic_cast<QBbgPortfolioDataResponse*>(TempIter.value());
            Q_ASSERT((pos && currRes->size() > 0) == currRes->hasPosition());
            Q_ASSERT((mkVal && currRes->size() > 0) == currRes->hasMarketValue());
            Q_ASSERT((cst && currRes->size() > 0) == currRes->hasCost());
            Q_ASSERT((cstDt && currRes->size() > 0) == currRes->hasCostDate());
            Q_ASSERT((cstFx && currRes->size() > 0) == currRes->hasCostFx());
            Q_ASSERT((wei && currRes->size() > 0) == currRes->hasWeight());
            currRes->addSecurity(Sec);
            Q_ASSERT_X(currRes->security(currRes->size() - 1).isValid(), "QBbgRequestResponseWorkerPrivate::PortfolioDataRecieved", "Invalid security recieved");
            if (pos) currRes->addPosition(*pos);
            if (mkVal) currRes->addMarketValue(*mkVal);
            if (cst) currRes->addCost(*cst);
            if (cstDt) currRes->addCostDate(*cstDt);
            if (cstFx) currRes->addCostFx(*cstFx);
            if (wei) currRes->addWeight(*wei);
            return;
        }
        Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::PortfolioDataRecieved", "Only PortfolioData can recieve Portfolio Data");
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
                    SetError(*GroupIter, QBbgAbstractResponse::InvalidInputs, "Invalid Request");
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
                    else if (reqType == QBbgAbstractRequest::HistoricalData) {
                        const QBbgHistoricalDataRequest* CurrentSingleHistData = dynamic_cast<const QBbgHistoricalDataRequest*>(CurrentSingle);
                        Q_ASSERT(CurrentSingleHistData);
                        request.set("startDate", CurrentSingleHistData->startDate().toString("yyyyMMdd").toLatin1().data());
                        request.set("endDate", (CurrentSingleHistData->endDate().isNull() ? QDate::currentDate() : CurrentSingleHistData->endDate()).toString("yyyyMMdd").toLatin1().data());
                        switch (CurrentSingleHistData->periodicityAdjustment()) {
                        case QBbgHistoricalDataRequest::ACTUAL:
                            request.set("periodicityAdjustment", "ACTUAL");
                            break;
                        case QBbgHistoricalDataRequest::CALENDAR:
                            request.set("periodicityAdjustment", "CALENDAR");
                            break;
                        case QBbgHistoricalDataRequest::FISCAL:
                            request.set("periodicityAdjustment", "FISCAL");
                            break;
                        default:
                            Q_ASSERT_X(false,"QBbgRequestResponseWorkerPrivate::SendRequ", "Unhandled periodicityAdjustment");
                        }
                        switch (CurrentSingleHistData->periodicitySelection()) {
                        case QBbgHistoricalDataRequest::DAILY:
                            request.set("periodicitySelection", "DAILY");
                            break;
                        case QBbgHistoricalDataRequest::WEEKLY:
                            request.set("periodicitySelection", "WEEKLY");
                            break;
                        case QBbgHistoricalDataRequest::MONTHLY:
                            request.set("periodicitySelection", "MONTHLY");
                            break;
                        case QBbgHistoricalDataRequest::QUARTERLY:
                            request.set("periodicitySelection", "QUARTERLY");
                            break;
                        case QBbgHistoricalDataRequest::SEMI_ANNUALLY:
                            request.set("periodicitySelection", "SEMI_ANNUALLY");
                            break;
                        case QBbgHistoricalDataRequest::YEARLY:
                            request.set("periodicitySelection", "YEARLY");
                            break;
                        default:
                            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::SendRequ", "Unhandled periodicitySelection");
                        }
                        if (CurrentSingleHistData->currency().size() == 3)
                            request.set("currency", CurrentSingleHistData->currency().toLatin1().data());
                        request.set("overrideOption", CurrentSingleHistData->useClosePrice() ? "OVERRIDE_OPTION_CLOSE" : "OVERRIDE_OPTION_GPA");
                        request.set("pricingOption", CurrentSingleHistData->usePriceForPricing() ? "PRICING_OPTION_PRICE" : "PRICING_OPTION_YIELD");
                        switch (CurrentSingleHistData->nonTradingDayFill()) {
                        case QBbgHistoricalDataRequest::NON_TRADING_WEEKDAYS:
                            request.set("nonTradingDayFillOption", "NON_TRADING_WEEKDAYS");
                            break;
                        case QBbgHistoricalDataRequest::ALL_CALENDAR_DAYS:
                            request.set("nonTradingDayFillOption", "ALL_CALENDAR_DAYS");
                            break;
                        case QBbgHistoricalDataRequest::FISCAL:
                            request.set("nonTradingDayFillOption", "ACTIVE_DAYS_ONLY");
                            break;
                        default:
                            Q_ASSERT_X(false, "QBbgRequestResponseWorkerPrivate::SendRequ", "Unhandled nonTradingDayFill");
                        }
                        request.set("nonTradingDayFillMethod", CurrentSingleHistData->fillWithNull() ? "NIL_VALUE" : "PREVIOUS_VALUE");
                        if (CurrentSingleHistData->maxDataPoints()>0)
                            request.set("maxDataPoints", CurrentSingleHistData->maxDataPoints());
                        request.set("returnRelativeDate", CurrentSingleHistData->useRelativeDate());
                        request.set("adjustmentNormal", CurrentSingleHistData->adjustmentNormal());
                        request.set("adjustmentAbnormal", CurrentSingleHistData->adjustmentAbnormal());
                        request.set("adjustmentSplit", CurrentSingleHistData->adjustmentSplit());
                        request.set("adjustmentFollowDPDF", CurrentSingleHistData->adjustmentFollowDPDF());
                        if (CurrentSingleHistData->calendarCode().size() == 2)
                            request.set("calendarCodeOverride", CurrentSingleHistData->calendarCode().toLatin1().data());
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
        :QBbgAbstractWorker(new QBbgRequestResponseWorkerPrivate(this, option), parent)
    {}

    void QBbgRequestResponseWorker::setRequest(const QBbgRequestGroup& req)
    {
        Q_D(QBbgRequestResponseWorker);
        if (d->m_SessionRunning) return;
        d->m_Requests = req;
        d->m_Requests.RequestGroups(d->Groups);
    }

    void QBbgRequestResponseWorkerPrivate::fillNoData()
    {
        QList<qint64> allIDs=m_Requests.IDList();
        for (QList<qint64>::const_iterator i = allIDs.constBegin(); i != allIDs.constEnd(); ++i) {
            if (!m_Results.contains(*i))
                SetError(*i, QBbgAbstractResponse::NoData, "Required data not found");
        }
    }

}