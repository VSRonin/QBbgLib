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

#include "QBbgHistoricalDataRequest.h"
#include "private/QBbgHistoricalDataRequest_p.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgHistoricalDataRequest::~QBbgHistoricalDataRequest() = default;
    QBbgHistoricalDataRequestPrivate::~QBbgHistoricalDataRequestPrivate() = default;
    QBbgHistoricalDataRequestPrivate::QBbgHistoricalDataRequestPrivate(QBbgHistoricalDataRequest* q)
        : QBbgAbstractFieldRequestPrivate(q, QBbgAbstractRequest::RequestType::HistoricalData)
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
        , m_currency(other.m_currency)
        , m_calendarCode(other.m_calendarCode)
    {
    }

    bool QBbgHistoricalDataRequest::operator==(const QBbgHistoricalDataRequest& a) const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return
            QBbgAbstractFieldRequest::operator==(a) &&
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
            d->m_currency == a.d_func()->m_currency &&
            d->m_calendarCode == a.d_func()->m_calendarCode
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
            d->m_currency == a.d_func()->m_currency &&
            d->m_calendarCode == a.d_func()->m_calendarCode
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
        m_currency = other.m_currency;
        m_calendarCode = other.m_calendarCode;
        return *this;
    }
    void QBbgHistoricalDataRequest::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgHistoricalDataRequest);
        QBbgAbstractFieldRequest::saveToStream(stream);
        stream 
            << d->m_startDate
            << d->m_endDate
            << d->m_currency
            << d->m_useClosePrice
            << d->m_usePriceForPricing
            << d->m_fillWithNull
            << d->m_maxDataPoints
            << d->m_useRelativeDate
            << d->m_adjustmentAbnormal
            << d->m_adjustmentNormal
            << d->m_adjustmentSplit
            << d->m_adjustmentFollowDPDF
            << d->m_calendarCode
            << static_cast<std::underlying_type<PeriodAdjustment>::type>(d->m_periodicityAdjustment)
            << static_cast<std::underlying_type<PeriodSelection>::type>(d->m_periodicitySelection)
            << static_cast<std::underlying_type<NonTradingDayFill>::type>(d->m_nonTradingDayFill)
            ;
    }

    void QBbgHistoricalDataRequest::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgHistoricalDataRequest);
        std::underlying_type<PeriodAdjustment>::type periodicityAdjustment;
        std::underlying_type<PeriodSelection>::type periodicitySelection;
        std::underlying_type<NonTradingDayFill>::type nonTradingDayFill;
        QBbgAbstractFieldRequest::loadFromStream(stream);
        stream
            >> d->m_startDate
            >> d->m_endDate
            >> d->m_currency
            >> d->m_useClosePrice
            >> d->m_usePriceForPricing
            >> d->m_fillWithNull
            >> d->m_maxDataPoints
            >> d->m_useRelativeDate
            >> d->m_adjustmentAbnormal
            >> d->m_adjustmentNormal
            >> d->m_adjustmentSplit
            >> d->m_adjustmentFollowDPDF
            >> d->m_calendarCode
            >> periodicityAdjustment
            >> periodicitySelection
            >> nonTradingDayFill
            ;
        d->m_periodicityAdjustment = static_cast<PeriodAdjustment>(periodicityAdjustment);
        d->m_periodicitySelection = static_cast<PeriodSelection>(periodicitySelection);
        d->m_nonTradingDayFill = static_cast<NonTradingDayFill>(nonTradingDayFill);
    }
    QString QBbgHistoricalDataRequest::calendarCode() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_calendarCode;
    }

    void QBbgHistoricalDataRequest::setCalendarCode(QString val)
    {
        Q_D(QBbgHistoricalDataRequest);
        val = val.trimmed().toUpper();
        if (val.size() != 2) {
            d->m_calendarCode.clear();
            return;
        }
        d->m_calendarCode = val;
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

    void QBbgHistoricalDataRequest::setUsePriceForPricing(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_usePriceForPricing = val;
    }

    bool QBbgHistoricalDataRequest::useClosePrice() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_useClosePrice;
    }

    void QBbgHistoricalDataRequest::setUseClosePrice(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_useClosePrice = val;
    }

    QString QBbgHistoricalDataRequest::currency() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_currency;
    }

    void QBbgHistoricalDataRequest::setCurrency(QString val)
    {
        Q_D(QBbgHistoricalDataRequest);
        val = val.trimmed().toUpper();
        if (val.size() != 3) {
            d->m_currency.clear();
            return;
        }
        d->m_currency = val;
    }

    QBbgHistoricalDataRequest::PeriodSelection QBbgHistoricalDataRequest::periodicitySelection() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_periodicitySelection;
    }

    void QBbgHistoricalDataRequest::setPeriodicitySelection(QBbgHistoricalDataRequest::PeriodSelection val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_periodicitySelection = val;
    }

    QBbgHistoricalDataRequest::PeriodAdjustment QBbgHistoricalDataRequest::periodicityAdjustment() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_periodicityAdjustment;
    }

    void QBbgHistoricalDataRequest::setPeriodicityAdjustment(PeriodAdjustment val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_periodicityAdjustment = val;
    }

    const QDate& QBbgHistoricalDataRequest::endDate() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_endDate;
    }

    void QBbgHistoricalDataRequest::setEndDate(const QDate& val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_endDate = val;
    }

    const QDate& QBbgHistoricalDataRequest::startDate() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        return d->m_startDate;
    }

    void QBbgHistoricalDataRequest::setStartDate(const QDate& val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_startDate = val;
    }

    void QBbgHistoricalDataRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() != QBbgSecurity::Client) {
            QBbgAbstractFieldRequest::setSecurity(val);
        }
        else {
            QBbgAbstractRequest::setSecurity(QBbgSecurity());
        }
    }

    bool QBbgHistoricalDataRequest::isValidReq() const
    {
        Q_D(const QBbgHistoricalDataRequest);
        if (d->m_startDate.isNull()) return false;
        if (!d->m_currency.isEmpty() && d->m_currency.size() != 3) return false;
        if (d->m_maxDataPoints<0) return false;
        if (!d->m_calendarCode.isEmpty() && d->m_calendarCode.size() != 2) return false;
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

    void QBbgHistoricalDataRequest::setNonTradingDayFill(QBbgHistoricalDataRequest::NonTradingDayFill val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_nonTradingDayFill = val;
    }

    void QBbgHistoricalDataRequest::setFillWithNull(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_fillWithNull = val;
    }

    void QBbgHistoricalDataRequest::setMaxDataPoints(qint32 val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_maxDataPoints = val;
    }

    void QBbgHistoricalDataRequest::setUseRelativeDate(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_useRelativeDate = val;
    }

    void QBbgHistoricalDataRequest::setAdjustmentNormal(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentNormal = val;
    }

    void QBbgHistoricalDataRequest::setAdjustmentAbnormal(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentAbnormal = val;
    }

    void QBbgHistoricalDataRequest::setAdjustmentSplit(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentSplit = val;
    }

    void QBbgHistoricalDataRequest::setAdjustmentFollowDPDF(bool val)
    {
        Q_D(QBbgHistoricalDataRequest);
        d->m_adjustmentFollowDPDF = val;
    }
}
