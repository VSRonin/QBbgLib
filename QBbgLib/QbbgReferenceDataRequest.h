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
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QbbgReferenceDataRequest_h__
#define QbbgReferenceDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QObject>
namespace QBbgLib {
    class QBbgReferenceDataRequestPrivate;
    class QBBG_EXPORT QBbgReferenceDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        Q_PROPERTY(bool useUTCtime READ useUTCtime WRITE setUseUTCtime)
        Q_DECLARE_PRIVATE(QBbgReferenceDataRequest)
    public:
        virtual ~QBbgReferenceDataRequest();
    	QBbgReferenceDataRequest();
        QBbgReferenceDataRequest(const QBbgReferenceDataRequest& a);
        virtual QBbgReferenceDataRequest& operator=(const QBbgReferenceDataRequest& a);
        virtual bool operator==(const QBbgReferenceDataRequest& a) const;
        bool useUTCtime() const;
        void setUseUTCtime(bool a);
        virtual void setSecurity(const QBbgSecurity& val);
    protected:
        QBbgReferenceDataRequest(QBbgReferenceDataRequestPrivate* d);
    };
}
#endif // QbbgReferenceDataRequest_h__