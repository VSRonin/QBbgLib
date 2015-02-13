#include "QBbgAbstractResponse.h"
#include "QBbgAbstractResponse_p.h"
namespace QBbgLib {
    QBbgAbstractResponse::~QBbgAbstractResponse()
    {
        delete d_ptr;
    }
    QBbgAbstractResponse::QBbgAbstractResponse()
        :d_ptr(new QBbgAbstractResponsePrivate(this))
    {}
    QBbgAbstractResponse::QBbgAbstractResponse(const QBbgAbstractResponse& other)
        : d_ptr(new QBbgAbstractResponsePrivate(this, *(other.d_func())))
    {}
    QBbgAbstractResponse::QBbgAbstractResponse(QBbgAbstractResponsePrivate* d)
        : d_ptr(d)
    {}
    void QBbgAbstractResponse::setErrorCode(BbgErrorCodes ErrCd)
    {
        Q_D(QBbgAbstractResponse);
        if (ErrCd == NoErrors)  
            d->m_ErrorCode = NoErrors;
        else 
            d->m_ErrorCode |= ErrCd;
    }
    bool QBbgAbstractResponse::hasErrors() const
    {
        return errorCode() != NoErrors;
    }
    QBbgAbstractResponse::BbgErrorCodes QBbgAbstractResponse::errorCode() const
    {
        Q_D(const QBbgAbstractResponse);
        return d->m_ErrorCode;
    }
    QString QBbgAbstractResponse::errorString() const
    {
        return bbgErrorCode2String(errorCode());
    }
    QBbgAbstractResponse& QBbgAbstractResponse::operator=(const QBbgAbstractResponse& other)
    {
        Q_D(QBbgAbstractResponse);
        d->operator=(*(other.d_func()));
        return *this;
    }
    void QBbgAbstractResponse::setID(qint64 val)
    {
        Q_D(QBbgAbstractResponse);
        d->m_ID = val;
    }
    qint64 QBbgAbstractResponse::getID() const
    {
        Q_D(const QBbgAbstractResponse);
        return d->m_ID;
    }
    QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse* q)
        : q_ptr(q)
        , m_ErrorCode(QBbgAbstractResponse::NoErrors)
        , m_ResType(QBbgAbstractResponse::Invalid)
        , m_ID(0)
    {}
    QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, const QBbgAbstractResponsePrivate& other)
        : q_ptr(q)
        , m_ErrorCode(other.m_ErrorCode)
        , m_ResType(other.m_ResType)
        , m_ID(other.m_ID)
    {}
    QBbgAbstractResponsePrivate& QBbgAbstractResponsePrivate::operator=(const QBbgAbstractResponsePrivate& other)
    {
        m_ErrorCode = other.m_ErrorCode;
        m_ResType = other.m_ResType;
        m_ID = m_ID;
        return *this;
    }
    QString QBbgAbstractResponse::bbgErrorCode2String(BbgErrorCodes a)
    {
        if (a == NoErrors) return "NoErrors";
        QString Result;
        if (a & ResponseError) Result += "Response Error, ";
        if (a & SecurityError) Result += "Invalid Security, ";
        if (a & InvalidInputs) Result += "Invalid Inputs, ";
        if (a & SessionError) Result += "Session Error, ";
        if (a & ServiceError) Result += "Service Error, ";
        if (a & FieldError) Result += "Invalid Field, ";
        if (a & UnknownError) Result += "Unknown Error, ";
        if (a & SessionStopped) Result += "Session Stopped, ";
        if (a & NoData) Result += "No Data, ";
        Result.chop(2);
        return Result;
    }

    QBbgAbstractResponse::ResponseType QBbgAbstractResponse::responseType() const
    {
        Q_D(const QBbgAbstractResponse);
        return d->m_ResType;
    }
    QBbgAbstractResponse::ResponseType QBbgAbstractResponse::stringToResponseType(QString a)
    {
        a = a.toLower().trimmed();
        if (a == "BeqsResponse") return BeqsResponse;
        else if (a == "historicaldataresponse") return HistoricalDataResponse;
        else if (a == "referencedataresponse") return ReferenceDataResponse;
        else if (a == "portfoliodataresponse") return PortfolioDataResponse;
        else if (a == "intradaytickresponse") return IntraDayTickResponse;
        else if (a == "intradaybarresponse") return IntraDayBarResponse;
        else return Invalid;
    }
    QString QBbgAbstractResponse::responseTypeToString(ResponseType a)
    {
        switch (a) {
        case QBbgLib::QBbgAbstractResponse::BeqsResponse:
            return "BeqsResponse";
        case QBbgLib::QBbgAbstractResponse::HistoricalDataResponse:
            return "HistoricalDataResponse";
        case QBbgLib::QBbgAbstractResponse::ReferenceDataResponse:
            return "ReferenceDataResponse";
        case QBbgLib::QBbgAbstractResponse::PortfolioDataResponse:
            return "PortfolioDataResponse";
        case QBbgLib::QBbgAbstractResponse::IntraDayTickResponse:
            return "IntraDayTickResponse";
        case QBbgLib::QBbgAbstractResponse::IntraDayBarResponse:
            return "IntraDayBarResponse";
        default:
            return QString();
        }
    }
}