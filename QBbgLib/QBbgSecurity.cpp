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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/ >.             *
*                                                                               *
\*******************************************************************************/

#include "QBbgSecurity.h"
#include "private/QBbgSecurity_p.h"
#include <QRegularExpression>
#include <QDataStream>
#include <QHash>
namespace QBbgLib {

    QBbgSecurityPrivate::~QBbgSecurityPrivate() = default;
    QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity* q)
        : q_ptr(q)
        , m_Extension(QBbgSecurity::Invalid)
    {}
    QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity* q, const QBbgSecurityPrivate& other)
        : q_ptr(q)
        , m_Name(other.m_Name)
        , m_Extension(other.m_Extension)
        , m_Exchange(other.m_Exchange)
        , m_PricingSource(other.m_PricingSource)
    {}

    void QBbgSecurity::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgSecurity);
        stream << d->m_Name << qint32(d->m_Extension) << d->m_Exchange << d->m_PricingSource;
    }

    void QBbgSecurity::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgSecurity);
        qint32 tempExt;
        stream >> d->m_Name >> tempExt >> d->m_Exchange >> d->m_PricingSource;
        d->m_Extension = static_cast<YellowKeys>(tempExt);
    }

    QBbgSecurity::QBbgSecurity()
        :d_ptr(new QBbgSecurityPrivate(this))
    {}
    QBbgSecurity::QBbgSecurity(const QBbgSecurity& other)
        : d_ptr(new QBbgSecurityPrivate(this,*(other.d_ptr)))
    {}
    QBbgSecurity::QBbgSecurity(const QString& SecName, YellowKeys SecKey)
        : d_ptr(new QBbgSecurityPrivate(this))
    {
        setName(SecName);
        setExtension(SecKey);
    }
    QBbgSecurity::QBbgSecurity(const QString& SecString)
        :d_ptr(new QBbgSecurityPrivate(this))
    {
        setFullName(SecString);
    }
    QBbgSecurity::~QBbgSecurity()
    {
        delete d_ptr;
    }
    const QString& QBbgSecurity::name() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Name;
    }
    void QBbgSecurity::setName(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_Name = val.simplified().toUpper();
    }
    const QString& QBbgSecurity::exchange() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Exchange;
    }
    void QBbgSecurity::setExchange(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_Exchange = val.simplified();
    }
    const QString& QBbgSecurity::pricingSource() const
    {
        Q_D(const QBbgSecurity);
        return d->m_PricingSource;
    }
    void QBbgSecurity::setPricingSource(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_PricingSource = val.trimmed();
    }
    QBbgSecurity::YellowKeys QBbgSecurity::extension() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Extension;
    }
    void QBbgSecurity::setExtension(YellowKeys val)
    {
        Q_D(QBbgSecurity);
        d->m_Extension = val;
    }
    bool QBbgSecurity::isValid() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Extension != Invalid && !(d->m_Name.isEmpty());
    }
    QString QBbgSecurity::yellowKeyToString(QBbgSecurity::YellowKeys a)
    {
        switch (a) {
        case Govt: return "Govt";
        case Corp: return "Corp";
        case Mtge: return "Mtge";
        case MMkt: return "MMkt";
        case Muni: return "Muni";
        case Pfd: return "Pfd";
        case Equity: return "Equity";
        case Comdty: return "Comdty";
        case Index: return "Index";
        case Curncy: return "Curncy";
        case Client: return "Client";
        //case ticker: return "ticker";
        case cusip: return "cusip";
        case wpk: return "wpk";
        case isin: return "isin";
        case buid: return "buid";
        case sedol1: return "sedol1";
        case sedol2: return "sedol2";
        case sicovam: return "sicovam";
        case common: return "common";
        case bsid: return "bsid";
        case svm: return "svm";
        case cins: return "cins";
        case cats: return "cats";
        case bbgid: return "bbgid";
        default: return QString();
        }
    }
    QBbgSecurity::YellowKeys QBbgSecurity::stringToYellowKey(QString a)
    {
        a = a.toLower().trimmed();
        if (a == "govt") return Govt;
        else if (a == "corp") return Corp;
        else if (a == "mtge") return Mtge;
        else if (a == "mmkt") return MMkt;
        else if (a == "muni") return Muni;
        else if (a == "pfd") return Pfd;
        else if (a == "equity") return Equity;
        else if (a == "comdty") return Comdty;
        else if (a == "index") return Index;
        else if (a == "curncy") return Curncy;
        else if (a == "client") return Client;
        //else if (a == "ticker") return ticker;
        else if (a == "cusip") return cusip;
        else if (a == "wpk") return wpk;
        else if (a == "isin") return isin;
        else if (a == "buid") return buid;
        else if (a == "sedol1") return sedol1;
        else if (a == "sedol2") return sedol2;
        else if (a == "sicovam") return sicovam;
        else if (a == "common") return common;
        else if (a == "bsid") return bsid;
        else if (a == "svm") return svm;
        else if (a == "cins") return cins;
        else if (a == "cats") return cats;
        else if (a == "bbgid") return bbgid;
        else return Invalid;
    }

    QString QBbgSecurity::fullName() const
    {
        QString Result;
        if (!isValid())
            return Result;
        Q_D(const QBbgSecurity);
        if (d->m_Extension & FirstPrefix)
            Result += '/' + yellowKeyToString(d->m_Extension) + '/';
        Result += d->m_Name;
        if (!(d->m_PricingSource.isEmpty()))
            Result += '@' + d->m_PricingSource;
        if (!(d->m_Extension & FirstPrefix)) {
            Result += ' ';
            if (!(d->m_Exchange.isEmpty()))
                Result += d->m_Exchange + ' ';
            Result += yellowKeyToString(d->m_Extension);
        }
        return Result;
    }

    void QBbgSecurity::setFullName(QString val)
    {
        if (!val.isEmpty()) {
            val = val.simplified();
            if (val.at(0) == '/') {
                setExtension(stringToYellowKey(val.mid(1, val.indexOf('/', 1))));
                val = val.mid(val.indexOf('/', 1) + 1);
            }
            else {
                setExtension(stringToYellowKey(val.right(val.size() - val.lastIndexOf(' '))));
                val = val.left(val.lastIndexOf(' '));
            }
            QRegularExpression priceSourceRegExp("\\s@(\\S+)(?:\\s|$)");
            QRegularExpressionMatch matchRes = priceSourceRegExp.match(val);
            if (matchRes.hasMatch()) {
                setPricingSource(matchRes.captured(1));
                val.replace(QRegularExpression("@\\S+"), QString());
            }
            setName(val);
        }
    }

    bool QBbgSecurity::operator!=(const QBbgSecurity& other) const
    {
        return !operator==(other);
    }

    bool QBbgSecurity::operator==(const QBbgSecurity& other) const
    {
        Q_D(const QBbgSecurity);
        return d->operator==(*(other.d_func()));
    }

    QBbgSecurity& QBbgSecurity::operator=(const QBbgSecurity& other)
    {
        Q_D(QBbgSecurity);
        d->operator=(*(other.d_func()));
        return *this;
    }

    bool QBbgSecurityPrivate::operator==(const QBbgSecurityPrivate& other) const
    {
        return
            m_Name == other.m_Name
            && m_Extension == other.m_Extension
            && m_Exchange == other.m_Exchange
            && m_PricingSource == other.m_PricingSource
            ;
    }
    QBbgSecurityPrivate& QBbgSecurityPrivate::operator=(const QBbgSecurityPrivate& other)
    {
        m_Name = other.m_Name;
        m_Extension = other.m_Extension;
        m_Exchange = other.m_Exchange;
        m_PricingSource = other.m_PricingSource;
        return *this;
    }
}

uint qHash(const QBbgLib::QBbgSecurity&key, uint seed)
{
    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << key;
    }
    return qHash(data, seed);
}

QDataStream& operator<<(QDataStream& stream, const QBbgLib::QBbgSecurity& obj)
{
    obj.saveToStream(stream);
    return stream;
}

QDataStream& operator>>(QDataStream& stream, QBbgLib::QBbgSecurity& obj)
{
    obj.loadFromStream(stream);
    return stream;
}
