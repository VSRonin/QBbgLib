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
#include <QVariant>
#include <QDateTime>
namespace QBbgLib {
    class QBbgAbstractIntradayResponsePrivate;
    class QBbgRequestResponseWorker;
    //! Base class for Bloomberg Responses based on intraday requests
    class QBBG_EXPORT QBbgAbstractIntradayResponse : public QBbgAbstractResponse
    {
        Q_GADGET
        Q_DECLARE_PRIVATE(QBbgAbstractIntradayResponse)
    public:
        //! Destructor
        virtual ~QBbgAbstractIntradayResponse() = 0;
        //! Copies another intraday response
        virtual QBbgAbstractIntradayResponse& operator=(const QBbgAbstractIntradayResponse& a);
        Q_INVOKABLE virtual QVariant value(int period) const;
        Q_INVOKABLE virtual QDateTime dateTime(int period) const;
        Q_INVOKABLE virtual int findDate(const QDateTime& val) const;
        Q_INVOKABLE virtual int findValue(const QVariant& val) const;
    protected:
        virtual void addValue(const QDateTime& dt, const QVariant& val);
        virtual void clear();
        QBbgAbstractIntradayResponse() = delete;
        QBbgAbstractIntradayResponse(QBbgAbstractIntradayResponsePrivate* d);
        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgAbstractIntradayResponse_h__