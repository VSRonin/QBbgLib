#ifndef QBbgAbstractWorker_h__
#define QBbgAbstractWorker_h__
#include <QObject>
#include "QBbgAbstractResponse.h"
namespace BloombergLP {namespace blpapi {class SessionOptions;}}
namespace QBbgLib {
    class QBbgAbstractWorkerPrivate;
    class QBbgAbstractResponse;
    class QBbgAbstractWorker : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgAbstractWorker)
    public:
        QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option);
        virtual ~QBbgAbstractWorker();
        virtual bool isAvailable() const;
        virtual void stop();
    protected:
        QBbgAbstractWorker(QBbgAbstractWorkerPrivate* d);
        QBbgAbstractWorkerPrivate* d_ptr;
    public slots:
        virtual void start() = 0;
        virtual void setRequest(const QBbgRequestGroup& req)=0;
    signals:
        void started();
        void stopped();
        void dataRecieved(qint64 reID, QBbgAbstractResponse* res);
        void progress(qint32 pct);
        void finished();
    };
}
#endif // QBbgAbstractWorker_h__