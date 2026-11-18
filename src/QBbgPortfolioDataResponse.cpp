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

#include "QBbgPortfolioDataResponse.h"
#include "private/QBbgPortfolioDataResponse_p.h"
#include <QDataStream>
#include <QJsonArray>
namespace QBbgLib {
QBbgPortfolioDataResponse::~QBbgPortfolioDataResponse() = default;
QBbgPortfolioDataResponsePrivate::~QBbgPortfolioDataResponsePrivate() = default;
QBbgPortfolioDataResponsePrivate::QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse *q, const QBbgPortfolioDataResponsePrivate &other)
    : QBbgAbstractFieldResponsePrivate(q, other)
    , m_Security(other.m_Security)
    , m_Position(other.m_Position)
    , m_MarketValue(other.m_MarketValue)
    , m_Cost(other.m_Cost)
    , m_CostDate(other.m_CostDate)
    , m_CostFx(other.m_CostFx)
    , m_Weight(other.m_Weight)
{ }

QBbgPortfolioDataResponsePrivate::QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse *q)
    : QBbgAbstractFieldResponsePrivate(q, QBbgAbstractResponse::ResponseType::PortfolioDataResponse)
{ }

QBbgPortfolioDataResponsePrivate &QBbgPortfolioDataResponsePrivate::operator=(const QBbgPortfolioDataResponsePrivate &other)
{
    QBbgAbstractFieldResponsePrivate::operator=(other);
    m_Security = other.m_Security;
    m_Position = other.m_Position;
    m_MarketValue = other.m_MarketValue;
    m_Cost = other.m_Cost;
    m_CostDate = other.m_CostDate;
    m_CostFx = other.m_CostFx;
    m_Weight = other.m_Weight;
    return *this;
}
double QBbgPortfolioDataResponsePrivate::positionMultiplier(QBbgLib::QBbgSecurity::YellowKeys val) const
{
    switch (val) {
    case QBbgLib::QBbgSecurity::YellowKeys::Govt:
    case QBbgLib::QBbgSecurity::YellowKeys::Corp:
    case QBbgLib::QBbgSecurity::YellowKeys::Mtge:
    case QBbgLib::QBbgSecurity::YellowKeys::Curncy:
    case QBbgLib::QBbgSecurity::YellowKeys::Muni:
        return 1000.0;
    case QBbgLib::QBbgSecurity::YellowKeys::Pfd:
    case QBbgLib::QBbgSecurity::YellowKeys::Equity:
        return 1.0;
    case QBbgLib::QBbgSecurity::YellowKeys::MMkt:
    case QBbgLib::QBbgSecurity::YellowKeys::Comdty:
    case QBbgLib::QBbgSecurity::YellowKeys::Index:
        Q_ASSERT_X(false, "getMultipier()", "Unspecifed multiplier for extension");
        return 1.0;
    default:
        Q_ASSERT_X(false, "getMultipier()", "Invalid Extension");
        return 0.0;
    }
}

int QBbgPortfolioDataResponse::size() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Security.size();
}

QBbgSecurity QBbgPortfolioDataResponse::security(int index) const
{
    if (index < 0 || index >= size())
        return QBbgSecurity();
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Security.at(static_cast<int>(index));
}

double QBbgPortfolioDataResponse::position(int index) const
{
    if (index < 0 || index >= size() || !hasPosition())
        return 0.0;
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Position.at(static_cast<int>(index));
}

double QBbgPortfolioDataResponse::marketValue(int index) const
{
    if (index < 0 || index >= size() || !hasMarketValue())
        return 0.0;
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_MarketValue.at(static_cast<int>(index));
}

double QBbgPortfolioDataResponse::cost(int index) const
{
    if (index < 0 || index >= size() || !hasCost())
        return 0.0;
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Cost.at(static_cast<int>(index));
}

double QBbgPortfolioDataResponse::costFx(int index) const
{
    if (index < 0 || index >= size() || !hasCostFx())
        return 0.0;
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_CostFx.at(static_cast<int>(index));
}

double QBbgPortfolioDataResponse::weight(int index) const
{
    if (index < 0 || index >= size() || !hasWeight())
        return 0.0;
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Weight.at(static_cast<int>(index));
}

QDate QBbgPortfolioDataResponse::costDate(int index) const
{
    if (index < 0 || index >= size() || !hasCostDate())
        return QDate();
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_CostDate.at(static_cast<int>(index));
}

bool QBbgPortfolioDataResponse::hasPosition() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_Position.isEmpty();
}

bool QBbgPortfolioDataResponse::hasMarketValue() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_MarketValue.isEmpty();
}

bool QBbgPortfolioDataResponse::hasCost() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_Cost.isEmpty();
}

bool QBbgPortfolioDataResponse::hasCostDate() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_CostDate.isEmpty();
}

