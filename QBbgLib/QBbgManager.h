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

#ifndef QBbgManager_h__
#define QBbgManager_h__
#include <QObject>
#include "QBbgProjectGlobals.h"
#include <QHash>
#include <QList>
//! Namespace containing all classes of the QBbgLib
namespace QBbgLib {
    class QBbgManagerPrivate;
    class QBbgRequestGroup;
    class QBbgAbstractRequest;
    class QBbgAbstractResponse;
    class QBbgReferenceDataRequest;
    class QBbgHistoricalDataRequest;
    class QBbgPortfolioDataRequest;
    class QBbgReferenceDataResponse;
    class QBbgHistoricalDataResponse;
    class QBbgPortfolioDataResponse;
    class QBbgIntradayTickRequest;
    class QBbgIntradayTickResponse;
    class QBbgAbstractWorker;
    /*!
    \brief The central Bloomberg manager
    \details This is the main class of the library.<br/>
    This class is in charge of sending the requests and collecting the responses from Bloomberg.
    \warning A QCoreApplication must be created before sending any request
    */
    class QBBG_EXPORT QBbgManager : public QObject
    {
        Q_OBJECT
        /*!
        \brief A list of all available result group IDs
        \getter getResultGroups()
        */
        Q_PROPERTY(QList<quint32> resultGroups READ getResultGroups)
    private:
        Q_DECLARE_PRIVATE(QBbgManager)
    protected:
        QBbgManagerPrivate* d_ptr;
        QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*>  >::iterator createThread(const QBbgRequestGroup& rq);
        const QBbgAbstractResponse* const getResultGeneric(quint32 group, qint64 id) const;
    public:
        //! Constructs a Bloomberg manager
        QBbgManager(QObject* parent = nullptr);
        //! Destructor
        virtual ~QBbgManager();
        /*!
        \brief Starts the group of requests asynchronously 
        \details This function will start a group of requests and return its ID.<br/>
        When the process is completed it will emit finished with the same ID as the returned one.<br/>
        If the request is invalid 0 will be returned.
        \note The returned ID does not depend from the one set in any single request
        */
        Q_INVOKABLE quint32 startRequest(const QBbgRequestGroup& rq);
        /*!
        \brief Starts the request asynchronously
        \details This function will start a request and return its ID.<br/>
        When the process is completed it will emit finished with the same ID as the returned one.<br/>
        If the request is invalid 0 will be returned.
        \note The returned ID does not depend from the one set in the single request
        */
        Q_INVOKABLE quint32 startRequest(const QBbgAbstractRequest& rq);
        /*!
        \brief Starts the group of requests synchronously
        \details This function will start a group of requests and return its ID.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid 0 will be returned.
        \note The returned ID does not depend from the one set in any single request
        */
        Q_INVOKABLE quint32 processRequestID(const QBbgRequestGroup& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its ID.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid 0 will be returned.
        \note The returned ID does not depend from the one set in the single request
        */
        Q_INVOKABLE quint32 processRequestID(const QBbgAbstractRequest& rq);
        /*!
        \brief Starts the group of requests synchronously
        \details This function will start a group of requests and return the individual results.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid the program will crash.
        \return A hash table with key the ID of the request and value a pointer to the response that has then to be dynamic_casted into the appropriate type
        \deprecated Use processRequestID(const QBbgRequestGroup&) and getResult() instead
        */
        const QHash<qint64, QBbgAbstractResponse* >& processRequest(const QBbgRequestGroup& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its result.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid a null pointer will be returned.
        */
        const QBbgReferenceDataResponse* const processRequest(const QBbgReferenceDataRequest& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its result.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid a null pointer will be returned.
        */
        const QBbgHistoricalDataResponse* const processRequest(const QBbgHistoricalDataRequest& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its result.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid a null pointer will be returned.
        */
        const QBbgPortfolioDataResponse* const processRequest(const QBbgPortfolioDataRequest& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its result.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid a null pointer will be returned.
        */
        const QBbgIntradayTickResponse* const processRequest(const QBbgIntradayTickRequest& rq);
        /*!
        \brief Starts the request synchronously
        \details This function will start a request and return its result.<br/>
        The program will wait until the process is finished.<br/>
        If the request is invalid a null pointer will be returned.
        */
        const QBbgAbstractResponse* const processRequest(const QBbgAbstractRequest& rq);
        /*!
        \brief Returns a result
        \details This method will return the result identified by the group ID and the ID within the group.<br/>
        If the selected result does not exist, it has not been downloaded yet or is not of type T a null pointer will be returned.
        \tparam T The type of response to retrieve
        */
        Q_INVOKABLE
        template <class T = QBbgAbstractResponse> 
        const T* const getResult(quint32 group, qint64 id) const
        {
            static_assert(std::is_base_of<QBbgAbstractResponse, T>::value, "getResult Template type must be derived from QBbgAbstractResponse");
            const QBbgAbstractResponse* const genericRes = getResultGeneric(group, id);
            if (!genericRes)
                return nullptr;
            if (!std::is_same<QBbgAbstractResponse, T>::value) {
                switch (genericRes->responseType()) {
                case QBbgAbstractResponse::ResponseType::ReferenceDataResponse:
                    if (!std::is_same<QBbgReferenceDataResponse, T>::value)
                        return nullptr;
                    break;
                case QBbgAbstractResponse::ResponseType::HistoricalDataResponse:
                    if (!std::is_same<QBbgHistoricalDataResponse, T>::value)
                        return nullptr;
                    break;
                case QBbgAbstractResponse::ResponseType::PortfolioDataResponse:
                    if (!std::is_same<QBbgPortfolioDataResponse, T>::value)
                        return nullptr;
                    break;
                case QBbgAbstractResponse::ResponseType::IntraDayTickResponse:
                    if (!std::is_same<QBbgIntradayTickResponse, T>::value)
                        return nullptr;
                    break;
                default:
                    Q_UNREACHABLE(); //Unhandled response type
                }
            }
            Q_ASSERT(dynamic_cast<const T* const>(genericRes));
            return static_cast<const T* const>(genericRes);
        }
        //! Returns a list of all available result group IDs
        QList<quint32> getResultGroups() const;
        //! Returns a list of all request IDs associated with the given group ID
        Q_INVOKABLE QList<qint64> getResultIDs(quint32 group) const;
    protected slots:
        void handleResponse(qint64 reID, QBbgAbstractResponse* res);
        void handleThreadFinished();
    signals:
        //! When a single result is recieved its group ID and its id inside the group are emitted
        void recieved(quint32, qint64);
        //! When a group of results is processed this will be emitted with the associated group ID
        void finished(quint32);
        //! This will emitted when no more request are running
        void allFinished();
    };
}
#endif // QBbgManager_h__
