/*******************************************************************************\
* This file is part of QBbgLib.                                                 *
*                                                                               *
* QBbgLib is free software : you can redistribute it and / or modify            *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* QBbgLib is distributed in the hope that it will be useful,                    *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                   *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#include "QBbgOverride.h"
#include "private/QBbgOverride_p.h"
#include <QDate>
#include <QTime>
#include <QVariant>
#include <blpapi_session.h>
namespace QBbgLib {

    QBbgOverridePrivate::~QBbgOverridePrivate() = default;
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

    QList<QString> QBbgOverride::getNames() const
    {
        return getKeys();
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
    QString QBbgOverride::operator[](const QString& Name) const
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
            //d->m_Overrides[Name] = val;
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
    void QBbgOverride::setOverride(const QString& Name, quint32 val)
    {
        setOverride(Name, QString::number(val));
    }

    void QBbgOverride::setOverride(const QString& Name, qint64 val)
    {
        setOverride(Name, QString::number(val));
    }
    void QBbgOverride::setOverride(const QString& Name, quint64 val)
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

    void QBbgOverride::setOverride(QString Name, const char *const val)
    {
        return setOverride(Name, QString(val));
    }

    void QBbgOverride::setOverride(const QString& Name, const QVariant& val)
    {
        switch (val.type()){
        case QMetaType::QString:
            return setOverride(Name, val.toString());
        case QMetaType::QDate:
            return setOverride(Name, val.toDate());
        case QMetaType::QTime:
            return setOverride(Name, val.toTime());
        case QMetaType::Double:
            return setOverride(Name, val.toDouble());
        case QMetaType::Int:
            return setOverride(Name, val.toInt());
        case QMetaType::LongLong:
            return setOverride(Name, val.toLongLong());
        case QMetaType::UInt:
            return setOverride(Name, val.toUInt());
        case QMetaType::ULongLong:
            return setOverride(Name, val.toULongLong());
        default:
            Q_UNREACHABLE(); // Invalid override type
        }
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
