#ifndef QBbgWorkerThread_h__
#define QBbgWorkerThread_h__
#include <QThread>
namespace QBbgLib {
    class QBbgAbstractWorker;
    class QBbgAbstractWorkerThreadPrivate;
    class QBbgAbstractResponse;
    class QBbgAbstractWorkerThread : public QThread
    {
        Q_OBJECT
    private:
        Q_DECLARE_PRIVATE(QBbgAbstractWorkerThread)      
    protected:
        QBbgAbstractWorkerThread(QBbgAbstractWorkerThreadPrivate* dp, QObject* parent = NULL);
        QBbgAbstractWorkerThreadPrivate* d_ptr;
    public slots:
        virtual void run();
        virtual ~QBbgAbstractWorkerThread();
    signals:
        void started();
        void stopped();
        void dataRecieved(qint64 reID, QBbgAbstractResponse* res);
        void progress(qint32 pct);
        void finished();
    };
}
#endif // QBbgWorkerThread_h__