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

#include "QBbgAbstractIntradayRequest.h"
#include "Private/QBbgAbstractIntradayRequest_p.h"
namespace QBbgLib {
    QBbgAbstractIntradayRequest::~QBbgAbstractIntradayRequest() = default;
    QBbgAbstractIntradayRequestPrivate::~QBbgAbstractIntradayRequestPrivate() = default;
    QBbgAbstractIntradayRequestPrivate::QBbgAbstractIntradayRequestPrivate(QBbgAbstractIntradayRequest* q, QBbgAbstractRequest::RequestType typ)
        : QBbgAbstractRequestPrivate(q, typ)
    {}
    QBbgAbstractIntradayRequestPrivate::QBbgAbstractIntradayRequestPrivate(QBbgAbstractIntradayRequest* q, const QBbgAbstractIntradayRequestPrivate& a)
        : QBbgAbstractRequestPrivate(q, a)
        , m_startDate(a.m_startDate)
        , m_endDate(a.m_endDate)
        , m_eventType(a.m_eventType)
    {}
    QBbgAbstractIntradayRequestPrivate& QBbgAbstractIntradayRequestPrivate::operator=(const QBbgAbstractIntradayRequestPrivate& a)
    {
        QBbgAbstractRequestPrivate::operator=(a);
        m_startDate = a.m_startDate;
        m_endDate = a.m_endDate;
        m_eventType = a.m_eventType;
        return *this;
    }

    QBbgAbstractIntradayRequest::QBbgAbstractIntradayRequest(QBbgAbstractIntradayRequestPrivate* d)
        : QBbgAbstractRequest(d)
    {}

    QBbgAbstractIntradayRequest& QBbgAbstractIntradayRequest::operator=(const QBbgAbstractIntradayRequest& a)
    {
        Q_D(QBbgAbstractIntradayRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }

    bool QBbgAbstractIntradayRequest::isValidReq() const
    {
        Q_D(const QBbgAbstractIntradayRequest);
        return 
            d->m_startDate.isValid()
            && d->m_endDate.isValid()
            && d->m_endDate >= d->m_startDate
            && d->m_eventType != QBbgAbstractIntradayRequest::EventType::Invalid
            && QBbgAbstractRequest::isValidReq();
    }

    QBbgAbstractIntradayRequest::EventType QBbgAbstractIntradayRequest::eventType() const
    {
        Q_D(const QBbgAbstractIntradayRequest);
        return d->m_eventType;
    }

    void QBbgAbstractIntradayRequest::setEventType(QBbgAbstractIntradayRequest::EventType val)
    {
        Q_D(QBbgAbstractIntradayRequest);
        d->m_eventType = val;
    }

    void QBbgAbstractIntradayRequest::setDateTimeRange(QDateTime startDt, QDateTime endDt)
    {
        if (startDt > endDt)
            std::swap(startDt, endDt);
        setStartDateTime(startDt); 
        setEndDateTime(endDt);

    }

    bool QBbgAbstractIntradayRequest::operator==(const QBbgAbstractIntradayRequest& other) const
    {
        Q_D(const QBbgAbstractIntradayRequest);
        return
            QBbgAbstractRequest::operator==(other)
            && d->m_eventType == other.d_func()->m_eventType
            && d->m_startDate == other.d_func()->m_startDate
            && d->m_endDate == other.d_func()->m_endDate
            ;
    }

    const QDateTime& QBbgAbstractIntradayRequest::endDateTime() const
    {
        Q_D(const QBbgAbstractIntradayRequest);
        return d->m_endDate;
    }

    void QBbgAbstractIntradayRequest::setEndDateTime(const QDateTime& val)
    {
        Q_D(QBbgAbstractIntradayRequest);
        d->m_endDate = val;
    }

    const QDateTime& QBbgAbstractIntradayRequest::startDateTime() const
    {
        Q_D(const QBbgAbstractIntradayRequest);
        return d->m_startDate;
    }

    void QBbgAbstractIntradayRequest::setStartDateTime(const QDateTime& val)
    {
        Q_D(QBbgAbstractIntradayRequest);
        d->m_startDate = val;
    }

    void QBbgAbstractIntradayRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() != QBbgSecurity::Client) {
            QBbgAbstractRequest::setSecurity(val);
        }
        else{
            QBbgAbstractRequest::setSecurity(QBbgSecurity());
        }
    }

    QString QBbgAbstractIntradayRequest::eventTypeString(const EventType& val)
    {
        switch (val) {
        case EventType::Invalid:
            return QString();
        case EventType::TRADE:
            return QStringLiteral("TRADE");
        case EventType::BID:
            return QStringLiteral("BID");
        case EventType::ASK:
            return QStringLiteral("ASK");
        case EventType::BID_BEST:
            return QStringLiteral("BID_BEST");
        case EventType::ASK_BEST:
            return QStringLiteral("ASK_BEST");
        case EventType::MID_PRICE:
            return QStringLiteral("MID_PRICE");
        case EventType::AT_TRADE:
            return QStringLiteral("AT_TRADE");
        case EventType::BEST_BID:
            return QStringLiteral("BEST_BID");
        case EventType::BEST_ASK:
            return QStringLiteral("BEST_ASK");
        default:
            Q_UNREACHABLE();
        }
    }

    QBbgAbstractIntradayRequest::EventType QBbgAbstractIntradayRequest::stringEventType(QString val)
    {
        val = val.simplified().toUpper();
        val.replace(' ', '_');
        if (val.compare("TRADE") == 0) 
            return EventType::TRADE;
        else if (val.compare("BID") == 0) 
            return EventType::BID;
        else if (val.compare("ASK") == 0) 
            return EventType::ASK;
        else if (val.compare("BID_BEST") == 0) 
            return EventType::BID_BEST;
        else if (val.compare("ASK_BEST") == 0) 
            return EventType::ASK_BEST;
        else if (val.compare("MID_PRICE") == 0)
            return EventType::MID_PRICE;
        else if (val.compare("AT_TRADE") == 0) 
            return EventType::AT_TRADE;
        else if (val.compare("BEST_BID") == 0) 
            return EventType::BEST_BID;
        else if (val.compare("BEST_ASK") == 0) 
            return EventType::BEST_ASK;
        else return EventType::Invalid;
    }

}

uint qHash(QBbgLib::QBbgAbstractIntradayRequest::EventType key, uint seed)
{
    return qHash(static_cast<std::underlying_type<decltype(key)>::type>(key), seed);
}
