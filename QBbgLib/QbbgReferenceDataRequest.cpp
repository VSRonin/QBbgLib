#include "QbbgReferenceDataRequest.h"
#include "QbbgReferenceDataRequest_p.h"
namespace QBbgLib {
    QBbgReferenceDataRequestPrivate::QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q)
        : QBbgAbstractFieldRequestPrivate(q)
        , m_UseUTCTime(false)
    {
        m_RqType = QBbgAbstractRequest::ReferenceData;
    }
    QBbgReferenceDataRequestPrivate::QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q, const QBbgReferenceDataRequestPrivate& other)
        : QBbgAbstractFieldRequestPrivate(q, other)
        , m_UseUTCTime(other.m_UseUTCTime)
    {
        m_RqType = QBbgAbstractRequest::ReferenceData;
    }
    QBbgReferenceDataRequestPrivate& QBbgReferenceDataRequestPrivate::operator=(const QBbgReferenceDataRequestPrivate& other)
    {
        QBbgAbstractFieldRequestPrivate::operator=(other);
        m_UseUTCTime = other.m_UseUTCTime;
        return *this;
    }
    QBbgReferenceDataRequest::QBbgReferenceDataRequest()
        :QBbgAbstractFieldRequest(new QBbgReferenceDataRequestPrivate(this))
    {}
    QBbgReferenceDataRequest::QBbgReferenceDataRequest(QBbgReferenceDataRequestPrivate* d)
        : QBbgAbstractFieldRequest(d)
    {}
    QBbgReferenceDataRequest::QBbgReferenceDataRequest(const QBbgReferenceDataRequest& a)
        : QBbgAbstractFieldRequest(new QBbgReferenceDataRequestPrivate(this, *(a.d_func())))
    {}

    QBbgReferenceDataRequest& QBbgReferenceDataRequest::operator=(const QBbgReferenceDataRequest& a)
    {
        Q_D(QBbgReferenceDataRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
    bool QBbgReferenceDataRequestPrivate::operator==(const QBbgReferenceDataRequestPrivate& a) const
    {
        return m_UseUTCTime == a.m_UseUTCTime && QBbgAbstractFieldRequestPrivate::operator==(a);
    }
    bool QBbgReferenceDataRequest::operator==(const QBbgReferenceDataRequest& a) const
    {
        Q_D(const QBbgReferenceDataRequest);
        return d->operator==(*(a.d_func()));
    }
    void QBbgReferenceDataRequest::setUseUTCtime(bool a)
    {
        Q_D(QBbgReferenceDataRequest);
        d->m_UseUTCTime = a;
    }
    bool QBbgReferenceDataRequest::useUTCtime() const
    {
        Q_D(const QBbgReferenceDataRequest);
        return d->m_UseUTCTime;
    }
    void QBbgReferenceDataRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() != QBbgSecurity::Client) {
            QBbgAbstractFieldRequest::setSecurity(val);
        }
    }

}