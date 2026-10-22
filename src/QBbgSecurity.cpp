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
#include <QIODevice>
#include <QHash>
#include <QJsonValue>
namespace QBbgLib {

QBbgSecurityPrivate::~QBbgSecurityPrivate() = default;
QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity *q)
    : q_ptr(q)
    , m_Extension(QBbgSecurity::YellowKeys::Invalid)
{ }
QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity *q, const QBbgSecurityPrivate &other)
    : q_ptr(q)
    , m_Name(other.m_Name)
    , m_Extension(other.m_Extension)
    , m_Exchange(other.m_Exchange)
    , m_PricingSource(other.m_PricingSource)
{ }

void QBbgSecurity::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgSecurity);
    stream << d->m_Name << qint32(d->m_Extension) << d->m_Exchange << d->m_PricingSource;
}

void QBbgSecurity::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgSecurity);
    qint32 tempExt;
    stream >> d->m_Name >> tempExt >> d->m_Exchange >> d->m_PricingSource;
    d->m_Extension = static_cast<YellowKeys>(tempExt);
}

QJsonObject QBbgSecurity::toJsonObject() const
{
    Q_D(const QBbgSecurity);
    return QJsonObject{{QStringLiteral("Name"), d->m_Name},
                       {QStringLiteral("Extension"), int(d->m_Extension)},
                       {QStringLiteral("Exchange"), d->m_Exchange},
                       {QStringLiteral("PricingSource"), d->m_PricingSource}};
}

bool QBbgSecurity::fromJsonObject(const QJsonObject &obj)
{
    Q_D(QBbgSecurity);
    int tempExt;
    QString tempName, tempExchange;
    QJsonValue tempValue;
    tempValue = obj.value(QStringLiteral("Name"));
    if (!tempValue.isString())
        return false;
    tempName = tempValue.toString();
    tempValue = obj.value(QStringLiteral("Extension"));
    if (!tempValue.isDouble())
        return false;
    tempExt = tempValue.toInt();
    tempValue = obj.value(QStringLiteral("Exchange"));
    if (!tempValue.isString())
        return false;
    tempExchange = tempValue.toString();
    tempValue = obj.value(QStringLiteral("PricingSource"));
    if (!tempValue.isString())
        return false;
    d->m_Name = tempName;
    d->m_Extension = static_cast<YellowKeys>(tempExt);
    d->m_Exchange = tempExchange;
    d->m_PricingSource = tempValue.toString();
    return true;
}

