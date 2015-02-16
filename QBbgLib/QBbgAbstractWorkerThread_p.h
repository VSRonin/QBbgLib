#include "QBbgAbstractWorkerThread.h"
namespace QBbgLib {
    class QBbgAbstractWorker;
    class QBbgAbstractWorkerThreadPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractWorkerThread)
        QBbgAbstractWorkerThreadPrivate(const QBbgAbstractWorkerThreadPrivate& other);
    public:
        QBbgAbstractWorkerThreadPrivate(QBbgAbstractWorkerThread* q, QBbgAbstractWorker* wrk);
        QBbgAbstractWorker* m_worker;
        virtual ~QBbgAbstractWorkerThreadPrivate();
    protected:
        QBbgAbstractWorkerThread* q_ptr;
    };

    

    

}