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
    private:
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
        const QBbgAbstractIntradayRequest::EventType& Type() const;
        Q_INVOKABLE virtual double tickSize(int period) const;
        Q_INVOKABLE virtual QString conditionCode(int period) const;
        Q_INVOKABLE virtual QString exchangeCode(int period) const;
        Q_INVOKABLE virtual QString micCode(int period) const;
        Q_INVOKABLE virtual QString brokerBuyCode(int period) const;
        Q_INVOKABLE virtual QString brokerSellCode(int period) const;
        Q_INVOKABLE virtual QString rpsCode(int period) const;
        bool hasConditionCode() const;
        bool hasExchangeCode() const;
        bool hasMicCode() const;
        bool hasBrokerBuyCode() const;
        bool hasBrokerSellCode() const;
        bool hasRpsCode() const;
    protected:
        QBbgIntradayTickResponse(QBbgIntradayTickResponsePrivate* dp);
        virtual void addValue(const QDateTime& dt, double val, double siz, const QString& cC, const QString& eC, const QString& mC, const QString& bbC, const QString& bsC, const QString& rC);
        void setType(const QBbgAbstractIntradayRequest::EventType& val);
        virtual void clear() override;
        void removeEmptyLists();
        friend class QBbgRequestResponseWorker;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgIntradayTickResponse);
#endif // QBbgIntradayTickResponse_h__
