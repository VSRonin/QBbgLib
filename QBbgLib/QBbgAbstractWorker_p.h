#ifndef QBbgAbstractWorker_p_h__
#define QBbgAbstractWorker_p_h__

#include "QBbgAbstractWorker.h"
#include <QScopedPointer>
#include <blpapi_session.h>
namespace QBbgLib {
    class QBbgAbstractWorkerPrivate : public BloombergLP::blpapi::EventHandler
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractWorker)
        QBbgAbstractWorkerPrivate(const QBbgAbstractWorkerPrivate& other);
    public:
        virtual ~QBbgAbstractWorkerPrivate();
        QBbgAbstractWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& options);
        QScopedPointer<BloombergLP::blpapi::Session> m_session;
        bool m_SessionRunning;
        virtual void handleResponseEvent(const BloombergLP::blpapi::Event& event)=0;
        void setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err) const;
        void setResponseID(QBbgAbstractResponse* res, qint64 corrID) const;
    protected:
        QBbgAbstractWorker* q_ptr;
    };

    

}
#endif // QBbgAbstractWorker_p_h__