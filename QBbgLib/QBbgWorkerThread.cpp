#include "QBbgWorkerThread.h"
#include "private/QBbgWorkerThread_p.h"
#include "QBbgAbstractWorker.h"
namespace QBbgLib {

QBbgWorkerThreadPrivate::~QBbgWorkerThreadPrivate()
{

}
    QBbgWorkerThread::QBbgWorkerThread(QBbgWorkerThreadPrivate* dp, QObject* parent)
        :QThread(parent)
        , d_ptr(dp)
    { 
        createConnections();
    }
    QBbgWorkerThread::QBbgWorkerThread(QBbgAbstractWorker* wrk, QObject* parent /*= NULL*/)
        :QThread(parent)
        , d_ptr(new QBbgWorkerThreadPrivate(this, wrk))
    {
        createConnections();
    }
    void QBbgWorkerThread::run()
    {
        Q_D(QBbgWorkerThread);
        d->m_worker->start();
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
        Q_D(QBbgWorkerThread);
        connect(d->m_worker, &QBbgAbstractWorker::started, this, &QBbgWorkerThread::started);
        connect(d->m_worker, &QBbgAbstractWorker::stopped, this, &QBbgWorkerThread::stopped);
        connect(d->m_worker, &QBbgAbstractWorker::dataRecieved, this, &QBbgWorkerThread::dataRecieved);
        connect(d->m_worker, &QBbgAbstractWorker::progress, this, &QBbgWorkerThread::progress);
        connect(d->m_worker, &QBbgAbstractWorker::finished, this, &QBbgWorkerThread::finished);
        connect(this, &QBbgWorkerThread::finished, this, &QBbgWorkerThread::deleteLater);
        connect(d->m_worker, &QBbgAbstractWorker::finished, this, &QBbgWorkerThread::quit);
        connect(d->m_worker, &QBbgAbstractWorker::stopped, this, &QBbgWorkerThread::quit);
    }

    void QBbgWorkerThread::stop()
    {
        Q_D(QBbgWorkerThread);
        d->m_worker->stop();
    }

    QBbgWorkerThreadPrivate::QBbgWorkerThreadPrivate(QBbgWorkerThread* q, QBbgAbstractWorker* wrk)
        : q_ptr(q)
        , m_worker(wrk)
    {
        Q_ASSERT(m_worker);
        wrk->setParent(q);
    }
}
