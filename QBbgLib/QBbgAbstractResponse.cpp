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
    QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse* q)
        : q_ptr(q)
        , m_ErrorCode(QBbgAbstractResponse::NoErrors)
        , m_ResType(QBbgAbstractResponse::Invalid)
    {}
    QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, const QBbgAbstractResponsePrivate& other)
        : q_ptr(q)
        , m_ErrorCode(other.m_ErrorCode)
        , m_ResType(other.m_ResType)
    {}
    QBbgAbstractResponsePrivate& QBbgAbstractResponsePrivate::operator=(const QBbgAbstractResponsePrivate& other)
    {
        m_ErrorCode = other.m_ErrorCode;
        m_ResType = other.m_ResType;
    }
}