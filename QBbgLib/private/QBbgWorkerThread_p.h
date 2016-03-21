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

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#ifndef QBbgWorkerThread_h__
#define QBbgWorkerThread_h__
#include <QThread>
namespace QBbgLib {
    class QBbgAbstractWorker;
    class QBbgAbstractResponse;
    class QBbgWorkerThread : public QThread
    {
        Q_OBJECT   
    public:
        QBbgWorkerThread(QBbgAbstractWorker* wrk, QObject* parent = NULL);
        virtual ~QBbgWorkerThread();
    private:
        QBbgAbstractWorker* m_worker;
    protected:
        void createConnections();
    public slots:
        void run();
        void stop();
    signals:
        void started();
        void stopped();
        void dataRecieved(qint64 reID, QBbgAbstractResponse* res);
        void progress(qint32 pct);
        void finished();
    };
}
#endif // QBbgWorkerThread_h__