QBbgSecurity::QBbgSecurity()
    : d_ptr(new QBbgSecurityPrivate(this))
{ }
QBbgSecurity::QBbgSecurity(const QBbgSecurity &other)
    : d_ptr(new QBbgSecurityPrivate(this, *(other.d_ptr)))
{ }
QBbgSecurity::QBbgSecurity(const QString &SecName, YellowKeys SecKey)
    : d_ptr(new QBbgSecurityPrivate(this))
{
    setName(SecName);
    setExtension(SecKey);
}
QBbgSecurity::QBbgSecurity(const QString &SecString)
    : d_ptr(new QBbgSecurityPrivate(this))
{
    setFullName(SecString);
}
QBbgSecurity::~QBbgSecurity()
{
    delete d_ptr;
}
const QString &QBbgSecurity::name() const
{
    Q_D(const QBbgSecurity);
    return d->m_Name;
}
void QBbgSecurity::setName(const QString &val)
{
    Q_D(QBbgSecurity);
    d->m_Name = val.simplified().toUpper();
}
const QString &QBbgSecurity::exchange() const
{
    Q_D(const QBbgSecurity);
    return d->m_Exchange;
}
void QBbgSecurity::setExchange(const QString &val)
{
    Q_D(QBbgSecurity);
    d->m_Exchange = val.simplified();
}
const QString &QBbgSecurity::pricingSource() const
{
    Q_D(const QBbgSecurity);
    return d->m_PricingSource;
}
void QBbgSecurity::setPricingSource(const QString &val)
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
    return d->m_Extension != YellowKeys::Invalid && !(d->m_Name.isEmpty());
}
QString QBbgSecurity::yellowKeyToString(QBbgSecurity::YellowKeys a)
{
    switch (a) {
    case YellowKeys::Govt:
        return QStringLiteral("Govt");
    case YellowKeys::Corp:
        return QStringLiteral("Corp");
    case YellowKeys::Mtge:
        return QStringLiteral("Mtge");
    case YellowKeys::MMkt:
        return QStringLiteral("MMkt");
    case YellowKeys::Muni:
        return QStringLiteral("Muni");
    case YellowKeys::Pfd:
        return QStringLiteral("Pfd");
    case YellowKeys::Equity:
        return QStringLiteral("Equity");
    case YellowKeys::Comdty:
        return QStringLiteral("Comdty");
    case YellowKeys::Index:
        return QStringLiteral("Index");
    case YellowKeys::Curncy:
        return QStringLiteral("Curncy");
    case YellowKeys::Client:
        return QStringLiteral("Client");
    // case ticker: return "ticker";
    case YellowKeys::cusip:
        return QStringLiteral("cusip");
    case YellowKeys::wpk:
        return QStringLiteral("wpk");
    case YellowKeys::isin:
        return QStringLiteral("isin");
    case YellowKeys::buid:
        return QStringLiteral("buid");
    case YellowKeys::sedol1:
        return QStringLiteral("sedol1");
    case YellowKeys::sedol2:
        return QStringLiteral("sedol2");
    case YellowKeys::sicovam:
        return QStringLiteral("sicovam");
    case YellowKeys::common:
        return QStringLiteral("common");
    case YellowKeys::bsid:
        return QStringLiteral("bsid");
    case YellowKeys::svm:
        return QStringLiteral("svm");
    case YellowKeys::cins:
        return QStringLiteral("cins");
    case YellowKeys::cats:
        return QStringLiteral("cats");
    case YellowKeys::bbgid:
        return QStringLiteral("bbgid");
    default:
        return QString();
    }
}
QBbgSecurity::YellowKeys QBbgSecurity::stringToYellowKey(QString a)
{
    a = a.toLower().trimmed();
    if (a == QStringLiteral("govt"))
        return YellowKeys::Govt;
    else if (a == QStringLiteral("corp"))
        return YellowKeys::Corp;
    else if (a == QStringLiteral("mtge"))
        return YellowKeys::Mtge;
    else if (a == QStringLiteral("mmkt"))
        return YellowKeys::MMkt;
    else if (a == QStringLiteral("muni"))
        return YellowKeys::Muni;
    else if (a == QStringLiteral("pfd"))
        return YellowKeys::Pfd;
    else if (a == QStringLiteral("equity"))
        return YellowKeys::Equity;
    else if (a == QStringLiteral("comdty"))
        return YellowKeys::Comdty;
    else if (a == QStringLiteral("index"))
        return YellowKeys::Index;
    else if (a == QStringLiteral("curncy"))
        return YellowKeys::Curncy;
    else if (a == QStringLiteral("client"))
        return YellowKeys::Client;
    // else if (a == "ticker") return ticker;
    else if (a == QStringLiteral("cusip"))
        return YellowKeys::cusip;
    else if (a == QStringLiteral("wpk"))
        return YellowKeys::wpk;
    else if (a == QStringLiteral("isin"))
        return YellowKeys::isin;
    else if (a == QStringLiteral("buid"))
        return YellowKeys::buid;
    else if (a == QStringLiteral("sedol1"))
        return YellowKeys::sedol1;
    else if (a == QStringLiteral("sedol2"))
        return YellowKeys::sedol2;
    else if (a == QStringLiteral("sicovam"))
        return YellowKeys::sicovam;
    else if (a == QStringLiteral("common"))
        return YellowKeys::common;
    else if (a == QStringLiteral("bsid"))
        return YellowKeys::bsid;
    else if (a == QStringLiteral("svm"))
        return YellowKeys::svm;
    else if (a == QStringLiteral("cins"))
        return YellowKeys::cins;
    else if (a == QStringLiteral("cats"))
        return YellowKeys::cats;
    else if (a == QStringLiteral("bbgid"))
        return YellowKeys::bbgid;
    else
        return YellowKeys::Invalid;
}

