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

#ifndef QBbgAbstractWorker_h__
#define QBbgAbstractWorker_h__
#include <QObject>
#include <QVariant>
#include <QScopedPointer>
#include "QBbgAbstractResponse.h"
namespace BloombergLP {
    namespace blpapi {
        class SessionOptions;
        class Element;
        class Event;
        class Session;
    }
}
namespace QBbgLib {
    class QBbgAbstractResponse;
    class QBbgRequestGroup;
    class QBbgAbstractWorker : public QObject
    {
        Q_OBJECT
    public:
        QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent=NULL);
        virtual ~QBbgAbstractWorker();
        virtual bool isAvailable() const;
        virtual void stop();
    protected:
        bool sessionRunning() const;
        void setSessionRunning(bool val);
        virtual void handleResponseEvent(const BloombergLP::blpapi::Event& event, bool isFinal) = 0;
        virtual void setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err, const QString& errMsg) const;
        virtual void setResponseID(QBbgAbstractResponse* res, qint64 corrID) const;
        virtual QVariant elementToVariant(BloombergLP::blpapi::Element& val);
        QScopedPointer<BloombergLP::blpapi::Session>& session();
    private:
        bool m_SessionRunning;
        QScopedPointer<BloombergLP::blpapi::Session> m_session;
    public slots:
        virtual void start() = 0;
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