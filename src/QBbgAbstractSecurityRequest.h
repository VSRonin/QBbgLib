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

#ifndef QBbgAbstractSecurityRequest_h__
#define QBbgAbstractSecurityRequest_h__
#include <QObject>
#include "QBbgAbstractRequest.h"
#include "QBbgSecurity.h"
#include <qbbglib_global.h>
class QDataStream;
namespace QBbgLib {
class QBbgAbstractSecurityRequest;
class QBbgAbstractSecurityRequestPrivate;
}
namespace QBbgLib {

//! Base class for all requests sent to Bloomberg that require a security
class QBBGLIB_EXPORT QBbgAbstractSecurityRequest : public QBbgAbstractRequest
{
    Q_GADGET
    /*!
    \brief The security associated with the request
    \getter security()
    \setter setSecurity()
    */
    Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
protected:
    Q_DECLARE_PRIVATE(QBbgAbstractSecurityRequest)
    QBbgAbstractSecurityRequest(QBbgAbstractSecurityRequestPrivate *d);
    QBbgAbstractSecurityRequest() = delete;
    void saveToStream(QDataStream &stream) const override;
    void loadFromStream(QDataStream &stream) override;
    void applyRequest(QJsonObject& obj) const override;
public:
    //! Destructor
    virtual ~QBbgAbstractSecurityRequest() = 0;
    //! Copies another request
    virtual QBbgAbstractSecurityRequest &operator=(const QBbgAbstractSecurityRequest &other);
    //! Returns the security associated with the request
    virtual const QBbgSecurity &security() const;
    //! Sets the security for the current request to the specified one
    virtual void setSecurity(const QBbgSecurity &val);
    /*!
    \brief Overloaded from setSecurity
    \arg SecName Name of the security to add
    \arg SecKey Yellow key or code identifier for the security
    \details Sets the security for the current request to the specified one
    */
    virtual void setSecurity(const QString &SecName, QBbgSecurity::YellowKeys SecKey);


    //! Checks if the request is valid
    bool isValidReq() const override;
    //! Checks if two requests are identical
    virtual bool operator==(const QBbgAbstractSecurityRequest &other) const;
};
}

#endif
