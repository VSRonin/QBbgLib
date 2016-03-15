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