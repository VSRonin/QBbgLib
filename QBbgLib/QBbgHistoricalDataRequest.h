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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QBbgHistoricalDataRequest_h__
#define QBbgHistoricalDataRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDate>
#include <QObject>
namespace QBbgLib {
    class QBbgHistoricalDataRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBBG_EXPORT QBbgHistoricalDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_PROPERTY(QString calendarCode READ calendarCode WRITE setCalendarCode)
        Q_PROPERTY(bool adjustmentFollowDPDF READ adjustmentFollowDPDF WRITE setAdjustmentFollowDPDF)
        Q_PROPERTY(bool adjustmentSplit READ adjustmentSplit WRITE setAdjustmentSplit)
        Q_PROPERTY(bool adjustmentAbnormal READ adjustmentAbnormal WRITE setAdjustmentAbnormal)
        Q_PROPERTY(bool adjustmentNormal READ adjustmentNormal WRITE setAdjustmentNormal)
        Q_PROPERTY(qint32 maxDataPoints READ maxDataPoints WRITE setMaxDataPoints)
        Q_PROPERTY(bool useRelativeDate READ useRelativeDate WRITE setUseRelativeDate)
        Q_PROPERTY(bool fillWithNull READ fillWithNull WRITE setFillWithNull)
        Q_PROPERTY(NonTradingDayFill nonTradingDayFill READ nonTradingDayFill WRITE setNonTradingDayFill)
        Q_PROPERTY(bool usePriceForPricing READ usePriceForPricing WRITE setUsePriceForPricing)
        Q_PROPERTY(bool useClosePrice READ useClosePrice WRITE setUseClosePrice)
        Q_PROPERTY(QString currency READ currency WRITE setCurrency)
        Q_PROPERTY(PeriodSelection periodicitySelection READ periodicitySelection WRITE setPeriodicitySelection)
        Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate)
        Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate)
        Q_DECLARE_PRIVATE(QBbgHistoricalDataRequest)
    public:
        enum PeriodAdjustment
        {
            ACTUAL
            , CALENDAR
            , FISCAL
        };
        Q_ENUM(PeriodAdjustment)
        enum PeriodSelection
        {
            DAILY
            , WEEKLY
            , MONTHLY
            , QUARTERLY
            , SEMI_ANNUALLY
            , YEARLY
        };
        Q_ENUM(PeriodSelection)
        enum NonTradingDayFill
        {
            NON_TRADING_WEEKDAYS
            , ALL_CALENDAR_DAYS
            , ACTIVE_DAYS_ONLY
        };
        Q_ENUM(NonTradingDayFill)
        virtual ~QBbgHistoricalDataRequest();
        QBbgHistoricalDataRequest();
        QBbgHistoricalDataRequest(const QBbgHistoricalDataRequest& a);
        virtual QBbgHistoricalDataRequest& operator=(const QBbgHistoricalDataRequest& a);
        virtual bool operator==(const QBbgHistoricalDataRequest& a) const;
        virtual QString calendarCode() const;
        virtual void setCalendarCode(QString val);
        virtual bool adjustmentFollowDPDF() const;
        virtual void setAdjustmentFollowDPDF(bool val);
        virtual bool adjustmentSplit() const;
        virtual void setAdjustmentSplit(bool val);
        virtual bool adjustmentAbnormal() const;
        virtual void setAdjustmentAbnormal(bool val);
        virtual bool adjustmentNormal() const;
        virtual void setAdjustmentNormal(bool val);
        virtual bool useRelativeDate() const; // #TODO Check if it's usable
        virtual void setUseRelativeDate(bool val);
        virtual qint32 maxDataPoints() const;
        virtual void setMaxDataPoints(qint32 val);
        virtual bool fillWithNull() const;
        virtual void setFillWithNull(bool val);
        virtual  NonTradingDayFill nonTradingDayFill() const;
        virtual  void setNonTradingDayFill(NonTradingDayFill val);
        virtual bool usePriceForPricing() const;
        virtual  void setUsePriceForPricing(bool val);
        virtual bool useClosePrice() const;
        virtual void setUseClosePrice(bool val);
        virtual QString currency() const;
        virtual void setCurrency(QString val);
        virtual PeriodSelection periodicitySelection() const;
        virtual void setPeriodicitySelection(QBbgHistoricalDataRequest::PeriodSelection val);
        virtual PeriodAdjustment periodicityAdjustment() const;
        virtual void setPeriodicityAdjustment(PeriodAdjustment val);
        virtual const QDate& endDate() const;
        virtual void setEndDate(const QDate& val);
        virtual const QDate& startDate() const;
        virtual void setStartDate(const QDate& val);
        virtual void setSecurity(const QBbgSecurity& val);
        virtual bool isValidReq() const;
    protected:
        virtual bool equalHistoricalFields(const QBbgHistoricalDataRequest& a) const;
        QBbgHistoricalDataRequest(QBbgHistoricalDataRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
    };
}
#endif // QBbgHistoricalDataRequest_h__