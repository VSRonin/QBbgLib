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


#ifndef QBbgAbstractIntradayRequest_p_h__
#define QBbgAbstractIntradayRequest_p_h__

#include "QBbgAbstractIntradayRequest.h"
#include "Private/QBbgAbstractRequest_p.h"
#include <QDateTime>
namespace QBbgLib {
    class QBbgAbstractIntradayRequestPrivate : public QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgAbstractIntradayRequest)
    public:
        virtual ~QBbgAbstractIntradayRequestPrivate() = 0;
        QBbgAbstractIntradayRequestPrivate(QBbgAbstractIntradayRequest* q, const QBbgAbstractIntradayRequestPrivate& a);
        QBbgAbstractIntradayRequestPrivate(QBbgAbstractIntradayRequest* q, QBbgAbstractRequest::RequestType typ);
        QBbgAbstractIntradayRequestPrivate& operator=(const QBbgAbstractIntradayRequestPrivate& a);
        QDateTime m_startDate;
        QDateTime m_endDate;
        QBbgAbstractIntradayRequest::EventType m_eventType;
    private:
        QBbgAbstractIntradayRequestPrivate(const QBbgAbstractIntradayRequestPrivate& other) = delete;
    };
}
#endif // QBbgAbstractIntradayRequest_p_h__