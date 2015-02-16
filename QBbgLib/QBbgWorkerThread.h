#ifndef QBbgWorkerThread_h__
#define QBbgWorkerThread_h__
#include <QThread>
namespace QBbgLib {
    class QBbgAbstractWorker;
    class QBbgWorkerThreadPrivate;
    class QBbgAbstractResponse;
    class QBbgWorkerThread : public QThread
    {
        Q_OBJECT
    private:
        Q_DECLARE_PRIVATE(QBbgWorkerThread)      
    public:
        QBbgWorkerThread(QBbgAbstractWorker* wrk, QObject* parent = NULL);
        virtual ~QBbgWorkerThread();
    protected:
        QBbgWorkerThread(QBbgWorkerThreadPrivate* dp, QObject* parent = NULL);
        QBbgWorkerThreadPrivate* d_ptr;
        void createConnections();
    public slots:
        void run();
    signals:
        void started();
        void stopped();
        void dataRecieved(qint64 reID, QBbgAbstractResponse* res);
        void progress(qint32 pct);
        void finished();
    };
}
#endif // QBbgWorkerThread_h__