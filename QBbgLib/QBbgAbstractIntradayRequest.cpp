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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.              *
*                                                                               *
\*******************************************************************************/

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#include "QBbgAbstractIntradayRequest.h"
#include "QBbgAbstractIntradayRequest_p.h"
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
}