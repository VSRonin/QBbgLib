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

#ifndef QBbgAbstractResponse_h__
#define QBbgAbstractResponse_h__
#include <QString>
#include <QObject>
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgAbstractResponsePrivate;
    class QBbgAbstractWorker;
    class QBbgRequestResponseWorker;
    class QBBG_EXPORT QBbgAbstractResponse
    {
        Q_GADGET
    private:
        Q_DECLARE_PRIVATE(QBbgAbstractResponse)
        Q_PROPERTY(BbgErrorCodes errorCode READ errorCode)
        Q_PROPERTY(QString errorString READ errorString)
        Q_PROPERTY(QString errorMessage READ errorMessage)
        Q_PROPERTY(bool hasErrors READ hasErrors)
        Q_PROPERTY(bool isEmpty READ isEmpty)
        Q_PROPERTY(qint64 responseID READ getID)
        Q_PROPERTY(ResponseType responseType READ responseType)
    protected:
        enum : qint32
        {
            FirstFielded = 0x10
            , FirstRealTime = 0x20
        };
    public:
        enum BbgErrorCodesF
        {
            NoErrors = 0
            , ResponseError = 0x1
            , SecurityError = 0x2
            , InvalidInputs = 0x4
            , SessionError = 0x8
            , ServiceError = 0x10
            , FieldError = 0x20
            , UnknownError = 0x40
            , SessionStopped = 0x80
            , NoData = 0x100
        };
        Q_ENUM(BbgErrorCodesF)
        Q_DECLARE_FLAGS(BbgErrorCodes, BbgErrorCodesF)
        enum class ResponseType : qint32
        {
            Invalid=-1
            , BeqsResponse
            , HistoricalDataResponse = FirstFielded
            , ReferenceDataResponse
            , PortfolioDataResponse
            , IntraDayTickResponse = FirstRealTime
            , IntraDayBarResponse
        };
        Q_ENUM(ResponseType)
        virtual ~QBbgAbstractResponse() =0;
        QBbgAbstractResponse(ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractResponse(const QBbgAbstractResponse& other);
        virtual QBbgAbstractResponse& operator=(const QBbgAbstractResponse& other);
        virtual BbgErrorCodes errorCode() const;
        virtual QString errorString() const;
        virtual QString errorMessage() const;
        virtual bool hasErrors() const;
        virtual bool isEmpty() const =0;
        Q_INVOKABLE static QString bbgErrorCode2String(BbgErrorCodes a);
        virtual qint64 getID() const;
        virtual ResponseType responseType()const;
    protected:
        QBbgAbstractResponsePrivate* d_ptr;
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