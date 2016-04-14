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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.              *
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
    /*!
    \brief An historical request
    \details This class can be used to query historical data from Bloomberg.<br/> 
    This is equivalent to BDH() Bloomberg function in excel.
    */
    class QBBG_EXPORT QBbgHistoricalDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        /*!
        \brief Returns the data based on the calendar of the specified country, exchange, or religion.
        \details Returns the data based on the calendar of the specified country, exchange, or religion from CDR<GO>.<br/>
        Taking a two character calendar code null terminated string. This will cause the data to be aligned according to the calendar and including calendar holidays.<br/>
        Only applies only to DAILY requests.
        \getter calendarCode()
        \setter setCalendarCode()
        */
        Q_PROPERTY(QString calendarCode READ calendarCode WRITE setCalendarCode)
        /*!
        \brief Adjustments based on DPDF
        \details Setting to true will follow the DPDF<GO> Bloomberg function.<br/>
        True is the default setting for this option.
        \getter adjustmentFollowDPDF()
        \setter setAdjustmentFollowDPDF()
        */
        Q_PROPERTY(bool adjustmentFollowDPDF READ adjustmentFollowDPDF WRITE setAdjustmentFollowDPDF)
        /*!
        \brief Adjustments based on Capital Changes
        \details Adjust historical pricing and/or volume to reflect: Spin-Offs, Stock Splits/Consolidations, Stock Dividend/Bonus, Rights Offerings/Entitlement.
        \getter adjustmentSplit()
        \setter setAdjustmentSplit()
        */
        Q_PROPERTY(bool adjustmentSplit READ adjustmentSplit WRITE setAdjustmentSplit)
        /*!
        \brief Adjusts for Abnormal Cash Dividends
        \details Adjust historical pricing to reflect:<ul>
        <li>Special Cash</li>
        <li>Liquidation, Capital Gains</li>
        <li>Long-Term Capital Gains</li>
        <li>Short-Term Capital Gains</li>
        <li>Memorial, Return of Capital</li>
        <li>Rights Redemption</li>
        <li>Miscellaneous</li>
        <li>Return Premium</li>
        <li>Preferred Rights Redemption</li>
        <li>Proceeds/Rights</li>
        <li>Proceeds/Shares</li>
        <li>Proceeds/Warrants</li>
        </ul>
        \getter adjustmentAbnormal()
        \setter setAdjustmentAbnormal()
        */
        Q_PROPERTY(bool adjustmentAbnormal READ adjustmentAbnormal WRITE setAdjustmentAbnormal)
        /*!
        \brief Adjust for "change on day"
        \details Adjust historical pricing to reflect:<ul>
        <li>Regular Cash</li>
        <li>Interim, 1st Interim</li>
        <li>2nd Interim, 3rd Interim</li>
        <li>4th Interim</li>
        <li>5th Interim, Income</li>
        <li>Estimated</li>
        <li>Partnership Distribution</li>
        <li>Final</li>
        <li>Interest on Capital</li>
        <li>Distribution</li>
        <li>Prorated</li>
        </ul>
        \getter adjustmentNormal()
        \setter setAdjustmentNormal()
        */
        Q_PROPERTY(bool adjustmentNormal READ adjustmentNormal WRITE setAdjustmentNormal)
        /*!
        \brief Maximum number of data points to return
        \details The response will contain up to X data points, where X is the integer specified.<br/>
        If the original data set is larger than X, the response will be a subset, containing the last X data points.<br/>
        Hence the first range of data points will be removed.
        \getter maxDataPoints()
        \setter setMaxDataPoints()
        */
        Q_PROPERTY(qint32 maxDataPoints READ maxDataPoints WRITE setMaxDataPoints)
        /*!
        \brief Returns data with a relative date
        \getter useRelativeDate()
        \setter setUseRelativeDate()
        */
        Q_PROPERTY(bool useRelativeDate READ useRelativeDate WRITE setUseRelativeDate)
        /*!
        \brief If data is to be displayed for non trading days what is the data to be returned.
        \details If set to true it will return a null QVariant for the non trading days otherwise the previous value will be used
        \getter fillWithNull()
        \setter setFillWithNull()
        */
        Q_PROPERTY(bool fillWithNull READ fillWithNull WRITE setFillWithNull)
        /*!
        \brief Sets to include/exclude non trading days where no data was generated.
        \getter nonTradingDayFill()
        \setter setNonTradingDayFill()
        */
        Q_PROPERTY(NonTradingDayFill nonTradingDayFill READ nonTradingDayFill WRITE setNonTradingDayFill)
        /*!
        \brief Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield.
        \details true = Price, false = yield
        \getter usePriceForPricing()
        \setter setUsePriceForPricing()
        */
        Q_PROPERTY(bool usePriceForPricing READ usePriceForPricing WRITE setUsePriceForPricing)
        /*!
        \brief Indicates whether to use the average or the closing price in quote calculation.
        \getter useClosePrice()
        \setter setUseClosePrice()
        */
        Q_PROPERTY(bool useClosePrice READ useClosePrice WRITE setUseClosePrice)
        /*!
        \brief Amends the value from local to desired currency.
        \details Use the 3 letters ISO code for the currency
        \getter currency()
        \setter setCurrency()
        */
        Q_PROPERTY(QString currency READ currency WRITE setCurrency)
        /*!
        \brief Determine the frequency of the output. To be used in conjunction with periodicityAdjustment
        \getter periodicitySelection()
        \setter setPeriodicitySelection()
        */
        Q_PROPERTY(PeriodSelection periodicitySelection READ periodicitySelection WRITE setPeriodicitySelection)
        /*!
        \brief Determine the frequency and calendar type of the output. To be used in conjunction with periodicitySelection
        \getter periodicityAdjustment()
        \setter setPeriodicityAdjustment()
        */
        Q_PROPERTY(PeriodAdjustment periodicityAdjustment READ periodicityAdjustment WRITE setPeriodicityAdjustment)
        //! The end date of the period to retrieve data
        Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate)
        //! The first date of the period to retrieve data
        Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate)
        Q_DECLARE_PRIVATE(QBbgHistoricalDataRequest)
    public:
        //! Determine the frequency and calendar type of the output.
        enum PeriodAdjustment
        {
            ACTUAL /*!< These revert to the actual date from today (if the end date is left blank) or from the End Date */
            , CALENDAR /*!< For pricing fields, these revert to the last business day of the specified calendar period. */
            , FISCAL /*!< These periods revert to the fiscal period end for the company */
        };
        Q_ENUM(PeriodAdjustment)
        //! Frequency of historical data
        enum PeriodSelection
        {
            DAILY /*!< Daily frequency */
            , WEEKLY /*!< Weekly frequency */
            , MONTHLY /*!< Monthly frequency */
            , QUARTERLY /*!< Quarterly (3 months) frequency */
            , SEMI_ANNUALLY /*!< Semi-Annual (6 months) frequency */
            , YEARLY /*!< Yearly frequency */
        };
        Q_ENUM(PeriodSelection)
        //! Policy to handle non-trading days
        enum NonTradingDayFill
        {
            NON_TRADING_WEEKDAYS /*!< Show only weekdays */
            , ALL_CALENDAR_DAYS /*!< Show all days */
            , ACTIVE_DAYS_ONLY /*!< Show only trading days */
        };
        Q_ENUM(NonTradingDayFill)
        //! Destructor
        virtual ~QBbgHistoricalDataRequest();
        //! Creates an empty historical data request
        QBbgHistoricalDataRequest();
        //! Creates a copy of another historical data request
        QBbgHistoricalDataRequest(const QBbgHistoricalDataRequest& a);
        //! Copies another historical data request
        virtual QBbgHistoricalDataRequest& operator=(const QBbgHistoricalDataRequest& a);
        //! Checks if two requests are identical
        virtual bool operator==(const QBbgHistoricalDataRequest& a) const;
        /*!
        \sa calendarCode
        */
        virtual QString calendarCode() const;
        /*!
        \sa calendarCode
        */
        virtual void setCalendarCode(QString val);
        /*!
        \sa adjustmentFollowDPDF
        */
        virtual bool adjustmentFollowDPDF() const;
        /*!
        \sa adjustmentFollowDPDF
        */
        virtual void setAdjustmentFollowDPDF(bool val);
        /*!
        \sa adjustmentSplit
        */
        virtual bool adjustmentSplit() const;
        /*!
        \sa adjustmentSplit
        */
        virtual void setAdjustmentSplit(bool val);
        /*!
        \sa adjustmentAbnormal
        */
        virtual bool adjustmentAbnormal() const;
        /*!
        \sa adjustmentAbnormal
        */
        virtual void setAdjustmentAbnormal(bool val);
        /*!
        \sa adjustmentNormal
        */
        virtual bool adjustmentNormal() const;
        /*!
        \sa adjustmentNormal
        */
        virtual void setAdjustmentNormal(bool val);
        /*!
        \sa useRelativeDate
        */
        virtual bool useRelativeDate() const;
        /*!
        \sa useRelativeDate
        */
        virtual void setUseRelativeDate(bool val);
        /*!
        \sa maxDataPoints
        */
        virtual qint32 maxDataPoints() const;
        /*!
        \sa maxDataPoints
        */
        virtual void setMaxDataPoints(qint32 val);
        /*!
        \sa fillWithNull
        */
        virtual bool fillWithNull() const;
        /*!
        \sa fillWithNull
        */
        virtual void setFillWithNull(bool val);
        /*!
        \sa nonTradingDayFill
        */
        virtual  NonTradingDayFill nonTradingDayFill() const;
        /*!
        \sa nonTradingDayFill
        */
        virtual  void setNonTradingDayFill(NonTradingDayFill val);
        /*!
        \sa usePriceForPricing
        */
        virtual bool usePriceForPricing() const;
        /*!
        \sa usePriceForPricing
        */
        virtual  void setUsePriceForPricing(bool val);
        /*!
        \sa useClosePrice
        */
        virtual bool useClosePrice() const;
        /*!
        \sa useClosePrice
        */
        virtual void setUseClosePrice(bool val);
        /*!
        \sa currency
        */
        virtual QString currency() const;
        /*!
        \sa currency
        */
        virtual void setCurrency(QString val);
        /*!
        \sa periodicitySelection
        */
        virtual PeriodSelection periodicitySelection() const;
        /*!
        \sa periodicitySelection
        */
        virtual void setPeriodicitySelection(QBbgHistoricalDataRequest::PeriodSelection val);
        /*!
        \sa periodicityAdjustment
        */
        virtual PeriodAdjustment periodicityAdjustment() const;
        /*!
        \sa periodicityAdjustment
        */
        virtual void setPeriodicityAdjustment(PeriodAdjustment val);
        //! The last date of the period to retrieve data
        virtual const QDate& endDate() const;
        //! Set the last date of the period to retrieve data
        virtual void setEndDate(const QDate& val);
        //! The first date of the period to retrieve data
        virtual const QDate& startDate() const;
        //! Set the first date of the period to retrieve data
        virtual void setStartDate(const QDate& val);
        //! Reimplemented from QBbgAbstractRequest::setSecurity()
        virtual void setSecurity(const QBbgSecurity& val) override;
        using QBbgAbstractFieldRequest::setSecurity;
        //! Reimplemented from QBbgAbstractRequest::isValidReq()
        virtual bool isValidReq() const override;
    protected:
        virtual bool equalHistoricalFields(const QBbgHistoricalDataRequest& a) const;
        QBbgHistoricalDataRequest(QBbgHistoricalDataRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgHistoricalDataRequest);
#endif // QBbgHistoricalDataRequest_h__