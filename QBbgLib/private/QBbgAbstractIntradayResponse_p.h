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
#include "private/QBbgAbstractResponse_p.h"
#include <QDateTime>
#include <QList>
namespace QBbgLib {
    class QBbgAbstractIntradayResponsePrivate : public QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractIntradayResponse)
        QBbgAbstractIntradayResponsePrivate(const QBbgAbstractIntradayResponsePrivate& other) = delete;
    public:
        virtual ~QBbgAbstractIntradayResponsePrivate() = 0;
        QBbgAbstractIntradayResponsePrivate(QBbgAbstractIntradayResponse* q, QBbgAbstractResponse::ResponseType typ);
        QBbgAbstractIntradayResponsePrivate(QBbgAbstractIntradayResponse* q, const QBbgAbstractIntradayResponsePrivate& other);
        virtual QBbgAbstractIntradayResponsePrivate& operator=(const QBbgAbstractIntradayResponsePrivate& other);
        QList<QDateTime> m_time;
        QList<double> m_value;
    };
}