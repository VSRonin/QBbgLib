#include "QBbgAbstractFieldRequest.h"
#include "QBbgAbstractFieldRequest_p.h"
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
    void QBbgAbstractFieldRequest::setOverrides(const Overrides& Overr)
    {
        Q_D(QBbgAbstractFieldRequest);
        clearOverrides();
        for (auto i = Overr.constBegin(); i != Overr.constEnd(); i++) {
            if (i.value().isNull()) continue;
            if (i.key().isEmpty()) continue;
            QString TempKey = i.key().simplified().toUpper();
            TempKey.replace(QChar(' '), QChar('_'));
            d->m_Overrides.insert(TempKey, i.value());
        }
    }
    void QBbgAbstractFieldRequest::setOverride(QString Name, const QVariant& Value)
    {
        Q_D(QBbgAbstractFieldRequest);
        Name = Name.simplified().toUpper();
        Name.replace(QChar(' '), QChar('_'));
        Overrides::iterator iter= d->m_Overrides.find(Name);
        if (Value.isNull()) {
            if (iter != d->m_Overrides.end)
                d->m_Overrides.erase(iter);
            return;
        }
        if (iter == d->m_Overrides.end)
            d->m_Overrides.insert(Name, Value);
        else
            iter.value() = Value;
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
    const Overrides& QBbgAbstractFieldRequest::overrides() const
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