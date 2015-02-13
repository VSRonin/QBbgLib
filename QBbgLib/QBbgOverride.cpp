#include "QBbgOverride.h"
#include "QBbgOverride_p.h"
#include <QDate>
#include <QTime>
#include <blpapi_session.h>
namespace QBbgLib {
    QBbgOverridePrivate::QBbgOverridePrivate(QBbgOverride* q)
        : q_ptr(q)
    {}
    QBbgOverridePrivate::QBbgOverridePrivate(QBbgOverride* q, const QBbgOverridePrivate& other)
        : q_ptr(q)
        , m_Overrides(other.m_Overrides)
    {}
    QBbgOverridePrivate& QBbgOverridePrivate::operator=(const QBbgOverridePrivate& other)
    {
        m_Overrides = other.m_Overrides;
        return *this;
    }
    QBbgOverride::QBbgOverride()
        :d_ptr(new QBbgOverridePrivate(this))
    {}
    QBbgOverride::QBbgOverride(const QBbgOverride& other)
        : d_ptr(new QBbgOverridePrivate(this,*(other.d_func())))
    {}
    QBbgOverride::QBbgOverride(QBbgOverridePrivate* d)
        : d_ptr(d)
    {}
    QBbgOverride& QBbgOverride::operator=(const QBbgOverride& other)
    {
        Q_D(QBbgOverride);
        d->operator=(*(other.d_func()));
        return *this;
    }
    QBbgOverride::~QBbgOverride()
    {
        delete d_ptr;
    }
    void QBbgOverride::clear()
    {
        Q_D(QBbgOverride);
        d->m_Overrides.clear();
    }
    qint32 QBbgOverride::size()
    {
        Q_D(const QBbgOverride);
        return d->m_Overrides.size();
    }
    bool QBbgOverride::contains(const QString& Name) const
    {
        Q_D(const QBbgOverride);
        return d->m_Overrides.contains(Name);
    }
    bool QBbgOverride::isEmpty() const
    {
        Q_D(const QBbgOverride);
        return d->m_Overrides.isEmpty();
    }
    QList<QString> QBbgOverride::getKeys() const
    {
        Q_D(const QBbgOverride);
        return d->m_Overrides.keys();
    }
    bool QBbgOverride::operator==(const QBbgOverride& other) const
    {
        Q_D(const QBbgOverride);
        return d->m_Overrides==other.d_func()->m_Overrides;
    }
    bool QBbgOverride::operator!=(const QBbgOverride& other) const
    {
        return !operator==(other);
    }
    QString& QBbgOverride::operator[](const QString& Name)
    {
        Q_D(QBbgOverride);
        return  d->m_Overrides[Name];
    }
    const QString QBbgOverride::operator[](const QString& Name) const
    {
        Q_D(const QBbgOverride);
        return  d->m_Overrides[Name];
    }
    QString QBbgOverride::overrideValue(const QString& Name) const
    {
        Q_D(const QBbgOverride);
        return  d->m_Overrides.value(Name, QString());
    }
    void QBbgOverride::setOverride(QString Name, const QString& val)
    {
        Q_D(QBbgOverride);
        Name = Name.simplified().toUpper();
        Name.replace(QChar(' '), QChar('_'));
        QHash<QString, QString>::iterator iter = d->m_Overrides.find(Name);
        if (val.isEmpty()) {
            if (iter != d->m_Overrides.end())
                d->m_Overrides.erase(iter);
            return;
        }
        if (iter == d->m_Overrides.end()) {
            if (d->m_Overrides.size()<100) //Bloomberg sets a hard limit of 100 overrides
                d->m_Overrides.insert(Name, val);
        }
        else {
            iter.value() = val;
        }
    }
    void QBbgOverride::setOverride(const QString& Name, const QDate& val)
    {
        if (val.isNull())
            setOverride(Name, QString());
        else
            setOverride(Name, val.toString("yyyyMMdd"));
    }
    void QBbgOverride::setOverride(const QString& Name, double val)
    {
        setOverride(Name, QString::number(val,'f'));
    }

    void QBbgOverride::setOverride(const QString& Name, qint32 val)
    {
        setOverride(Name, QString::number(val));
    }
    void QBbgOverride::setOverride(const QString& Name, qint64 val)
    {
        setOverride(Name, QString::number(val));
    }

    void QBbgOverride::setOverride(const QString& Name, const QTime& val)
    {
        if (val.isNull())
            setOverride(Name, QString());
        else
            setOverride(Name, val.toString("HHmmss"));
    }
    void QBbgOverride::setOverride(const QString& Name, bool val)
    {
        setOverride(Name, val ? QString("Y") : QString("N"));
    }

    void QBbgOverride::addOverrideToRequest(BloombergLP::blpapi::Request& rq) const
    {
        Q_D(const QBbgOverride);
        for (QHash<QString, QString>::const_iterator i = d->m_Overrides.constBegin(); i != d->m_Overrides.constEnd(); ++i) {
            BloombergLP::blpapi::Element CurrentOverrides = rq.getElement("overrides").appendElement();
            CurrentOverrides.setElement("fieldId", i.key().toLatin1().data());
            CurrentOverrides.setElement("value", i.value().toLatin1().data());
        }
    }

}