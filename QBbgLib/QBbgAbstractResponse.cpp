#include "QBbgAbstractResponse.h"
#include "private/QBbgAbstractResponse_p.h"
#include <QHash>
namespace QBbgLib {

    QBbgAbstractResponsePrivate::~QBbgAbstractResponsePrivate() = default;
}
    QBbgAbstractResponse::~QBbgAbstractResponse()
    {
        delete d_ptr;
    }
    QBbgAbstractResponse::QBbgAbstractResponse(ResponseType typ)
        :d_ptr(new QBbgAbstractResponsePrivate(this,typ))
    {}
    QBbgAbstractResponse::QBbgAbstractResponse(const QBbgAbstractResponse& other)
        : d_ptr(new QBbgAbstractResponsePrivate(this, *(other.d_func())))
    {}
    QBbgAbstractResponse::QBbgAbstractResponse(QBbgAbstractResponsePrivate* d)
        : d_ptr(d)
    {}
    void QBbgAbstractResponse::setErrorCode(BbgErrorCodes ErrCd, const QString& errMsg)
    {
        Q_D(QBbgAbstractResponse);
        if (ErrCd == NoErrors) {
            d->m_ErrorCode = NoErrors;
            d->m_ErrorMessage.clear();
        }
        else {
            d->m_ErrorCode |= ErrCd;
            d->m_ErrorMessage = errMsg;
        }
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
    QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, QBbgAbstractResponse::ResponseType typ)
        : q_ptr(q)
        , m_ErrorCode(QBbgAbstractResponse::NoErrors)
        , m_ResType(typ)
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
        Q_ASSERT_X(m_ResType == other.m_ResType, "QBbgAbstractRequestPrivate::operator=", "Trying to copy between two diffrent Response types");
        m_ErrorCode = other.m_ErrorCode;
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
        if (a == "BeqsResponse") return ResponseType::BeqsResponse;
        else if (a == "historicaldataresponse") return ResponseType::HistoricalDataResponse;
        else if (a == "referencedataresponse") return ResponseType::ReferenceDataResponse;
        else if (a == "portfoliodataresponse") return ResponseType::PortfolioDataResponse;
        else if (a == "intradaytickresponse") return ResponseType::IntraDayTickResponse;
        else if (a == "intradaybarresponse") return ResponseType::IntraDayBarResponse;
        else return ResponseType::Invalid;
    }
    QString QBbgAbstractResponse::responseTypeToString(ResponseType a)
    {
        switch (a) {
        case QBbgLib::QBbgAbstractResponse::ResponseType::BeqsResponse:
            return "BeqsResponse";
        case QBbgLib::QBbgAbstractResponse::ResponseType::HistoricalDataResponse:
            return "HistoricalDataResponse";
        case QBbgLib::QBbgAbstractResponse::ResponseType::ReferenceDataResponse:
            return "ReferenceDataResponse";
        case QBbgLib::QBbgAbstractResponse::ResponseType::PortfolioDataResponse:
            return "PortfolioDataResponse";
        case QBbgLib::QBbgAbstractResponse::ResponseType::IntraDayTickResponse:
            return "IntraDayTickResponse";
        case QBbgLib::QBbgAbstractResponse::ResponseType::IntraDayBarResponse:
            return "IntraDayBarResponse";
        default:
            return QString();
        }
    }
    QString QBbgAbstractResponse::errorMessage() const
    {
        Q_D(const QBbgAbstractResponse);
        return errorString() + " - " + d->m_ErrorMessage;
    }
}

uint qHash(QBbgLib::QBbgAbstractResponse::ResponseType key, uint seed /*= 0*/)
{
    return qHash(static_cast<qint32>(key), seed);
}
