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