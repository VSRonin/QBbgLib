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

#include "QBbgManager.h"
#include "private/QBbgManager_p.h"
#include "QBbgRequestGroup.h"
#include <limits>
#include <QEventLoop>
#ifndef QBbg_OFFLINE
#include "private/QBbgRequestResponseWorker_p.h"
#include <blpapi_sessionoptions.h>
#endif
#include <QCoreApplication>
#include "QBbgReferenceDataRequest.h"
#include "QBbgPortfolioDataRequest.h"
#include "QBbgHistoricalDataRequest.h"
#include "QBbgReferenceDataResponse.h"
#include "QBbgPortfolioDataResponse.h"
#include "QBbgHistoricalDataResponse.h"
#include "QBbgIntradayTickRequest.h"
#include "QBbgIntradayTickResponse.h"
#include <QThread>
namespace QBbgLib {


    QBbgManagerPrivate::QBbgManagerPrivate(QBbgManager* qp)
        :q_ptr(qp)
        , m_options(nullptr)
    {
        #ifndef QBbg_OFFLINE
        m_options = new BloombergLP::blpapi::SessionOptions;
        m_options->setServerHost("localhost");
        m_options->setServerPort(8194);
        m_options->setMaxPendingRequests(std::numeric_limits<qint32>::max() - 2);
        m_options->setAutoRestartOnDisconnection(false);
        #endif
    }
    QBbgManager::~QBbgManager()
    {
        //disconnect();
        delete d_ptr;
    }
    QBbgManager::QBbgManager(QObject* parent/*=NULL*/)
        :QObject(parent)
        , d_ptr(new QBbgManagerPrivate(this))
    {}
    QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator QBbgManager::createThread(const QBbgRequestGroup& rq)
{
        Q_ASSERT_X(QCoreApplication::instance(), "QBbgManager", "A QCoreApplication must be created to process requests");
        Q_D(QBbgManager);
        quint32 newID = 1;
        while (d->m_ResultTable.contains(newID) || d->m_ThreadPool.contains(newID)) {
            Q_ASSERT_X(newID < std::numeric_limits<quint32>::max(),"Adding Bloomberg Request","Overflow. Too many request sent");
            ++newID;
        }
        QThread* newThread = nullptr;
        #ifndef QBbg_OFFLINE
        QBbgRequestResponseWorker* newWorker = new QBbgRequestResponseWorker(*(d->m_options));
        newWorker->setRequest(rq);
        newThread = new QThread(this);
        newWorker->moveToThread(newThread);
        connect(newWorker, &QBbgAbstractWorker::dataRecieved, this, &QBbgManager::handleResponse);
        connect(newWorker, &QBbgAbstractWorker::finished, this, &QBbgManager::handleThreadFinished);
        connect(newThread, &QThread::started, newWorker, &QBbgAbstractWorker::start);
        connect(newWorker, &QBbgAbstractWorker::finished, newThread, &QThread::quit);
        //connect(newWorker, &QBbgAbstractWorker::finished, newWorker, &QBbgAbstractWorker::deleteLater);
        connect(newThread, &QThread::finished, newThread, &QThread::deleteLater);
        return d->m_ThreadPool.insert(newID, std::make_pair(newThread, newWorker));
        #else
        Q_UNUSED(rq)
        return d->m_ThreadPool.insert(newID, std::make_pair(newThread, nullptr));
        #endif
        
        
    }
    quint32 QBbgManager::startRequest(const QBbgRequestGroup& rq)
    {
        if (!rq.isValidReq() || rq.size() == 0)
            return 0;
        QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator newTh = createThread(rq);
        #ifndef QBbg_OFFLINE
        Q_D(QBbgManager);
        if (d->m_ThreadPool.size() < qMax(1,QThread::idealThreadCount()))
            newTh.value().first->start();
        else
            d->m_queuedThreads.append(newTh.key());
        #endif
        return newTh.key();
    }

    quint32 QBbgManager::startRequest(const QBbgAbstractRequest& rq)
    {
        QBbgRequestGroup rg;
        if (rg.addRequest(rq) == QBbgAbstractRequest::InvalidID)
            return 0;
        return startRequest(rg);
    }

    quint32 QBbgManager::processRequestID(const QBbgRequestGroup& rq)
    {
        if (!rq.isValidReq() || rq.size() == 0)
            return 0;
        QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator newTh = createThread(rq);
        const quint32 threadKey = newTh.key();
        #ifndef QBbg_OFFLINE
        QEventLoop waitLoop;
        connect(newTh.value().first, &QThread::finished, &waitLoop, &QEventLoop::quit);
        newTh.value().first->start();
        waitLoop.exec();
        Q_ASSERT(d_func()->m_ResultTable.contains(threadKey));
        #else
        Q_ASSERT(!d_func()->m_ResultTable.contains(threadKey));
        d_func()->m_ResultTable.insert(threadKey, new QHash<qint64, QBbgAbstractResponse* >);
        #endif // !QBbg_OFFLINE
        return threadKey;
    }

    quint32 QBbgManager::processRequestID(const QBbgAbstractRequest& rq)
    {
        QBbgRequestGroup rg;
        if (rg.addRequest(rq) == QBbgAbstractRequest::InvalidID)
            return 0;
        return processRequestID(rg);
    }

    const QHash<qint64, QBbgAbstractResponse* >& QBbgManager::processRequest(const QBbgRequestGroup& rq)
    {
        Q_ASSERT_X(rq.isValidReq() && rq.size() > 0,"QBbgManager::processRequest","Invalid request sent");
        Q_D(QBbgManager);
        return *(d->m_ResultTable.value(processRequestID(rq)));
    }

