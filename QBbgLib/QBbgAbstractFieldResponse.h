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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QBbgAbstractFieldResponse_h__
#define QBbgAbstractFieldResponse_h__
#include "QBbgAbstractResponse.h"
namespace QBbgLib {
    class QBbgAbstractFieldResponsePrivate;
    class QBbgRequestResponseWorker;
    class QBBG_EXPORT QBbgAbstractFieldResponse : public QBbgAbstractResponse
    {
        Q_DECLARE_PRIVATE(QBbgAbstractFieldResponse)
    public:
        virtual ~QBbgAbstractFieldResponse() = 0;
        QBbgAbstractFieldResponse(ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractFieldResponse(const QBbgAbstractFieldResponse& a);
        virtual QBbgAbstractFieldResponse& operator=(const QBbgAbstractFieldResponse& a);
        virtual const QString& header() const;
    protected:
        QBbgAbstractFieldResponse(QBbgAbstractFieldResponsePrivate* d);
        virtual void setHeader(const QString& Header = QString());

        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgAbstractFieldResponse_h__