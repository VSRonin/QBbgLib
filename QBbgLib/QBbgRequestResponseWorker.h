#ifndef QBbgRequestResponseWorker_h__
#define QBbgRequestResponseWorker_h__
#include <QtGlobal>
#include "QBbgAbstractWorker.h"
namespace QBbgLib {
    class QBbgRequestResponseWorkerPrivate;
    class QBbgRequestGroup;
    class QBbgRequestResponseWorker : public QBbgAbstractWorker
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgRequestResponseWorker);
    public:
        QBbgRequestResponseWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent = NULL);
        virtual const QBbgAbstractResponse* result(qint64 id) const;
    public slots:
        virtual void start();
        virtual void start(const QBbgRequestGroup& req);
        virtual void setRequest(const QBbgRequestGroup& req);     
        virtual void ClearResults();
    };

}
#endif // QBbgRequestResponseWorker_h__