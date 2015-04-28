#ifndef QBbgHistoricalDataRequest_p_h__
#define QBbgHistoricalDataRequest_p_h__

#include "QBbgHistoricalDataRequest.h"
#include "QBbgAbstractFieldRequest_p.h"
#include <QDate>
namespace QBbgLib {
    class QBbgHistoricalDataRequestPrivate : public QBbgAbstractFieldRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgHistoricalDataRequest)
    public:
        
        QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q);
        QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q, const QBbgHistoricalDataRequestPrivate& other);
        virtual QBbgHistoricalDataRequestPrivate& operator=(const QBbgHistoricalDataRequestPrivate& other);
        virtual bool operator==(const QBbgHistoricalDataRequestPrivate& a) const;
    private:
        QBbgHistoricalDataRequestPrivate(const QBbgHistoricalDataRequestPrivate& other);
        QDate m_startDate;
        QDate m_endDate;
        QBbgHistoricalDataRequest::PeriodAdjustment m_periodicityAdjustment;
        QBbgHistoricalDataRequest::PeriodSelection m_periodicitySelection;
        char m_currency[3 + 1];
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
        char m_calendarCode[2 + 1];
    };

    

}
#endif // QBbgHistoricalDataRequest_p_h__

