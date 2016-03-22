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

#ifndef QBbgAbstractRequest_h__
#define QBbgAbstractRequest_h__
#include <QObject>
#include "QBbgSecurity.h"
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate;
    class QBbgRequestGroup;
    class QBbgRequestResponseWorker;
    //! Base class for all requests sent to Bloomberg
    class QBBG_EXPORT QBbgAbstractRequest
    {
        Q_GADGET
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        Q_PROPERTY(qint64 requestID READ getID WRITE setID)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_PROPERTY(RequestType requestType READ requestType)
    protected:
        enum : qint32
        {
            FirstFielded=0x10
            , FirstRealTime = 0x20
        };
        enum class ServiceType
        {
            NoService=0
            , refdata=1
            , mktdata
            , mktvwap
            , mktbar
            , apiflds
            , pagedata
            , tasvc
            , apiauth
        };
    public:
        enum SpecialIDs { 
            InvalidID = -1024 
        };
        Q_ENUM(SpecialIDs)
        enum class RequestType : qint32
        {
            Invalid =-1
            , Beqs
            , HistoricalData = FirstFielded
            , ReferenceData
            , PortfolioData
            , IntraDayTick = FirstRealTime
            , IntraDayBar
        };
        Q_ENUM(RequestType)
    protected:
        Q_DECLARE_PRIVATE(QBbgAbstractRequest)
        QBbgAbstractRequestPrivate* d_ptr;
        QBbgAbstractRequest(QBbgAbstractRequestPrivate* d);
        static ServiceType serviceForRequest(RequestType a);
        static QString serviceStringForRequest(RequestType a);
        static QString serviceTypeToString(ServiceType a);
        static ServiceType stringToServiceType(const QString& a);
        static QString requestTypeToString(RequestType a);
        static RequestType stringToRequestType(QString a);
    public:
        //! Destructor
        virtual ~QBbgAbstractRequest() =0;
        //! Creates a request of type typ
        QBbgAbstractRequest(RequestType typ);
        //! Creates a copy of another request
        QBbgAbstractRequest(const QBbgAbstractRequest& other);
        //! Copies another request
        virtual QBbgAbstractRequest& operator=(const QBbgAbstractRequest& other);
        //! Returns the security associated with the request
        virtual const QBbgSecurity& security() const;
        //! Sets the security for the current request to the specified one
        virtual void setSecurity(const QBbgSecurity& val);
        /*!
        \brief Overloaded from setSecurity
        \arg SecName Name of the security to add
        \arg SecKey Yellow key or code identifier for the security
        \details Sets the security for the current request to the specified one
        */
        virtual void setSecurity(const QString& SecName, QBbgSecurity::YellowKeys SecKey);
        /*!
        \brief Returns the current ID for the request
        \details If the ID is not set or invalid SpecialIDs::InvalidID will be returned
        */
        virtual qint64 getID() const;
        /*!
        \brief Set the ID associated to the current request
        \note Negative values are reserved so only 65 bits can be used to determine the ID
        */
        virtual void setID(qint64 val);
        //! Checks if the request is valid
        virtual bool isValidReq() const;
        //! Returns the type of request
        virtual RequestType requestType() const;
        friend class QBbgRequestGroup;
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestResponseWorkerPrivate;
        friend class QBbgRequestResponseWorker;
    };
}
/*!
\brief Allows QBbgAbstractRequest::RequestType to be used as a key of a QHash
\relates QBbgLib::QBbgAbstractRequest
*/
QBBG_EXPORT uint qHash(QBbgLib::QBbgAbstractRequest::RequestType key, uint seed = 0);
#endif // QBbgAbstractRequest_h__