#include "QBbgAbstractWorker.h"
#include "QBbgAbstractWorker_p.h"
#include <blpapi_session.h>
namespace QBbgLib {
    QBbgAbstractWorkerPrivate::QBbgAbstractWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& option)
        :q_ptr(q)
        , m_session(new BloombergLP::blpapi::Session(option,this))
        , m_SessionRunning(false)
    {}
    QBbgAbstractWorkerPrivate::~QBbgAbstractWorkerPrivate()
    {
        if (m_SessionRunning)
            m_session->stop();
    }
    QBbgAbstractWorker::QBbgAbstractWorker( QBbgAbstractWorkerPrivate* d)
        : d_ptr(d)
    {}
    QBbgAbstractWorker::~QBbgAbstractWorker()
    {
        delete d_ptr;
    }
}