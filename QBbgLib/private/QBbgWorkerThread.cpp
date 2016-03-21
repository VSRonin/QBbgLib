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

#include "private/QBbgWorkerThread_p.h"
#include "private/QBbgAbstractWorker_p.h"
namespace QBbgLib {

    QBbgWorkerThread::QBbgWorkerThread(QBbgAbstractWorker* wrk, QObject* parent)
        :QThread(parent)
        , m_worker(wrk)
    {
        createConnections();
    }
    void QBbgWorkerThread::run()
    {
        m_worker->start();
        exec();
    }
    QBbgWorkerThread::~QBbgWorkerThread()
    {
        while (isRunning()) {
            quit();
            wait(2000);
        }
        Q_ASSERT_X(!isRunning(), "~QBbgWorkerThread()", "Destroying thread while still running");
    }
    void QBbgWorkerThread::createConnections()
    {
        connect(m_worker, &QBbgAbstractWorker::started, this, &QBbgWorkerThread::started);
        connect(m_worker, &QBbgAbstractWorker::stopped, this, &QBbgWorkerThread::stopped);
        connect(m_worker, &QBbgAbstractWorker::dataRecieved, this, &QBbgWorkerThread::dataRecieved);
        connect(m_worker, &QBbgAbstractWorker::progress, this, &QBbgWorkerThread::progress);
        connect(m_worker, &QBbgAbstractWorker::finished, this, &QBbgWorkerThread::finished);
        connect(this, &QBbgWorkerThread::finished, this, &QBbgWorkerThread::deleteLater);
        connect(m_worker, &QBbgAbstractWorker::finished, this, &QBbgWorkerThread::quit);
        connect(m_worker, &QBbgAbstractWorker::stopped, this, &QBbgWorkerThread::quit);
    }

    void QBbgWorkerThread::stop()
    {
        m_worker->stop();
    }


}