#include "QSingleBbgRequest.h"
#include "QSingleBbgRequest_p.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
    void QSingleBbgRequest::SetField(const QString& val)
    {
        Q_D(QSingleBbgRequest);
        d->m_Field = val.simplified().toUpper();
        d->m_Field.replace(QChar(' '), QChar('_'));
    }
    QSingleBbgRequestPrivate::QSingleBbgRequestPrivate(QSingleBbgRequest* q)
        : QBbgAbstractRequestPrivate(q)
    {}
    QSingleBbgRequestPrivate::QSingleBbgRequestPrivate(QSingleBbgRequest* q, const QSingleBbgRequestPrivate& a)
        : QBbgAbstractRequestPrivate(q,a)
        , m_Field(a.m_Field)
        , m_Overrides(a.m_Overrides)
    {}
    QSingleBbgRequestPrivate& QSingleBbgRequestPrivate::operator=(const QSingleBbgRequestPrivate& a)
    {
        QBbgAbstractRequestPrivate::operator=(a);
        m_Field = a.m_Field;
        m_Overrides = a.m_Overrides;
        return *this;
    }
    void QSingleBbgRequest::SetOverrides(const Overrides& Overr)
    {
        Q_D(QSingleBbgRequest);
        ClearOverrides();
        for (auto i = Overr.constBegin(); i != Overr.constEnd(); i++) {
            if (i.value().isNull()) continue;
            if (i.key().isEmpty()) continue;
            QString TempKey = i.key().simplified().toUpper();
            TempKey.replace(QChar(' '), QChar('_'));
            d->m_Overrides.insert(TempKey, i.value());
        }
    }
    void QSingleBbgRequest::SetOverride(QString Name, const QVariant& Value)
    {
        Q_D(QSingleBbgRequest);
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
    void QSingleBbgRequest::ClearOverrides()
    {
        Q_D(QSingleBbgRequest);
        d->m_Overrides.clear();
    }
    bool QSingleBbgRequest::SameOverrides(const QSingleBbgRequest& a)const
    {
        Q_D(const QSingleBbgRequest);
        return d->SameOverrides(*(a.d_func()));
    }
    bool QSingleBbgRequestPrivate::SameOverrides(const QSingleBbgRequestPrivate& a)const
    {
        return m_Overrides == a.m_Overrides;
    }

    bool QSingleBbgRequest::IsValidReq() const
    {
        Q_D(const QSingleBbgRequest);
        return
            !d->m_Field.isEmpty()
            && d->m_Security.isValid()
            ;
    }

    bool QSingleBbgRequestPrivate::operator==(const QSingleBbgRequestPrivate& a) const
    {
        if (
            (m_Security != a.m_Security)
            || (m_Field != a.m_Field)
            || (m_RqType != a.m_RqType)
            )
            return false;
        return m_Overrides == a.m_Overrides;
    }
    bool QSingleBbgRequest::operator==(const QSingleBbgRequest& a) const
    {
        Q_D(const QSingleBbgRequest);
        return d->operator==(*(a.d_func()));
    }
    const QString& QSingleBbgRequest::GetField() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Field;
    }
    const Overrides& QSingleBbgRequest::GetOverrides() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Overrides;
    }

    QBbgLib::QSingleBbgRequest::QSingleBbgRequest()
        :QBbgAbstractRequest(new QSingleBbgRequestPrivate(this))
    {}

    QBbgLib::QSingleBbgRequest::QSingleBbgRequest(const QSingleBbgRequest& a)
        : QBbgAbstractRequest(new QSingleBbgRequestPrivate(this, *(a.d_func())))
    {}

    QSingleBbgRequest& QBbgLib::QSingleBbgRequest::operator=(const QSingleBbgRequest& a)
    {
        Q_D(QSingleBbgRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
}