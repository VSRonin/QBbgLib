#include "QBbgAbstractRequest.h"
#include "QBbgAbstractRequest_p.h"
namespace QBbgLib {
    QBbgAbstractRequest::QBbgAbstractRequest()
        : d_ptr(new QBbgAbstractRequestPrivate(this))
    {}
    QBbgAbstractRequest::QBbgAbstractRequest(const QBbgAbstractRequest& other)
        : d_ptr(new QBbgAbstractRequestPrivate(this, *(other.d_ptr)))
    {}

    QBbgAbstractRequest::QBbgAbstractRequest(QBbgAbstractRequestPrivate* d)
        : d_ptr(d)
    {}
    QBbgAbstractRequest::~QBbgAbstractRequest()
    {
        delete d_ptr;
    }
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q)
        : q_ptr(q)
        , m_RqType(QBbgAbstractRequest::ReferenceData)
    {}
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, const QBbgAbstractRequestPrivate& other)
        : q_ptr(q)
        , m_ID(other.m_ID)
        , m_Security(other.m_Security)
        , m_RqType(other.m_RqType)
    {}
    QBbgAbstractRequestPrivate& QBbgAbstractRequestPrivate::operator=(const QBbgAbstractRequestPrivate& other)
    {
        m_ID = other.m_ID;
        m_Security = other.m_Security;
        m_RqType = other.m_RqType;
        return *this;
    }
    void QBbgAbstractRequest::setSecurity(const QBbgSecurity& val)
    {
        Q_D(QBbgAbstractRequest);
        d->m_Security = val;
    }
    const QBbgSecurity& QBbgAbstractRequest::security() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_Security;
    }
    QBbgAbstractRequest& QBbgAbstractRequest::operator=(const QBbgAbstractRequest& other)
    {
        Q_D(QBbgAbstractRequest);
        d->operator=(*(other.d_ptr));
        return *this;
    }
    qint64 QBbgAbstractRequest::getID() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_ID;
    }
    void QBbgAbstractRequest::setID(qint64 val)
    {
        Q_D(QBbgAbstractRequest);
        d->m_ID = val;
    }
}

