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

#ifndef QBbgAbstractIntradayResponse_h__
#define QBbgAbstractIntradayResponse_h__

#include "QBbgAbstractResponse.h"
#include <QDateTime>
namespace QBbgLib {
    class QBbgAbstractIntradayResponsePrivate;
    class QBbgRequestResponseWorker;
    //! Base class for Bloomberg Responses based on intraday requests
    class QBBG_EXPORT QBbgAbstractIntradayResponse : public QBbgAbstractResponse
    {
        Q_GADGET
        /*!
        \brief Number of values in the series
        \getter size()
        */
        Q_PROPERTY(int size READ size)
        Q_DECLARE_PRIVATE(QBbgAbstractIntradayResponse)
    public:
        //! Destructor
        virtual ~QBbgAbstractIntradayResponse() = 0;
        //! Copies another intraday response
        virtual QBbgAbstractIntradayResponse& operator=(const QBbgAbstractIntradayResponse& a);
        Q_INVOKABLE virtual double value(int period) const;
        Q_INVOKABLE virtual QDateTime dateTime(int period) const;
        //! Number of values in the series
        virtual int size() const;
    protected:
        virtual void addValue(const QDateTime& dt, double val);
        virtual void clear();
        QBbgAbstractIntradayResponse() = delete;
        QBbgAbstractIntradayResponse(QBbgAbstractIntradayResponsePrivate* d);
    };
}
#endif // QBbgAbstractIntradayResponse_h__