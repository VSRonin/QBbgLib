#include "QBbgHistoricalDataRequest.h"
#include "private/QBbgHistoricalDataRequest_p.h"
namespace QBbgLib {
    QBbgHistoricalDataRequestPrivate::QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q)
        : QBbgAbstractFieldRequestPrivate(q)
        , m_periodicityAdjustment(QBbgHistoricalDataRequest::CALENDAR)
        , m_periodicitySelection(QBbgHistoricalDataRequest::DAILY)
        , m_useClosePrice(true)
        , m_usePriceForPricing(false)
        , m_nonTradingDayFill(QBbgHistoricalDataRequest::ACTIVE_DAYS_ONLY)
        , m_fillWithNull(false)
        , m_maxDataPoints(0)
        , m_useRelativeDate(false)
        , m_adjustmentNormal(false)
        , m_adjustmentAbnormal(false)
        , m_adjustmentSplit(false)
        , m_adjustmentFollowDPDF(false)
    {
        m_currency[0] = '\0';
        m_calendarCode[0] = '\0';
        m_RqType = QBbgAbstractRequest::HistoricalData;
    }

    QBbgHistoricalDataRequestPrivate::QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q, const QBbgHistoricalDataRequestPrivate& other)
        : QBbgAbstractFieldRequestPrivate(q, other)
        , m_startDate(other.m_startDate)
        , m_endDate(other.m_endDate)
        , m_periodicityAdjustment(other.m_periodicityAdjustment)
        , m_periodicitySelection(other.m_periodicitySelection)
        , m_useClosePrice(other.m_useClosePrice)
        , m_usePriceForPricing(other.m_usePriceForPricing)
        , m_nonTradingDayFill(other.m_nonTradingDayFill)
        , m_fillWithNull(other.m_fillWithNull)
        , m_maxDataPoints(other.m_maxDataPoints)
        , m_useRelativeDate(other.m_useRelativeDate)
        , m_adjustmentNormal(other.m_adjustmentNormal)
        , m_adjustmentAbnormal(other.m_adjustmentAbnormal)
        , m_adjustmentSplit(other.m_adjustmentSplit)
        , m_adjustmentFollowDPDF(other.m_adjustmentFollowDPDF)
    {
        for (int i = 0; i < (sizeof(m_currency) / sizeof(*m_currency)); ++i) {
            m_currency[i] = other.m_currency[i];
        }
        for (int i = 0; i < (sizeof(m_calendarCode) / sizeof(*m_calendarCode)); ++i) {
            m_calendarCode[i] = other.m_calendarCode[i];
        }
        m_RqType = QBbgAbstractRequest::HistoricalData;
    }

    bool QBbgHistoricalDataRequestPrivate::operator==(const QBbgHistoricalDataRequestPrivate& a) const
    {
        return 
            QBbgAbstractFieldRequestPrivate::operator==(a) &&
            m_startDate == a.m_startDate &&
            m_endDate == a.m_endDate &&
            m_periodicityAdjustment == a.m_periodicityAdjustment &&
            m_periodicitySelection == a.m_periodicitySelection &&
            m_useClosePrice == a.m_useClosePrice &&
            m_usePriceForPricing == a.m_usePriceForPricing &&
            m_nonTradingDayFill == a.m_nonTradingDayFill &&
            m_fillWithNull == a.m_fillWithNull &&
            m_maxDataPoints == a.m_maxDataPoints &&
            m_useRelativeDate == a.m_useRelativeDate &&
            m_adjustmentNormal == a.m_adjustmentNormal &&
            m_adjustmentAbnormal == a.m_adjustmentAbnormal &&
            m_adjustmentSplit == a.m_adjustmentSplit &&
            m_adjustmentFollowDPDF == a.m_adjustmentFollowDPDF &&
            strcmp(m_currency, a.m_currency)==0 && 
            strcmp(m_calendarCode, a.m_calendarCode) == 0
        ;
    }
    bool QBbgHistoricalDataRequest::equalHistoricalFields(const QBbgHistoricalDataRequest& a) const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return 
            d->m_startDate == a.d_func()->m_startDate &&
            d->m_endDate == a.d_func()->m_endDate &&
            d->m_periodicityAdjustment == a.d_func()->m_periodicityAdjustment &&
            d->m_periodicitySelection == a.d_func()->m_periodicitySelection &&
            d->m_useClosePrice == a.d_func()->m_useClosePrice &&
            d->m_usePriceForPricing == a.d_func()->m_usePriceForPricing &&
            d->m_nonTradingDayFill == a.d_func()->m_nonTradingDayFill &&
            d->m_fillWithNull == a.d_func()->m_fillWithNull &&
            d->m_maxDataPoints == a.d_func()->m_maxDataPoints &&
            d->m_useRelativeDate == a.d_func()->m_useRelativeDate &&
            d->m_adjustmentNormal == a.d_func()->m_adjustmentNormal &&
            d->m_adjustmentAbnormal == a.d_func()->m_adjustmentAbnormal &&
            d->m_adjustmentSplit == a.d_func()->m_adjustmentSplit &&
            d->m_adjustmentFollowDPDF == a.d_func()->m_adjustmentFollowDPDF &&
            strcmp(d->m_currency, a.d_func()->m_currency) == 0 &&
            strcmp(d->m_calendarCode, a.d_func()->m_calendarCode) == 0
            ;
    }
    QBbgHistoricalDataRequestPrivate& QBbgHistoricalDataRequestPrivate::operator=(const QBbgHistoricalDataRequestPrivate& other)
    {
        QBbgAbstractFieldRequestPrivate::operator=(other);
        m_startDate = other.m_startDate;
        m_endDate = other.m_endDate;
        m_periodicityAdjustment = other.m_periodicityAdjustment;
        m_periodicitySelection = other.m_periodicitySelection;
        m_useClosePrice = other.m_useClosePrice;
        m_usePriceForPricing = other.m_usePriceForPricing;
        m_nonTradingDayFill = other.m_nonTradingDayFill;
        m_fillWithNull = other.m_fillWithNull;
        m_maxDataPoints = other.m_maxDataPoints;
        m_useRelativeDate = other.m_useRelativeDate;
        m_adjustmentNormal = other.m_adjustmentNormal;
        m_adjustmentAbnormal = other.m_adjustmentAbnormal;
        m_adjustmentSplit = other.m_adjustmentSplit;
        m_adjustmentFollowDPDF = other.m_adjustmentFollowDPDF;
        for (int i = 0; i < (sizeof(m_currency) / sizeof(*m_currency)); ++i) {
            m_currency[i] = other.m_currency[i];
        }
        for (int i = 0; i < (sizeof(m_calendarCode) / sizeof(*m_calendarCode)); ++i) {
            m_calendarCode[i] = other.m_calendarCode[i];
        }
        return *this;
    }
    bool QBbgHistoricalDataRequest::operator==(const QBbgHistoricalDataRequest& a) const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->operator==(*(a.d_func()));
    }

    QString QBbgHistoricalDataRequest::calendarCode() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_calendarCode;
    }

    void QBbgHistoricalDataRequest::calendarCode(QString val)
    {
        Q_D(QBbgHistoricalDataRequest);
        val = val.trimmed().toUpper();
        if (val.size() != 2) {
            d->m_calendarCode[0]='\0';
            return;
        }
        d->m_calendarCode[0] = val.at(0).toLatin1();
        d->m_calendarCode[1] = val.at(1).toLatin1();
        d->m_calendarCode[2] = '\0';
    }

    bool QBbgHistoricalDataRequest::adjustmentFollowDPDF() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_adjustmentFollowDPDF;
    }

    bool QBbgHistoricalDataRequest::adjustmentSplit() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_adjustmentSplit;
    }

    bool QBbgHistoricalDataRequest::adjustmentAbnormal() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_adjustmentAbnormal;
    }

    bool QBbgHistoricalDataRequest::adjustmentNormal() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_adjustmentNormal;
    }

    bool QBbgHistoricalDataRequest::useRelativeDate() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_useRelativeDate;
    }

    qint32 QBbgHistoricalDataRequest::maxDataPoints() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_maxDataPoints;
    }

    bool QBbgHistoricalDataRequest::fillWithNull() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_fillWithNull;
    }

    QBbgHistoricalDataRequest::NonTradingDayFill QBbgHistoricalDataRequest::nonTradingDayFill() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_nonTradingDayFill;
    }

    bool QBbgHistoricalDataRequest::usePriceForPricing() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_usePriceForPricing;
    }

    void QBbgHistoricalDataRequest::usePriceForPricing(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_usePriceForPricing = val;
    }

    bool QBbgHistoricalDataRequest::useClosePrice() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_useClosePrice;
    }

    void QBbgHistoricalDataRequest::useClosePrice(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_useClosePrice = val;
    }

    QString QBbgHistoricalDataRequest::currency() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_currency;
    }

    void QBbgHistoricalDataRequest::currency(QString val)
    {
        Q_D(QBbgHistoricalDataRequest);
        val = val.trimmed().toUpper();
        if (val.size() != 3) {
            d->m_currency[0] = '\0';
            return;
        }
        d->m_currency[0] = val.at(0).toLatin1();
        d->m_currency[1] = val.at(1).toLatin1();
        d->m_currency[2] = val.at(2).toLatin1();
        d->m_currency[3] = '\0';
    }

    QBbgHistoricalDataRequest::PeriodSelection QBbgHistoricalDataRequest::periodicitySelection() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_periodicitySelection;
    }

    void QBbgHistoricalDataRequest::periodicitySelection(QBbgHistoricalDataRequest::PeriodSelection val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_periodicitySelection = val;
    }

    QBbgHistoricalDataRequest::PeriodAdjustment QBbgHistoricalDataRequest::periodicityAdjustment() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_periodicityAdjustment;
    }

    void QBbgHistoricalDataRequest::periodicityAdjustment(PeriodAdjustment val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_periodicityAdjustment = val;
    }

    const QDate& QBbgHistoricalDataRequest::endDate() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_endDate;
    }

    void QBbgHistoricalDataRequest::endDate(const QDate& val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_endDate = val;
    }

    const QDate& QBbgHistoricalDataRequest::startDate() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_startDate;
    }

    void QBbgHistoricalDataRequest::startDate(const QDate& val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_startDate = val;
    }

    void QBbgHistoricalDataRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() != QBbgSecurity::Client) {
            QBbgAbstractFieldRequest::setSecurity(val);
        }
    }

    bool QBbgHistoricalDataRequest::isValidReq() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        if (d->m_startDate.isNull()) return false;
        if (d->m_currency[0] != '\0' && strlen(d->m_currency) != 3) return false;
        if (d->m_maxDataPoints<0) return false;
        if (d->m_calendarCode[0] != '\0' && strlen(d->m_calendarCode) != 2) return false;
        //if (d->m_calendarCode[0] != '\0' && d->m_periodicitySelection != DAILY) return false; //calendarCodeOverride only applies only to DAILY requests
        return QBbgAbstractFieldRequest::isValidReq();
    }


    QBbgHistoricalDataRequest::QBbgHistoricalDataRequest()
        :QBbgAbstractFieldRequest(new QBbgHistoricalDataRequestPrivate(this))
    {

    }

    QBbgHistoricalDataRequest::QBbgHistoricalDataRequest(const QBbgHistoricalDataRequest& a)
        : QBbgAbstractFieldRequest(new QBbgHistoricalDataRequestPrivate(this, *(a.d_func())))
    {

    }

    QBbgHistoricalDataRequest& QBbgHistoricalDataRequest::operator=(const QBbgHistoricalDataRequest& a)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }

    void QBbgHistoricalDataRequest::nonTradingDayFill(QBbgHistoricalDataRequest::NonTradingDayFill val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_nonTradingDayFill = val;
    }

    void QBbgHistoricalDataRequest::fillWithNull(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_fillWithNull = val;
    }

    void QBbgHistoricalDataRequest::maxDataPoints(qint32 val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_maxDataPoints = val;
    }

    void QBbgHistoricalDataRequest::useRelativeDate(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_useRelativeDate = val;
    }

    void QBbgHistoricalDataRequest::adjustmentNormal(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentNormal = val;
    }

    void QBbgHistoricalDataRequest::adjustmentAbnormal(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentAbnormal = val;
    }

    void QBbgHistoricalDataRequest::adjustmentSplit(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentSplit = val;
    }

    void QBbgHistoricalDataRequest::adjustmentFollowDPDF(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentFollowDPDF = val;
    }
}