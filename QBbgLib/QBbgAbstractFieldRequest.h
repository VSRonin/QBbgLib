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

#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgAbstractRequest.h"
#include <QString>
#include <QObject>
#include "QBbgOverride.h"
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBbgRequestGroup;
    /*!
    \brief Request with fields and overrides
    \details This class represents all requests that can supply a field and a set of overrides
    */
    class QBBG_EXPORT QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_GADGET
        Q_PROPERTY(QString field READ field WRITE setField)
        Q_PROPERTY(QBbgOverride overrides READ overrides WRITE setOverrides)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
        //! Destructor
        virtual ~QBbgAbstractFieldRequest() = 0;
        //! Creates a request of type typ
        QBbgAbstractFieldRequest(RequestType typ);
        //! Creates a request that is a copy of another
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        //! Checks if two requests are identical
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        //! Copies another request
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        //! The field related to the request
        virtual const QString& field() const;
        /*! 
        \brief Sets the field for the request
        \details The input will be normalized. Spaces will be replaced by _ and the string will be capitalised
        */
        virtual void setField(const QString& val);
        //! Returns the set of overrides applied to the request
        virtual const QBbgOverride& overrides() const;
        //! Sets the overrides to apply to the request
        virtual void setOverrides(const QBbgOverride& Overr);
        //! Remove all overrides from a request
        Q_INVOKABLE virtual void clearOverrides();
        //! Reimplemented from QBbgAbstractRequest::isValidReq
		virtual bool isValidReq() const;
	protected:
        virtual bool sameOverrides(const QBbgAbstractFieldRequest& a)const;
        QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestGroup;
	};
}
#endif // SingleBbgRequest_h__

