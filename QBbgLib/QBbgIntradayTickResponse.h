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

#ifndef QBbgIntradayTickResponse_h__
#define QBbgIntradayTickResponse_h__

#include "QBbgAbstractIntradayResponse.h"
#include "QBbgAbstractIntradayRequest.h"
#include "QBbgProjectGlobals.h"
#include <QList>
namespace QBbgLib {
    class QBbgIntradayTickResponsePrivate;
    //! A response for intraday tick data series
    class QBBG_EXPORT QBbgIntradayTickResponse : public QBbgAbstractIntradayResponse
    {
        Q_GADGET
        /*!
        \brief Checks if the series contains any condition code
        \getter hasConditionCode
        */
        Q_PROPERTY(bool hasConditionCode READ hasConditionCode);
        /*!
        \brief Checks if the series contains any exchange code
        \getter hasExchangeCode
        */
        Q_PROPERTY(bool hasExchangeCode READ hasExchangeCode);
        /*!
        \brief Checks if the series contains any bank identifier code or market identifier code
        \getter hasBicMicCode
        */
        Q_PROPERTY(bool hasBicMicCode READ hasBicMicCode);
        /*!
        \brief Checks if the series contains any buy side broker code
        \getter hasBrokerBuyCode
        */
        Q_PROPERTY(bool hasBrokerBuyCode READ hasBrokerBuyCode);
        /*!
        \brief Checks if the series contains any sell side broker code
        \getter hasBrokerSellCode
        */
        Q_PROPERTY(bool hasBrokerSellCode READ hasBrokerSellCode);
        /*!
        \brief Checks if the series contains any reporting party side code
        \getter hasRpsCode
        */
        Q_PROPERTY(bool hasRpsCode READ hasRpsCode);
        /*!
        \brief Type of events in the series
        \getter type
        */
        Q_PROPERTY(QBbgAbstractIntradayRequest::EventType type READ type);
        Q_DECLARE_PRIVATE(QBbgIntradayTickResponse)
    public:
        //! Destructor
        virtual ~QBbgIntradayTickResponse();
        //! Creates an empty intraday tick response
        QBbgIntradayTickResponse();
        //! Creates a copy of another intraday tick response
        QBbgIntradayTickResponse(const QBbgIntradayTickResponse& other);
        //! Copies another intraday tick response
        virtual QBbgIntradayTickResponse& operator=(const QBbgIntradayTickResponse& other);
        //! Reimplemented from QBbgAbstractResponse::isEmpty()
        virtual bool isEmpty() const;
        //! Type of events in the series
        QBbgAbstractIntradayRequest::EventType type() const;
        /*!
        \brief The size related to the event
        \arg index The index of the object in the series
        \return 0 if index is out of range
        */
        Q_INVOKABLE virtual double tickSize(int index) const;
        /*!
        \brief The condition code related to the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeConditionCodes
        */
        Q_INVOKABLE virtual QString conditionCode(int index) const;
        /*!
        \brief The exchange code related to the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeExchangeCodes
        */
        Q_INVOKABLE virtual QString exchangeCode(int index) const;
        /*!
        \brief The bank identifier code or market identifier code related to the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeBicMicCodes
        */
        Q_INVOKABLE virtual QString bicMicCode(int index) const;
        /*!
        \brief The broker code related to the buy side of the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeBrokerCodes
        */
        Q_INVOKABLE virtual QString brokerBuyCode(int index) const;
        /*!
        \brief The broker code related to the sell side of the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeBrokerCodes
        */
        Q_INVOKABLE virtual QString brokerSellCode(int index) const;
        /*!
        \brief The reporting party side code related to the event
        \arg index The index of the object in the series
        \return A null string if index is out of range
        \sa QBbgIntradayTickRequest::includeRpsCodes
        */
        Q_INVOKABLE virtual QString rpsCode(int index) const;
        /*!
        \sa hasConditionCode
        */
        bool hasConditionCode() const;
        /*!
        \sa hasExchangeCode
        */
        bool hasExchangeCode() const;
        /*!
        \sa hasBicMicCode
        */
        bool hasBicMicCode() const;
        /*!
        \sa hasBrokerBuyCode
        */
        bool hasBrokerBuyCode() const;
        /*!
        \sa hasBrokerSellCode
        */
        bool hasBrokerSellCode() const;
        /*!
        \sa hasRpsCode
        */
        bool hasRpsCode() const;
    protected:
        QBbgIntradayTickResponse(QBbgIntradayTickResponsePrivate* dp);
        virtual void addValue(const QDateTime& dt, double val, double siz, const QString& cC, const QString& eC, const QString& mC, const QString& bbC, const QString& bsC, const QString& rC);
        void setType(const QBbgAbstractIntradayRequest::EventType& val);
        virtual void clear() override;
        void removeEmptyLists();
        virtual void saveToStream(QDataStream& stream) const;
        virtual void loadFromStream(QDataStream& stream);
        friend class QBbgRequestResponseWorker;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgIntradayTickResponse);
#endif // QBbgIntradayTickResponse_h__
