#ifndef QBbgAbstractWorker_h__
#define QBbgAbstractWorker_h__

#include <QObject>
namespace BloombergLP {namespace blpapi {class SessionOptions;}}
namespace QBbgLib {
    class QBbgAbstractWorkerPrivate;
    class QBbgAbstractWorker : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgAbstractWorker)
    public:
        QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option);
        virtual ~QBbgAbstractWorker();
    protected:
        QBbgAbstractWorker(QBbgAbstractWorkerPrivate* d);
        QBbgAbstractWorkerPrivate* d_ptr;
    signals:
        void Started();
        void Stopped();
    };
}
#endif // QBbgAbstractWorker_h__