#ifndef QBbgRequestResponseWorker_h__
#define QBbgRequestResponseWorker_h__
#include <QtGlobal>
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractWorker.h"
namespace QBbgLib {
    class QBbgRequestResponseWorkerPrivate;
    class QBbgRequestGroup;
    class QBBG_EXPORT QBbgRequestResponseWorker : public QBbgAbstractWorker
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgRequestResponseWorker);
    public:
        QBbgRequestResponseWorker(const BloombergLP::blpapi::SessionOptions& option);
        virtual void start(const QBbgRequestGroup& req);
        virtual const QBbgAbstractResponse* result(qint64 id) const;
    protected:
        virtual void start();
    signals:
        void Recieved(qint64);
        void Progress(qint32);
        void Stopped();
        void Finished();
    };

}
#endif // QBbgRequestResponseWorker_h__