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

#ifndef QBbgAbstractResponse_h__
#define QBbgAbstractResponse_h__
#include <QString>
#include <QObject>
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgAbstractResponsePrivate;
    class QBbgAbstractWorker;
    class QBbgRequestResponseWorker;
    //! Base Class for Bloomberg Responses
    class QBBG_EXPORT QBbgAbstractResponse
    {
        Q_GADGET
        /*!
        \brief The error code associated with the response
        \getter errorCode()
        */
        Q_PROPERTY(BbgErrorCodes errorCode READ errorCode)
        /*!
        \brief String representation of the error
        \getter errorString()
        */
        Q_PROPERTY(QString errorString READ errorString)
        /*!
        \brief The details of the error
        \getter errorMessage()
        */
        Q_PROPERTY(QString errorMessage READ errorMessage)
        /*!
        \brief Checks if the response has any error
        \getter hasErrors()
        */
        Q_PROPERTY(bool hasErrors READ hasErrors)
        /*!
        \brief Check if the response contains any value
        \getter isEmpty()
        */
        Q_PROPERTY(bool isEmpty READ isEmpty)
        /*!
        \brief The ID of the response
        \getter getID()
        */
        Q_PROPERTY(qint64 responseID READ getID)
        /*!
        \brief Returns the type of the current response
        \getter responseType()
        */
        Q_PROPERTY(ResponseType responseType READ responseType)
    private:
        Q_DECLARE_PRIVATE(QBbgAbstractResponse)
    protected:
        enum : qint32
        {
            FirstFielded = 0x10
            , FirstRealTime = 0x20
        };
    public:
        //! Flags representing possible errors
        enum BbgErrorCodesF
        {
            NoErrors = 0 /*!< No error occurred*/
            , ResponseError = 0x1 /*!< Response error */
            , SecurityError = 0x2 /*!< Invalid security */
            , InvalidInputs = 0x4 /*!< Invalid inputs */
            , SessionError = 0x8 /*!< Session error */
            , ServiceError = 0x10 /*!< Service error */
            , FieldError = 0x20 /*!< Invalid field */
            , UnknownError = 0x40 /*!< Unknown error */
            , SessionStopped = 0x80 /*!< Process stopped by user*/
            , NoData = 0x100 /*!< No data available */
        };
        Q_ENUM(BbgErrorCodesF)
        Q_DECLARE_FLAGS(BbgErrorCodes, BbgErrorCodesF)
        //! Type of response
        enum class ResponseType : qint32
        {
            Invalid=-1 /*!< Invalid Type */
            , BeqsResponse /*!< Currently Unavailable */
            , HistoricalDataResponse = FirstFielded /*!< Response associated with an historical data request */
            , ReferenceDataResponse /*!< Response associated with a reference data request */
            , PortfolioDataResponse  /*!< Response associated with a portfolio request */
            , IntraDayTickResponse = FirstRealTime /*!< Currently Unavailable */
            , IntraDayBarResponse  /*!< Currently Unavailable */
        };
        Q_ENUM(ResponseType)
        //! Destructor
        virtual ~QBbgAbstractResponse() =0;
        //! Copies another response
        virtual QBbgAbstractResponse& operator=(const QBbgAbstractResponse& other);
        //! The error code associated with the response
        virtual BbgErrorCodes errorCode() const;
        /*!
        \brief String representation of the error
        \details This is equivalent to bbgErrorCode2String(errorCode())
        */
        virtual QString errorString() const;
        /*!
        \brief The details of the error
        \details This string contains more detailed information regarding the error
        */
        virtual QString errorMessage() const;
        /*!
        \brief Checks if the response has any error
        \details This is equivalent to errorCode() == BbgErrorCodesF::NoErrors
        */
        virtual bool hasErrors() const;
        //! Check if the response contains any value
        virtual bool isEmpty() const =0;
        //! Converts an error code to the its string representation
        Q_INVOKABLE static QString bbgErrorCode2String(BbgErrorCodes a);
        /*!
        \brief The ID of the response
        \details This is the same as the request associated with this response
        */
        virtual qint64 getID() const;
        //! Returns the type of the current response
        virtual ResponseType responseType()const;
    protected:
        QBbgAbstractResponsePrivate* d_ptr;
        QBbgAbstractResponse() = delete;
        QBbgAbstractResponse(QBbgAbstractResponsePrivate* d);
        virtual void setErrorCode(BbgErrorCodes ErrCd,const QString& errMsg=QString());
        virtual void setID(qint64 val);
        static QString responseTypeToString(ResponseType a);
        static ResponseType stringToResponseType(QString a);

        friend class QBbgAbstractWorker;
        friend class QBbgRequestResponseWorker;
    };
}
/*!
\brief Allows QBbgAbstractResponse::ResponseType to be used as a key of a QHash
\relates QBbgLib::QBbgAbstractResponse
*/
QBBG_EXPORT uint qHash(QBbgLib::QBbgAbstractResponse::ResponseType key, uint seed = 0);
Q_DECLARE_OPERATORS_FOR_FLAGS(QBbgLib::QBbgAbstractResponse::BbgErrorCodes)
#endif // QBbgAbstractResponse_h__