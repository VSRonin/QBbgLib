#ifndef QBbgAbstractWorker_h__
#define QBbgAbstractWorker_h__
#include <QObject>
#include "QBbgAbstractResponse.h"
#include "QBbgProjectGlobals.h"
namespace BloombergLP {namespace blpapi {class SessionOptions;}}
namespace QBbgLib {
    class QBbgAbstractWorkerPrivate;
    class QBBG_EXPORT QBbgAbstractWorker : public QObject
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgAbstractWorker)
    public:
        QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option);
        virtual ~QBbgAbstractWorker();
        virtual bool isAvailable() const;
        virtual void stop();
    protected:
        virtual void start() = 0;
        QBbgAbstractWorker(QBbgAbstractWorkerPrivate* d);
        QBbgAbstractWorkerPrivate* d_ptr;
    signals:
        void Started();
        void Stopped();
    };
}
#endif // QBbgAbstractWorker_h__