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

#ifndef QBbgIntradayTickRequest_p_h__
#define QBbgIntradayTickRequest_p_h__

#include "QBbgIntradayTickRequest.h"
#include "private/QBbgAbstractIntradayRequest_p.h"
namespace QBbgLib {
    class QBbgIntradayTickRequestPrivate : public QBbgAbstractIntradayRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgIntradayTickRequest)
    public:
        virtual ~QBbgIntradayTickRequestPrivate();
        QBbgIntradayTickRequestPrivate(QBbgIntradayTickRequest* q);
        QBbgIntradayTickRequestPrivate(QBbgIntradayTickRequest* q, const QBbgIntradayTickRequestPrivate& other);
        virtual QBbgIntradayTickRequestPrivate& operator=(const QBbgIntradayTickRequestPrivate& other);
        bool m_includeConditionCodes;
        bool m_includeNonPlottable;
        bool m_includeExchangeCodes;
        bool m_includeBrokerCodes;
        bool m_includeRpsCodes;
        bool m_includeBicMicCodes;
    private:
        QBbgIntradayTickRequestPrivate(const QBbgIntradayTickRequestPrivate& other) = delete;
    };
}
#endif // QBbgIntradayTickRequest_p_h__
