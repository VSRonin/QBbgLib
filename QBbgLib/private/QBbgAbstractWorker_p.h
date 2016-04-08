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

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#ifndef QBbgAbstractWorker_h__
#define QBbgAbstractWorker_h__
#include <QObject>
#include <QVariant>
#include <memory>
#include "QBbgAbstractResponse.h"
#include <blpapi_session.h>
namespace QBbgLib {
    class QBbgAbstractResponse;
    class QBbgRequestGroup;
    class QBbgAbstractWorker : public QObject, public BloombergLP::blpapi::EventHandler
    {
        Q_OBJECT
    public:
        QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent);
        virtual ~QBbgAbstractWorker() = 0;
        virtual bool isAvailable() const;
        virtual void stop();
    protected:
        bool sessionRunning() const;
        void setSessionRunning(bool val);
        virtual void handleResponseEvent(const BloombergLP::blpapi::Event& event, bool isFinal) = 0;
        virtual void setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err, const QString& errMsg) const;
        virtual void setResponseID(QBbgAbstractResponse* res, qint64 corrID) const;
        virtual QVariant elementToVariant(BloombergLP::blpapi::Element& val);
        std::unique_ptr<BloombergLP::blpapi::Session>& session();
    private:
        bool m_SessionRunning;
        std::unique_ptr<BloombergLP::blpapi::Session> m_session;
    public slots:
        virtual bool start() = 0;
        virtual void setRequest(const QBbgRequestGroup& req)=0;
    signals:
        void started();
        void stopped();
        void dataRecieved(qint64 reID, QBbgAbstractResponse* res);
        void progress(qint32 pct);
        void finished();
    };
}
#endif // QBbgAbstractWorker_h__