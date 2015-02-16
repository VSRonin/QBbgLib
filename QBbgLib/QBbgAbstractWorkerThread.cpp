#include "QBbgAbstractWorkerThread.h"
#include "QBbgAbstractWorkerThread_p.h"
#include "QBbgAbstractWorker.h"
namespace QBbgLib {
    QBbgAbstractWorkerThread::QBbgAbstractWorkerThread(QBbgAbstractWorkerThreadPrivate* dp, QObject* parent)
        :QThread(parent)
        , d_ptr(dp)
    {
        Q_D(QBbgAbstractWorkerThread);
        connect(d->m_worker, &QBbgAbstractWorker::started, this, &QBbgAbstractWorkerThread::started);
        connect(d->m_worker, &QBbgAbstractWorker::stopped, this, &QBbgAbstractWorkerThread::stopped);
        connect(d->m_worker, &QBbgAbstractWorker::dataRecieved, this, &QBbgAbstractWorkerThread::dataRecieved);
        connect(d->m_worker, &QBbgAbstractWorker::progress, this, &QBbgAbstractWorkerThread::progress);
        connect(d->m_worker, &QBbgAbstractWorker::finished, this, &QBbgAbstractWorkerThread::finished);
        connect(this, &QBbgAbstractWorkerThread::finished, this, &QBbgAbstractWorkerThread::deleteLater);
        connect(d->m_worker, &QBbgAbstractWorker::finished, this, &QBbgAbstractWorkerThread::quit);
        connect(d->m_worker, &QBbgAbstractWorker::stopped, this, &QBbgAbstractWorkerThread::quit);
    }
    void QBbgAbstractWorkerThread::run()
    {
        Q_D(QBbgAbstractWorkerThread);
        d->m_worker->start();
        exec();
    }
    QBbgAbstractWorkerThread::~QBbgAbstractWorkerThread()
    {
        delete d_ptr;
    }
    QBbgAbstractWorkerThreadPrivate::~QBbgAbstractWorkerThreadPrivate()
    {
        delete m_worker;
    }
    QBbgAbstractWorkerThreadPrivate::QBbgAbstractWorkerThreadPrivate(QBbgAbstractWorkerThread* q, QBbgAbstractWorker* wrk)
        : q_ptr(q)
        , m_worker(wrk)
    {
        Q_ASSERT(m_worker);
        Q_ASSERT(q_ptr);
    }
}
