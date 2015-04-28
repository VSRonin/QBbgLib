#include "QBbgAbstractFieldRequest.h"
#include "private/QBbgAbstractFieldRequest_p.h"
#include "QBbgOverride.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
    void QBbgAbstractFieldRequest::setField(const QString& val)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Field = val.simplified().toUpper();
        d->m_Field.replace(QChar(' '), QChar('_'));
    }
    QBbgAbstractFieldRequestPrivate::QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q)
        : QBbgAbstractRequestPrivate(q)
    {}
    QBbgAbstractFieldRequestPrivate::QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, const QBbgAbstractFieldRequestPrivate& a)
        : QBbgAbstractRequestPrivate(q,a)
        , m_Field(a.m_Field)
        , m_Overrides(a.m_Overrides)
    {}
    QBbgAbstractFieldRequestPrivate& QBbgAbstractFieldRequestPrivate::operator=(const QBbgAbstractFieldRequestPrivate& a)
    {
        QBbgAbstractRequestPrivate::operator=(a);
        m_Field = a.m_Field;
        m_Overrides = a.m_Overrides;
        return *this;
    }
    void QBbgAbstractFieldRequest::setOverrides(const QBbgOverride& Overr)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Overrides = Overr;
    }
    void QBbgAbstractFieldRequest::clearOverrides()
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Overrides.clear();
    }
    bool QBbgAbstractFieldRequest::sameOverrides(const QBbgAbstractFieldRequest& a)const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->SameOverrides(*(a.d_func()));
    }
    bool QBbgAbstractFieldRequestPrivate::SameOverrides(const QBbgAbstractFieldRequestPrivate& a)const
    {
        return m_Overrides == a.m_Overrides;
    }

    bool QBbgAbstractFieldRequest::isValidReq() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return
            !d->m_Field.isEmpty()
            && d->m_Security.isValid()
            && (d->m_RqType & FirstFielded)
            ;
    }

    bool QBbgAbstractFieldRequestPrivate::operator==(const QBbgAbstractFieldRequestPrivate& a) const
    {
        if (
            (m_Security != a.m_Security)
            || (m_Field != a.m_Field)
            || (m_RqType != a.m_RqType)
            )
            return false;
        return m_Overrides == a.m_Overrides;
    }
    bool QBbgAbstractFieldRequest::operator==(const QBbgAbstractFieldRequest& a) const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->operator==(*(a.d_func()));
    }
    const QString& QBbgAbstractFieldRequest::field() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->m_Field;
    }
    const QBbgOverride& QBbgAbstractFieldRequest::overrides() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->m_Overrides;
    }

    QBbgAbstractFieldRequest::QBbgAbstractFieldRequest()
        :QBbgAbstractRequest(new QBbgAbstractFieldRequestPrivate(this))
    {}

    QBbgAbstractFieldRequest::QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a)
        : QBbgAbstractRequest(new QBbgAbstractFieldRequestPrivate(this, *(a.d_func())))
    {}

    QBbgAbstractFieldRequest::QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d)
        : QBbgAbstractRequest(d)
    {}

    QBbgAbstractFieldRequest& QBbgAbstractFieldRequest::operator=(const QBbgAbstractFieldRequest& a)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
}
