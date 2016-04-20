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

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/
#include "QBbgIntradayTickResponse.h"
#include "private/QBbgIntradayTickResponse_p.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgIntradayTickResponse::~QBbgIntradayTickResponse() = default;
    QBbgIntradayTickResponsePrivate::~QBbgIntradayTickResponsePrivate() = default;
    QBbgIntradayTickResponse::QBbgIntradayTickResponse()
        :QBbgAbstractIntradayResponse(new QBbgIntradayTickResponsePrivate(this))
    {}

    QBbgIntradayTickResponse::QBbgIntradayTickResponse(QBbgIntradayTickResponsePrivate* dp)
        : QBbgAbstractIntradayResponse(dp)
    {}

    QBbgIntradayTickResponse::QBbgIntradayTickResponse(const QBbgIntradayTickResponse& other)
        : QBbgAbstractIntradayResponse(new QBbgIntradayTickResponsePrivate(this, *(other.d_func())))
    {}

    QBbgIntradayTickResponse& QBbgIntradayTickResponse::operator=(const QBbgIntradayTickResponse& other)
    {
        Q_D(QBbgIntradayTickResponse);
        d->operator=(*(other.d_func()));
        return *this;
    }
    QBbgIntradayTickResponsePrivate::QBbgIntradayTickResponsePrivate(QBbgIntradayTickResponse* q)
        :QBbgAbstractIntradayResponsePrivate(q, QBbgAbstractResponse::ResponseType::IntraDayTickResponse)
    {}

    QBbgIntradayTickResponsePrivate::QBbgIntradayTickResponsePrivate(QBbgIntradayTickResponse* q, const QBbgIntradayTickResponsePrivate& other)
        : QBbgAbstractIntradayResponsePrivate(q, other)
        , m_conditionCode(other.m_conditionCode)
        , m_exchangeCode(other.m_exchangeCode)
        , m_type(other.m_type)
        , m_micCode(other.m_micCode)
        , m_brokerBuyCode(other.m_brokerBuyCode)
        , m_brokerSellCode(other.m_brokerSellCode)
        , m_rpsCode(other.m_rpsCode)
    {}

    QBbgIntradayTickResponsePrivate& QBbgIntradayTickResponsePrivate::operator=(const QBbgIntradayTickResponsePrivate& other)
    {
        QBbgAbstractIntradayResponsePrivate::operator=(other);
        m_conditionCode = other.m_conditionCode;
        m_exchangeCode = other.m_exchangeCode;
        m_type = other.m_type;
        m_micCode = other.m_micCode;
        m_brokerBuyCode = other.m_brokerBuyCode;
        m_brokerSellCode = other.m_brokerSellCode;
        m_rpsCode = other.m_rpsCode;
        return *this;
    }

    void QBbgIntradayTickResponse::addValue(const QDateTime& dt, double val, double siz, const QString& cC, const QString& eC, const QString& mC, const QString& bbC, const QString& bsC, const QString& rC)
    {
        QBbgAbstractIntradayResponse::addValue(dt, val);
        Q_D(QBbgIntradayTickResponse);
        d->m_size.append(siz);
        d->m_conditionCode.append(cC);
        d->m_exchangeCode.append(eC);
        d->m_micCode.append(mC);
        d->m_brokerBuyCode.append(bbC);
        d->m_brokerSellCode.append(bsC);
        d->m_rpsCode.append(rC);
    }

    void QBbgIntradayTickResponse::clear()
    {
        QBbgAbstractIntradayResponse::clear();
        Q_D(QBbgIntradayTickResponse);
        d->m_conditionCode.clear();
        d->m_exchangeCode.clear();
        d->m_micCode.clear();
        d->m_brokerBuyCode.clear();
        d->m_brokerSellCode.clear();
        d->m_rpsCode.clear();
        d->m_size.clear();
    }

    void QBbgIntradayTickResponse::removeEmptyLists()
    {
        Q_D(QBbgIntradayTickResponse);
        if(!hasConditionCode())
            d->m_conditionCode.clear();
        if (!hasExchangeCode())
            d->m_exchangeCode.clear();
        if (!hasBicMicCode())
            d->m_micCode.clear();
        if (!hasBrokerBuyCode())
            d->m_brokerBuyCode.clear();
        if (!hasBrokerSellCode())
            d->m_brokerSellCode.clear();
        if (!hasRpsCode())
            d->m_rpsCode.clear();
    }

    bool QBbgIntradayTickResponse::isEmpty() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_time.isEmpty();
    }

    QBbgAbstractIntradayRequest::EventType QBbgIntradayTickResponse::type() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_type;
    }

    double QBbgIntradayTickResponse::tickSize(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_size.value(period, 0.0);
    }

    QString QBbgIntradayTickResponse::conditionCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_conditionCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasConditionCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_conditionCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    QString QBbgIntradayTickResponse::exchangeCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_exchangeCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasExchangeCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_exchangeCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    QString QBbgIntradayTickResponse::bicMicCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_micCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasBicMicCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_micCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    QString QBbgIntradayTickResponse::brokerBuyCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_brokerBuyCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasBrokerBuyCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_brokerBuyCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    QString QBbgIntradayTickResponse::brokerSellCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_brokerSellCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasBrokerSellCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_brokerSellCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    QString QBbgIntradayTickResponse::rpsCode(int period) const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->m_rpsCode.value(period);
    }

    bool QBbgIntradayTickResponse::hasRpsCode() const
    {
        Q_D(const QBbgIntradayTickResponse);
        return d->genericHas(d->m_rpsCode, [](const QString& val)->bool {return !val.isEmpty(); });
    }

    void QBbgIntradayTickResponse::setType(const QBbgAbstractIntradayRequest::EventType& val)
    {
        Q_D(QBbgIntradayTickResponse);
        d->m_type = val;
    }
    void QBbgIntradayTickResponse::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgIntradayTickResponse);
        QBbgAbstractResponse::saveToStream(stream);
        stream
            << d->m_size
            << d->m_conditionCode
            << d->m_exchangeCode
            << d->m_micCode
            << d->m_brokerBuyCode
            << d->m_brokerSellCode
            << d->m_rpsCode
            << static_cast<std::underlying_type<QBbgAbstractIntradayRequest::EventType>::type>(d->m_type)
            ;
    }

    void QBbgIntradayTickResponse::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgIntradayTickResponse);
        std::underlying_type<QBbgAbstractIntradayRequest::EventType>::type tempTyp;
        QBbgAbstractResponse::loadFromStream(stream);
        stream
            >> d->m_size
            >> d->m_conditionCode
            >> d->m_exchangeCode
            >> d->m_micCode
            >> d->m_brokerBuyCode
            >> d->m_brokerSellCode
            >> d->m_rpsCode
            >> tempTyp
            ;
        d->m_type = static_cast<QBbgAbstractIntradayRequest::EventType>(tempTyp);
    }


    void QBbgAbstractIntradayRequest::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgAbstractIntradayRequest);
        QBbgAbstractRequest::loadFromStream(stream);
        std::underlying_type<EventType>::type tempTyp;
        stream >> d->m_startDate >> d->m_endDate >> tempTyp;
        d->m_eventType = static_cast<EventType>(tempTyp);
    }
}