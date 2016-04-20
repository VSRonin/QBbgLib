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

#include "QBbgAbstractIntradayResponse.h"
#include "private/QBbgAbstractIntradayResponse_p.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgAbstractIntradayResponse::~QBbgAbstractIntradayResponse() = default;
    QBbgAbstractIntradayResponsePrivate::~QBbgAbstractIntradayResponsePrivate() = default;
    QBbgAbstractIntradayResponsePrivate::QBbgAbstractIntradayResponsePrivate(QBbgAbstractIntradayResponse* q, QBbgAbstractResponse::ResponseType typ)
        :QBbgAbstractResponsePrivate(q, typ)
    {}

    QBbgAbstractIntradayResponsePrivate::QBbgAbstractIntradayResponsePrivate(QBbgAbstractIntradayResponse* q, const QBbgAbstractIntradayResponsePrivate& other)
        : QBbgAbstractResponsePrivate(q, other)
        , m_time(other.m_time)
        , m_value(other.m_value)
    {}
    QBbgAbstractIntradayResponsePrivate& QBbgAbstractIntradayResponsePrivate::operator=(const QBbgAbstractIntradayResponsePrivate& other)
    {
        QBbgAbstractResponsePrivate::operator=(other);
        m_time = other.m_time;
        m_value = other.m_value;
        return *this;
    }

    void QBbgAbstractIntradayResponse::addValue(const QDateTime& dt, double val)
    {
        Q_D(QBbgAbstractIntradayResponse);
        d->m_time.append(dt);
        d->m_value.append(val);
    }

    void QBbgAbstractIntradayResponse::clear()
    {
        Q_D(QBbgAbstractIntradayResponse);
        d->m_time.clear();
        d->m_value.clear();
    }

    QBbgAbstractIntradayResponse::QBbgAbstractIntradayResponse(QBbgAbstractIntradayResponsePrivate* d)
        : QBbgAbstractResponse(d)
    {}
    QBbgAbstractIntradayResponse& QBbgAbstractIntradayResponse::operator=(const QBbgAbstractIntradayResponse& a)
    {
        Q_D(QBbgAbstractIntradayResponse);
        d->operator=(*(a.d_func()));
        return *this;
    }

    double QBbgAbstractIntradayResponse::value(int index) const
    {
        Q_D(const QBbgAbstractIntradayResponse);
        return d->m_value.value(index,0.0);
    }

    QDateTime QBbgAbstractIntradayResponse::dateTime(int index) const
    {
        Q_D(const QBbgAbstractIntradayResponse);
        return d->m_time.value(index);
    }

    int QBbgAbstractIntradayResponse::size() const
    {
        Q_D(const QBbgAbstractIntradayResponse);
        return d->m_time.size();
    }

}