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
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QBbgHistoricalDataResponse_p_h__
#define QBbgHistoricalDataResponse_p_h__
#include "QBbgHistoricalDataResponse.h"
#include "QBbgAbstractFieldResponse_p.h"
#include "QBbgSecurity.h"
#include <QList>
#include <QDate>
namespace QBbgLib {
    class QBbgHistoricalDataResponsePrivate : public QBbgAbstractFieldResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgHistoricalDataResponse)
        QBbgHistoricalDataResponsePrivate(const QBbgHistoricalDataResponsePrivate& other);
    public:
        virtual ~QBbgHistoricalDataResponsePrivate();
        QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q, const QBbgHistoricalDataResponsePrivate& other);
        QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q);
        virtual QBbgHistoricalDataResponsePrivate& operator=(const QBbgHistoricalDataResponsePrivate& other);
        QMap<QDate, QVariant> m_values;
        QMap<QDate, QString> m_relDates;
    };

    

}
#endif // QBbgHistoricalDataResponse_p_h__