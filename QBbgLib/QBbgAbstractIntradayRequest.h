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

#ifndef QBbgIntradayTickRequest_h__
#define QBbgIntradayTickRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDateTime>
#include <QObject>
namespace QBbgLib {
    class QBbgAbstractIntradayRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBBG_EXPORT QBbgAbstractIntradayRequest : public QBbgAbstractRequest
    {
        Q_GADGET
        /*! 
        \brief The last date/time of the period to retrieve data
        \getter endDateTime
        \setter setEndDateTime
        */
        Q_PROPERTY(QDateTime endDateTime READ endDateTime WRITE setEndDateTime)
        /*!
        \brief The first date/time of the period to retrieve data
        \getter startDateTime
        \setter setStartDateTime
        */
        Q_PROPERTY(QDateTime startDateTime READ startDateTime WRITE setStartDateTime)
        /*!
        \brief The type of event to retrieve
        \getter eventType
        \setter setEventType
        */
        Q_PROPERTY(QDateTime eventType READ eventType WRITE setEventType)
        Q_DECLARE_PRIVATE(QBbgAbstractIntradayRequest)
    public:
        //! Type of event to capture
        enum class EventType{
            Invalid /*!< Invalid Request Event Type*/
            , TRADE /*!< Corresponds to LAST_PRICE */
            , BID /*!< Depending on the exchange bid ticks will be returned as BID, BID_BEST or BEST_BID. */
            , ASK /*!< Depending on the exchange ask ticks will be returned as ASK, ASK_BEST or BEST_ASK. */
            , BID_BEST /*!< Depending on the exchange bid ticks will be returned as BID, BID_BEST or BEST_BID. */
            , ASK_BEST /*!< Depending on the exchange ask ticks will be returned as ASK, ASK_BEST or BEST_ASK. */
            , MID_PRICE /*!< Only applies to the LSE.<br/>The mid price is equal to the sum of the best bid price and the best offer price divided by two, and rounded up to be consistent with the relevant price format. */
            , AT_TRADE /*!< Automatic trade for London Sets stocks. */
            , BEST_BID /*!< Depending on the exchange bid ticks will be returned as BID, BID_BEST or BEST_BID. */
            , BEST_ASK /*!< Depending on the exchange ask ticks will be returned as ASK, ASK_BEST or BEST_ASK. */
        };
        Q_ENUM(EventType)
        //! Destructor
        virtual ~QBbgAbstractIntradayRequest() =0;
        //! Copies another tick data request
        virtual QBbgAbstractIntradayRequest& operator=(const QBbgAbstractIntradayRequest& a);
        //! The last date/time of the period to retrieve data
        virtual const QDateTime& endDateTime() const;
        //! Set the last date/time of the period to retrieve data
        virtual void setEndDateTime(const QDateTime& val);
        //! The first date/time of the period to retrieve data
        virtual const QDateTime& startDateTime() const;
        //! Set the first date/time of the period to retrieve data
        virtual void setStartDateTime(const QDateTime& val);
        //! Reimplemented from QBbgAbstractRequest::setSecurity()
        virtual void setSecurity(const QBbgSecurity& val) override;
        //! Reimplemented from QBbgAbstractRequest::isValidReq()
        virtual bool isValidReq() const override;
        //! Returns the type of event to retrieve
        virtual EventType eventType() const;
        //! Set the type of event to retrieve
        virtual void setEventType(EventType val);
    protected:
        QBbgAbstractIntradayRequest() = delete;
        QBbgAbstractIntradayRequest(QBbgAbstractIntradayRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
    };
}
#endif // QBbgIntradayTickRequest_h__
