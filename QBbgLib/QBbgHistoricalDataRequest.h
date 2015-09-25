#ifndef QBbgHistoricalDataRequest_h__
#define QBbgHistoricalDataRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDate>
namespace QBbgLib {
    class QBbgHistoricalDataRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBBG_EXPORT QBbgHistoricalDataRequest : public QBbgAbstractFieldRequest
    {
        Q_DECLARE_PRIVATE(QBbgHistoricalDataRequest)
    public:
        enum PeriodAdjustment
        {
            ACTUAL
            , CALENDAR
            , FISCAL
        };
        enum PeriodSelection
        {
            DAILY
            , WEEKLY
            , MONTHLY
            , QUARTERLY
            , SEMI_ANNUALLY
            , YEARLY
        };
        enum NonTradingDayFill
        {
            NON_TRADING_WEEKDAYS
            , ALL_CALENDAR_DAYS
            , ACTIVE_DAYS_ONLY
        };
        virtual ~QBbgHistoricalDataRequest();
        QBbgHistoricalDataRequest();
        QBbgHistoricalDataRequest(const QBbgHistoricalDataRequest& a);
        virtual QBbgHistoricalDataRequest& operator=(const QBbgHistoricalDataRequest& a);
        virtual bool operator==(const QBbgHistoricalDataRequest& a) const;
        virtual QString calendarCode() const;
        virtual void calendarCode(QString val);
        virtual bool adjustmentFollowDPDF() const;
        virtual void adjustmentFollowDPDF(bool val);
        virtual bool adjustmentSplit() const;
        virtual void adjustmentSplit(bool val);
        virtual bool adjustmentAbnormal() const;
        virtual void adjustmentAbnormal(bool val);
        virtual bool adjustmentNormal() const;
        virtual void adjustmentNormal(bool val);
        virtual bool useRelativeDate() const;
        virtual void useRelativeDate(bool val);
        virtual qint32 maxDataPoints() const;
        virtual void maxDataPoints(qint32 val);
        virtual bool fillWithNull() const;
        virtual void fillWithNull(bool val);
        virtual  NonTradingDayFill nonTradingDayFill() const;
        virtual  void nonTradingDayFill(NonTradingDayFill val);
        virtual bool usePriceForPricing() const;
        virtual  void usePriceForPricing(bool val);
        virtual bool useClosePrice() const;
        virtual void useClosePrice(bool val);
        virtual QString currency() const;
        virtual void currency(QString val);
        virtual PeriodSelection periodicitySelection() const;
        virtual void periodicitySelection(QBbgHistoricalDataRequest::PeriodSelection val);
        virtual PeriodAdjustment periodicityAdjustment() const;
        virtual void periodicityAdjustment(PeriodAdjustment val);
        virtual const QDate& endDate() const;
        virtual void endDate(const QDate& val);
        virtual const QDate& startDate() const;
        virtual void startDate(const QDate& val);
        virtual void setSecurity(const QBbgSecurity& val);
        virtual bool isValidReq() const;
    protected:
        virtual bool equalHistoricalFields(const QBbgHistoricalDataRequest& a) const;
        QBbgHistoricalDataRequest(QBbgHistoricalDataRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
    };
}
#endif // QBbgHistoricalDataRequest_h__