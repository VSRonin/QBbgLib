#include "QBbgManager.h"
#include "private/QBbgManager_p.h"
#include "QBbgRequestGroup.h"
#include <limits>
#include <QEventLoop>
#include "QBbgRequestResponseWorker.h"
#include <QCoreApplication>
namespace QBbgLib {
    QBbgManagerPrivate::QBbgManagerPrivate(QBbgManager* qp)
        :q_ptr(qp)
    {
        m_options.setServerHost("localhost");
        m_options.setServerPort(8194);
        m_options.setMaxPendingRequests(std::numeric_limits<qint32>::max() - 2);
        m_options.setAutoRestartOnDisconnection(false);
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
    QHash<quint32, QBbgWorkerThread* >::iterator QBbgManager::createThread(const QBbgRequestGroup& rq)
    {
        Q_ASSERT_X(QCoreApplication::instance(), "QBbgManager", "A QCoreApplication must be created to process requests");
        Q_D(QBbgManager);
        quint32 newID = 0;
        while (d->m_ResultTable.contains(newID) || d->m_ThreadPool.contains(newID)) {
            Q_ASSERT_X(newID < std::numeric_limits<quint32>::max(),"Adding Bloomberg Request","Overflow. Too many request sent");
            ++newID;
        }
        QBbgRequestResponseWorker* newWorker = new QBbgRequestResponseWorker(d->m_options);
        newWorker->setRequest(rq);
        QBbgWorkerThread* newThread = new QBbgWorkerThread(newWorker, this);
        connect(newThread, &QBbgWorkerThread::dataRecieved, this, &QBbgManager::handleResponse);
        connect(newThread, &QBbgWorkerThread::finished, this, &QBbgManager::handleThreadFinished);
        return d->m_ThreadPool.insert(newID, newThread);
    }
    quint32 QBbgManager::startRequest(const QBbgRequestGroup& rq)
    {
        QHash<quint32, QBbgWorkerThread* >::iterator newTh = createThread(rq);
        newTh.value()->start();
        return newTh.key();
    }

    quint32 QBbgManager::startRequest(const QBbgAbstractRequest& rq)
    {
        QBbgRequestGroup rg;
        rg.addRequest(rq);
        return startRequest(rg);
    }

    const QHash<qint64, QBbgAbstractResponse* >& QBbgManager::processRequest(const QBbgRequestGroup& rq)
    {
        Q_D(QBbgManager);
        QHash<quint32, QBbgWorkerThread* >::iterator newTh = createThread(rq);
        const quint32 threadKey = newTh.key();
        QEventLoop waitLoop;
        connect(newTh.value(), &QBbgWorkerThread::finished, &waitLoop, &QEventLoop::quit);
        newTh.value()->start();
        waitLoop.exec();
        Q_ASSERT(d->m_ResultTable.contains(threadKey));
        return *(d->m_ResultTable.value(threadKey));
    }

    const QBbgAbstractResponse* QBbgManager::processRequest(const QBbgAbstractRequest& rq)
    {
        QBbgRequestGroup rg;
        rg.addRequest(rq);
        const QHash<qint64, QBbgAbstractResponse* >& resHash= processRequest(rg);
        Q_ASSERT(resHash.count() == 1);
        return resHash.begin().value();
    }

    void QBbgManager::handleResponse(qint64 reID, QBbgAbstractResponse* res)
    {
        Q_ASSERT(sender());
        Q_D(QBbgManager);
        quint32 foundRes=0;
        for (QHash<quint32, QBbgWorkerThread* >::iterator resIter = d->m_ThreadPool.begin(); resIter != d->m_ThreadPool.end(); ++resIter) {
            if (resIter.value() == sender()) {
                foundRes = resIter.key();
                break;
            }
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
        for (QHash<quint32, QBbgWorkerThread* >::iterator resIter = d->m_ThreadPool.begin(); resIter != d->m_ThreadPool.end(); ++resIter) {
            if (resIter.value() == sender()) {
                emit finished(resIter.key());
                d->m_ThreadPool.erase(resIter);
                if (d->m_ThreadPool.isEmpty())
                    emit allFinished();
                return;
            }
        }
        Q_UNREACHABLE(); //Could not find sender()
    }
    const QBbgAbstractResponse* const QBbgManager::getResult(quint32 group, qint64 id) const
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
        for (QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* >::iterator i = m_ResultTable.begin(); i != m_ResultTable.end(); ++i) {
            Q_ASSERT(i.value());
            for (QHash<qint64, QBbgAbstractResponse* >::iterator j = i.value()->begin(); j != i.value()->end(); ++j) {
                Q_ASSERT(j.value());
                delete j.value();
            }
            delete i.value();
        }
        for (QHash<quint32, QBbgWorkerThread* >::iterator i = m_ThreadPool.begin(); i != m_ThreadPool.end(); ++i) {
            Q_ASSERT(i.value());
            if (i.value()->isRunning()) {
                i.value()->stop();
                //i.value()->wait(2000);
            }
        }
    }
}
