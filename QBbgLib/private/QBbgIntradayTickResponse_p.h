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

#ifndef QBbgIntradayTickResponse_p_h__
#define QBbgIntradayTickResponse_p_h__

#include "QBbgIntradayTickResponse.h"
#include "QBbgAbstractIntradayRequest.h"
#include "private/QBbgAbstractIntradayResponse_p.h"
#include <QList>
#include <QStringList>
namespace QBbgLib {
    class QBbgIntradayTickResponsePrivate : public QBbgAbstractIntradayResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgIntradayTickResponse)
        QBbgIntradayTickResponsePrivate(const QBbgIntradayTickResponsePrivate& other) = delete;
    public:
        virtual ~QBbgIntradayTickResponsePrivate();
        QBbgIntradayTickResponsePrivate(QBbgIntradayTickResponse* q, const QBbgIntradayTickResponsePrivate& other);
        QBbgIntradayTickResponsePrivate(QBbgIntradayTickResponse* q);
        virtual QBbgIntradayTickResponsePrivate& operator=(const QBbgIntradayTickResponsePrivate& other);
        QBbgAbstractIntradayRequest::EventType m_type;
        QList<double> m_size;
        QStringList m_conditionCode;
        QStringList m_exchangeCode;
        QStringList m_micCode;
        QStringList m_brokerBuyCode;
        QStringList m_brokerSellCode;
        QStringList m_rpsCode;
        template<class T, class S>
        bool genericHas(T container, S predicate) const
        {
            return std::any_of(container.constBegin(), container.constEnd(), predicate);
        }
    };
}
#endif // QBbgIntradayTickResponse_p_h__