bool QBbgPortfolioDataResponse::hasCostFx() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_CostFx.isEmpty();
}

bool QBbgPortfolioDataResponse::hasWeight() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return !d->m_Weight.isEmpty();
}

void QBbgPortfolioDataResponse::clear()
{
    Q_D(QBbgPortfolioDataResponse);
    d->m_Security.clear();
    d->m_Position.clear();
    d->m_MarketValue.clear();
    d->m_Cost.clear();
    d->m_CostDate.clear();
    d->m_CostFx.clear();
    d->m_Weight.clear();
}

QBbgPortfolioDataResponse::QBbgPortfolioDataResponse(const QBbgPortfolioDataResponse &other)
    : QBbgAbstractFieldResponse(new QBbgPortfolioDataResponsePrivate(this, *(other.d_func())))
{ }

QBbgPortfolioDataResponse::QBbgPortfolioDataResponse()
    : QBbgAbstractFieldResponse(new QBbgPortfolioDataResponsePrivate(this))
{ }

QBbgPortfolioDataResponse::QBbgPortfolioDataResponse(QBbgPortfolioDataResponsePrivate *dp)
    : QBbgAbstractFieldResponse(dp)
{ }
QBbgPortfolioDataResponse &QBbgPortfolioDataResponse::operator=(const QBbgPortfolioDataResponse &other)
{
    Q_D(QBbgPortfolioDataResponse);
    d->operator=(*(other.d_func()));
    return *this;
}

bool QBbgPortfolioDataResponse::isEmpty() const
{
    Q_D(const QBbgPortfolioDataResponse);
    return d->m_Security.isEmpty();
}
void QBbgPortfolioDataResponse::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgPortfolioDataResponse);
    QBbgAbstractFieldResponse::saveToStream(stream);
    stream << d->m_Security << d->m_Position << d->m_MarketValue << d->m_Cost << d->m_CostDate << d->m_CostFx << d->m_Weight;
}

void QBbgPortfolioDataResponse::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgPortfolioDataResponse);
    QBbgAbstractFieldResponse::loadFromStream(stream);
    stream >> d->m_Security >> d->m_Position >> d->m_MarketValue >> d->m_Cost >> d->m_CostDate >> d->m_CostFx >> d->m_Weight;
}

bool QBbgPortfolioDataResponse::loadFromJsonResponse(const QJsonObject &obj)
{
    const QJsonArray currentFieldArray = obj.value(QStringLiteral("data")).toArray();
    bool oneSent = false;
    for (auto currentField : currentFieldArray) {
        const QJsonObject currentFieldObj = currentField.toObject();
        const QString secString = currentFieldObj.value(QStringLiteral("Security")).toString();
        if (secString.isEmpty())
            continue;
        const bool hasPos = currentFieldObj.contains(QStringLiteral("Position"));
        const bool hasMkVal = currentFieldObj.contains(QStringLiteral("Market Value"));
        const bool haspCst = currentFieldObj.contains(QStringLiteral("Cost"));
        const bool hasCstDt = currentFieldObj.contains(QStringLiteral("Cost Date"));
        const bool hasCstFx = currentFieldObj.contains(QStringLiteral("Cost Fx Rate"));
        const bool hasWei = currentFieldObj.contains(QStringLiteral("Weight"));
        Q_ASSERT((hasPos && size() > 0) == hasPosition());
        Q_ASSERT((hasMkVal && size() > 0) == hasMarketValue());
        Q_ASSERT((haspCst && size() > 0) == hasCost());
        Q_ASSERT((hasCstDt && size() > 0) == hasCostDate());
        Q_ASSERT((hasCstFx && size() > 0) == hasCostFx());
        Q_ASSERT((hasWei && size() > 0) == hasWeight());
        Q_D(QBbgPortfolioDataResponse);
        d->m_Security.append(secString);
        if (hasPos) {
            const double mutilp = d->positionMultiplier(d->m_Security.last().extension());
            d->m_Position.append(currentFieldObj.value(QStringLiteral("Position")).toDouble() * mutilp);
        }
        if (hasMkVal)
            d->m_MarketValue.append(currentFieldObj.value(QStringLiteral("Market Value")).toDouble());
        if (haspCst)
            d->m_Cost.append(currentFieldObj.value(QStringLiteral("Cost")).toDouble());
        if (hasCstDt)
            d->m_CostDate.append(QDate::fromString(currentFieldObj.value(QStringLiteral("Cost Date")).toString(), Qt::ISODate));
        if (hasCstFx)
            d->m_CostFx.append(currentFieldObj.value(QStringLiteral("Cost Fx Rate")).toDouble());
        if (hasWei)
            d->m_Weight.append(currentFieldObj.value(QStringLiteral("Weight")).toDouble());
        oneSent = true;
    }
    return oneSent;
}
}
