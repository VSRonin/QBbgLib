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

#ifndef QBbgHistoricalDataRequest_p_h__
#define QBbgHistoricalDataRequest_p_h__

#include "QBbgHistoricalDataRequest.h"
#include "Private/QBbgAbstractFieldRequest_p.h"
#include <QDate>
namespace QBbgLib {
    class QBbgHistoricalDataRequestPrivate : public QBbgAbstractFieldRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgHistoricalDataRequest)
    private:
        QBbgHistoricalDataRequestPrivate(const QBbgHistoricalDataRequestPrivate& other);
    public:
        virtual ~QBbgHistoricalDataRequestPrivate();
        QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q);
        QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q, const QBbgHistoricalDataRequestPrivate& other);
        virtual QBbgHistoricalDataRequestPrivate& operator=(const QBbgHistoricalDataRequestPrivate& other);
        QDate m_startDate;
        QDate m_endDate;
        QBbgHistoricalDataRequest::PeriodAdjustment m_periodicityAdjustment;
        QBbgHistoricalDataRequest::PeriodSelection m_periodicitySelection;
        QString m_currency;
        bool m_useClosePrice;
        bool m_usePriceForPricing;
        QBbgHistoricalDataRequest::NonTradingDayFill m_nonTradingDayFill;
        bool m_fillWithNull;
        qint32 m_maxDataPoints;
        bool m_useRelativeDate;
        bool m_adjustmentNormal;
        bool m_adjustmentAbnormal;
        bool m_adjustmentSplit;
        bool m_adjustmentFollowDPDF;
        QString m_calendarCode;
    };

    

}
#endif // QBbgHistoricalDataRequest_p_h__

