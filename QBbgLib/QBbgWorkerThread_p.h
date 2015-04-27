#ifndef QBbgWorkerThread_p_h__
#define QBbgWorkerThread_p_h__

#include "QBbgWorkerThread.h"
namespace QBbgLib {
    class QBbgAbstractWorker;
    class QBbgWorkerThreadPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgWorkerThread)
        QBbgWorkerThreadPrivate(const QBbgWorkerThreadPrivate& other);
    public:
        QBbgWorkerThreadPrivate(QBbgWorkerThread* q, QBbgAbstractWorker* wrk);
        QBbgAbstractWorker* m_worker;
    protected:
        QBbgWorkerThread* q_ptr;
    };

}
#endif // QBbgWorkerThread_p_h__