    const QBbgAbstractResponse* const QBbgManager::processRequest(const QBbgAbstractRequest& rq)
    {
        QBbgRequestGroup rg;
        if(rg.addRequest(rq) == QBbgAbstractRequest::InvalidID)
            return nullptr;
        const QHash<qint64, QBbgAbstractResponse* >& resHash= processRequest(rg);
        if (resHash.isEmpty())
            return nullptr;
        Q_ASSERT(resHash.count() == 1);
        return resHash.begin().value();
    }

    const QBbgPortfolioDataResponse* const QBbgManager::processRequest(const QBbgPortfolioDataRequest& rq)
    {
        return static_cast<const QBbgPortfolioDataResponse*>(processRequest(static_cast<const QBbgAbstractRequest&>(rq)));
    }

    const QBbgReferenceDataResponse* const QBbgManager::processRequest(const QBbgReferenceDataRequest& rq)
    {
        return static_cast<const QBbgReferenceDataResponse*>(processRequest(static_cast<const QBbgAbstractRequest&>(rq)));
    }

    const QBbgHistoricalDataResponse* const QBbgManager::processRequest(const QBbgHistoricalDataRequest& rq)
    {
        return static_cast<const QBbgHistoricalDataResponse*>(processRequest(static_cast<const QBbgAbstractRequest&>(rq)));
    }

    const QBbgIntradayTickResponse* const QBbgManager::processRequest(const QBbgIntradayTickRequest& rq)
    {
        return static_cast<const QBbgIntradayTickResponse*>(processRequest(static_cast<const QBbgAbstractRequest&>(rq)));
    }

    void QBbgManager::handleResponse(qint64 reID, QBbgAbstractResponse* res)
    {
        Q_ASSERT(sender());
        Q_D(QBbgManager);
        quint32 foundRes=0;
        for (QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator resIter = d->m_ThreadPool.begin(); resIter != d->m_ThreadPool.end(); ++resIter) {
        #ifndef QBbg_OFFLINE
            if (resIter.value().second == sender()) {
                foundRes = resIter.key();
                break;
        }
        #endif // !QBbg_OFFLINE 
        }
        QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* >::iterator resIter = d->m_ResultTable.find(foundRes);
        if (resIter == d->m_ResultTable.end()) {
            resIter = d->m_ResultTable.insert(foundRes, new QHash<qint64, QBbgAbstractResponse* >());
        }
        QHash<qint64, QBbgAbstractResponse* >::iterator singleIter = resIter.value()->find(reID);
        if (singleIter == resIter.value()->end()) {
            resIter.value()->insert(reID, res);
        }
        else {
            delete singleIter.value();
            singleIter.value() = res;
        }
        emit recieved(foundRes,reID);
    }

    void QBbgManager::handleThreadFinished()
    {
        Q_ASSERT(sender());
        Q_D(QBbgManager);
        for (QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator resIter = d->m_ThreadPool.begin(); resIter != d->m_ThreadPool.end(); ++resIter) {
            #ifndef QBbg_OFFLINE
            if (resIter.value().second == sender()) {
                emit finished(resIter.key());
                delete resIter.value().second;
                d->m_ThreadPool.erase(resIter);
                if (d->m_ThreadPool.isEmpty()) {
                    Q_ASSERT(d->m_queuedThreads.isEmpty()); // There should be no queue active at this point
                    emit allFinished();
                }
                else if (!d->m_queuedThreads.isEmpty()) {
                    QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator queuedThread = d->m_ThreadPool.find(d->m_queuedThreads.dequeue());
                    Q_ASSERT(queuedThread != d->m_ThreadPool.end()); // A queued thread does not exist
                    queuedThread.value().first->start();
                }
                return;
            }
            #endif
        }
        Q_UNREACHABLE(); //Could not find sender()
    }
    const QBbgAbstractResponse* const QBbgManager::getResultGeneric(quint32 group, qint64 id) const
    {
        Q_D(const QBbgManager);
        const QHash < qint64, QBbgAbstractResponse* >* resGroup=d->m_ResultTable.value(group, NULL);
        if (resGroup)
            return resGroup->value(id, NULL);
        return NULL;
    }

    QList<quint32> QBbgManager::getResultGroups()const
    {
        Q_D(const QBbgManager);
        return d->m_ResultTable.keys();
    }

    QList<qint64> QBbgManager::getResultIDs(quint32 group) const
    {
        Q_D(const QBbgManager);
        if (!d->m_ResultTable.contains(group))
            return QList<qint64>();
        return d->m_ResultTable.value(group)->keys();
    }

    QBbgManagerPrivate::~QBbgManagerPrivate()
    {
        if (m_options) {
            #ifndef QBbg_OFFLINE
            delete m_options;
            #endif
        }
        for (QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* >::iterator i = m_ResultTable.begin(); i != m_ResultTable.end(); ++i) {
            Q_ASSERT(i.value());
            for (QHash<qint64, QBbgAbstractResponse* >::iterator j = i.value()->begin(); j != i.value()->end(); ++j) {
                Q_ASSERT(j.value());
                delete j.value();
            }
            delete i.value();
        }
        for (QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> >::iterator i = m_ThreadPool.begin(); i != m_ThreadPool.end(); ++i) {
            if (i.value().first) {
                if (i.value().first->isRunning()) {
                    i.value().first->quit();
                }
            }
            #ifndef QBbg_OFFLINE
            if (i.value().second) {
                i.value().second->stop();
                i.value().second->deleteLater();
            }
            #endif
        }
    }
}
