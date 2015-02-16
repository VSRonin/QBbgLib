#include "QBbgManager.h"
#include "QBbgManager_p.h"
#include "QBbgRequestGroup.h"
#include <limits>
#include "QBbgRequestResponseWorker.h"
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
        disconnect();
        delete d_ptr;
    }
    QBbgManager::QBbgManager(QObject* parent/*=NULL*/)
        :QObject(parent)
        , d_ptr(new QBbgManagerPrivate(this))
    {}

    quint32 QBbgManager::startRequest(const QBbgRequestGroup& rq)
    {
        Q_D(QBbgManager);
        quint32 newID = 0;
        while (d->m_ThreadPool.contains(newID)) {
            Q_ASSERT(newID < std::numeric_limits<quint32>::max());
            ++newID;
        }
        QBbgRequestResponseWorker* newWorker = new QBbgRequestResponseWorker(d->m_options);
        newWorker->setRequest(rq);
        QBbgWorkerThread* newThread = new QBbgWorkerThread(newWorker, this);
        connect(newThread, &QBbgWorkerThread::dataRecieved, this, &QBbgManager::handleResponse);
        connect(newThread, &QBbgWorkerThread::finished, this, &QBbgManager::handleThreadFinished);
        d->m_ThreadPool.insert(newID, newThread).value()->start();
        return newID;
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
                emit resIter.key();
                d->m_ThreadPool.erase(resIter);
                return;
            }
        }
        Q_ASSERT_X(false, "QBbgManager::handleThreadFinished", "Could not find sender()");
    }

    const QBbgAbstractResponse* const QBbgManager::getResult(quint32 group, qint64 id)
    {
        Q_D(QBbgManager);
        return d->m_ResultTable.value(group, NULL)->value(id, NULL);
    }

    QBbgManagerPrivate::~QBbgManagerPrivate()
    {
        for (QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* >::iterator i = m_ResultTable.begin(); i != m_ResultTable.end(); ++i) {
            for (QHash<qint64, QBbgAbstractResponse* >::iterator j = i.value()->begin(); j != i.value()->end(); ++j) {
                delete j.value();
            }
            delete i.value();
        }
        for (QHash<quint32, QBbgWorkerThread* >::iterator i = m_ThreadPool.begin(); i != m_ThreadPool.end(); ++i) {
            Q_ASSERT(i.value());
            if (i.value()->isRunning()) {
                i.value()->quit();
                i.value()->wait();
            }
        }
    }
}