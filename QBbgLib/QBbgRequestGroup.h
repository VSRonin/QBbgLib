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

#ifndef QBbgRequest_h__
#define QBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgSecurity.h"
#include "QBbgAbstractRequest.h"
#include <QList> 
#include <QHash>
#include <QString>
class QDataStream;
namespace QBbgLib {
    class QBbgRequestGroupPrivate;
    class QBbgRequestResponseWorker;
    class QBbgRequestGroup;
}
//! Write a request into a QDataStream
QBBG_EXPORT QDataStream& operator<<(QDataStream& stream, const QBbgLib::QBbgRequestGroup& obj);
//! Read a request from a QDataStream
QBBG_EXPORT QDataStream& operator>>(QDataStream& stream, QBbgLib::QBbgRequestGroup& obj);
namespace QBbgLib {
    /*!
    \brief A list of requests
    \details This class stores a list of requests to be sent to Bloomberg, the requests will be automatically arranged so that the least ammount of transactions will be sent to the Bloomberg server<br/>
    Each request will be indexed by a 64bit integer
    */
	class QBBG_EXPORT QBbgRequestGroup
	{
        Q_GADGET
        /*!
        \brief The number of requests in the list
        \getter size()
        */
        Q_PROPERTY(qint32 size READ size)
        /*!
        \brief Checks if the request is valid
        \getter isValidReq()
        */
        Q_PROPERTY(bool isValidReq READ isValidReq)
    private:
        Q_DECLARE_PRIVATE(QBbgRequestGroup)
        QBbgRequestGroupPrivate* d_ptr;
        virtual const QBbgAbstractRequest* const request(qint64 ID) const;
	public:
        //! Creates an empty list of requests
		QBbgRequestGroup();
        //! Creates a copy of another list of requests
		QBbgRequestGroup(const QBbgRequestGroup& a);
        //! Copies another list of requests
		QBbgRequestGroup& operator=(const QBbgRequestGroup& a);
		virtual ~QBbgRequestGroup();
        //! Returns the number of requests in the list
        virtual qint32 size() const;
        //! Returns the IDs of all the requests for the selected security
        Q_INVOKABLE virtual QList<qint64> findSecurity(const QBbgSecurity& Secur)const;
        //! Returns the IDs of all requests
        Q_INVOKABLE virtual QList<qint64> IDList() const;
        /*!
        \brief Adds a request to the list and returns its ID
        \details This function tries to add the request to the list, if unsuccessful it will return QBbgAbstractRequest::InvalidID
        \return The actual ID of the request that will be used.
        \warning If you used QBbgAbstractRequest::setID that value will be used as the preferred ID but there is no guarantee the actual request ID will be the selected one, always check the returned value
        */
        Q_INVOKABLE qint64 addRequest(const QBbgAbstractRequest& a);
        /*!
        \brief Adds a request to the list and returns its ID
        \details This function tries to add the request to the list, if unsuccessful it will return QBbgAbstractRequest::InvalidID
        \arg a The request to add
        \arg preferredID the preferred ID for the request
        \return The actual ID of the request that will be used.
        \warning If you used QBbgAbstractRequest::setID that value will be overridden by preferredID<br/>There is no guarantee the actual request ID will be the selected one, always check the returned value
        */
        Q_INVOKABLE qint64 addRequest(QBbgAbstractRequest& a, qint64 preferredID);
        //! Checks if all requests in the list are valid 
		bool isValidReq() const;
        //! Removes all requests from the list
        Q_INVOKABLE void clear();
        //! Returns a list of all types of requests in the list
        Q_INVOKABLE QList<QBbgAbstractRequest::RequestType> differentTypes() const;
        /*!
        \brief Returns the request corresponding to the given ID
        \arg ID The ID of the request to retrieve
        \tparam T A QBbgAbstractRequest (default) or a class derived from it
        \return A pointer to the request or NULL if the list does not contain a request of type T with the specified ID
        \details This function returns the request corresponding to a given ID.<br/>
        If the list does not contain a request with that ID, it will return NULL<br/>
        If you specify the template parameter to something different from QBbgAbstractRequest the method will return NULL also if the request with the selected ID is not of the type specified
        */
        Q_INVOKABLE
        template <class T = QBbgAbstractRequest> 
        const T* const getRequest(qint64 ID) const
        {
            static_assert(std::is_base_of<QBbgAbstractRequest, T>::value, "getRequest Template type must be derived from QBbgAbstractRequest");
            const QBbgAbstractRequest* const genericRq = request(ID);
            if(!genericRq)
                return nullptr;
            if (!std::is_same<QBbgAbstractRequest, T>::value) {
                switch (genericRq->requestType()) {
                case QBbgAbstractRequest::RequestType::ReferenceData:
                    if (!std::is_same<QBbgReferenceDataRequest, T>::value)
                        return nullptr;
                    break;
                case QBbgAbstractRequest::RequestType::HistoricalData:
                    if (!std::is_same<QBbgHistoricalDataRequest, T>::value)
                        return nullptr;
                    break;
                case QBbgAbstractRequest::RequestType::PortfolioData:
                    if (!std::is_same<QBbgPortfolioDataRequest, T>::value)
                        return nullptr;
                    break;
                default:
                    Q_UNREACHABLE(); //Unhandled request type
                }
            }
            return static_cast<const T* const>(genericRq);
        }
	protected:
        QBbgAbstractRequest* FindEditRequest(qint64 ID);
		void RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID = 1i64)const;
        QList<QString> differentServices() const;
        virtual void saveToStream(QDataStream& stream) const;
        virtual void loadFromStream(QDataStream& stream);
        friend class QBbgRequestResponseWorker;
        friend QDataStream& ::operator<<(QDataStream& stream, const QBbgRequestGroup& obj);
        friend QDataStream& ::operator>>(QDataStream& stream, QBbgRequestGroup& obj);
	};
}
Q_DECLARE_METATYPE(QBbgLib::QBbgRequestGroup);
#endif // QBbgRequest_h__