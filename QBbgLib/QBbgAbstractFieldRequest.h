#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgAbstractRequest.h"
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

#include <QString>
#include <QObject>
#include "QBbgOverride.h"
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBbgRequestGroup;
    class QBBG_EXPORT QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_GADGET
        Q_PROPERTY(QString field READ field WRITE setField)
        Q_PROPERTY(QBbgOverride overrides READ overrides WRITE setOverrides)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
        virtual ~QBbgAbstractFieldRequest() = 0;
        QBbgAbstractFieldRequest(RequestType typ);
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        virtual const QString& field() const;
        virtual void setField(const QString& val);
        virtual const QBbgOverride& overrides() const;
        virtual void setOverrides(const QBbgOverride& Overr);
        Q_INVOKABLE virtual void clearOverrides();
		virtual bool isValidReq() const;
	protected:
        virtual bool sameOverrides(const QBbgAbstractFieldRequest& a)const;
        QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestGroup;
	};
}
#endif // SingleBbgRequest_h__