QString QBbgSecurity::fullName() const
{
    QString Result;
    if (!isValid())
        return Result;
    Q_D(const QBbgSecurity);
    if (static_cast<std::underlying_type<QBbgSecurity::YellowKeys>::type>(d->m_Extension) & FirstPrefix)
        Result += QLatin1Char('/') + yellowKeyToString(d->m_Extension) + QLatin1Char('/');
    Result += d->m_Name;
    if (!(d->m_PricingSource.isEmpty()))
        Result += QLatin1Char('@') + d->m_PricingSource;
    if (!(static_cast<std::underlying_type<QBbgSecurity::YellowKeys>::type>(d->m_Extension) & FirstPrefix)) {
        Result += QLatin1Char(' ');
        if (!(d->m_Exchange.isEmpty()))
            Result += d->m_Exchange + QLatin1Char(' ');
        Result += yellowKeyToString(d->m_Extension);
    }
    return Result;
}

void QBbgSecurity::setFullName(QString val)
{
    if (!val.isEmpty()) {
        val = val.simplified();
        if (val.at(0) == QLatin1Char('/')) {
            setExtension(stringToYellowKey(val.mid(1, val.indexOf(QLatin1Char('/'), 1))));
            val = val.mid(val.indexOf(QLatin1Char('/'), 1) + 1);
        } else {
            setExtension(stringToYellowKey(val.right(val.size() - val.lastIndexOf(QLatin1Char(' ')))));
            val = val.left(val.lastIndexOf(QLatin1Char(' ')));
        }
        static QRegularExpression priceSourceRegExp(QStringLiteral("\\s@(\\S+)(?:\\s|$)"));
        QRegularExpressionMatch matchRes = priceSourceRegExp.match(val);
        if (matchRes.hasMatch()) {
            setPricingSource(matchRes.captured(1));
            static QRegularExpression tempRx(QStringLiteral("@\\S+"));
            val.replace(tempRx, QString());
        }
        setName(val);
    }
}

bool QBbgSecurity::operator!=(const QBbgSecurity &other) const
{
    return !operator==(other);
}

bool QBbgSecurity::operator==(const QBbgSecurity &other) const
{
    Q_D(const QBbgSecurity);
    return d->operator==(*(other.d_func()));
}

QBbgSecurity &QBbgSecurity::operator=(const QBbgSecurity &other)
{
    Q_D(QBbgSecurity);
    d->operator=(*(other.d_func()));
    return *this;
}

bool QBbgSecurityPrivate::operator==(const QBbgSecurityPrivate &other) const
{
    return m_Name == other.m_Name && m_Extension == other.m_Extension && m_Exchange == other.m_Exchange && m_PricingSource == other.m_PricingSource;
}
QBbgSecurityPrivate &QBbgSecurityPrivate::operator=(const QBbgSecurityPrivate &other)
{
    m_Name = other.m_Name;
    m_Extension = other.m_Extension;
    m_Exchange = other.m_Exchange;
    m_PricingSource = other.m_PricingSource;
    return *this;
}

TypeForQHash qHash(const QBbgLib::QBbgSecurity &key, TypeForQHash seed)
{
    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << key;
    }
    return qHash(data, seed);
}
}

QDataStream &operator<<(QDataStream &stream, const QBbgLib::QBbgSecurity &obj)
{
    obj.saveToStream(stream);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QBbgLib::QBbgSecurity &obj)
{
    obj.loadFromStream(stream);
    return stream;
}
