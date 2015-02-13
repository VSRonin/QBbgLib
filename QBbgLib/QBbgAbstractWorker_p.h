#ifndef QBbgAbstractWorker_p_h__
#define QBbgAbstractWorker_p_h__
#include <QVariant>
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
        virtual void setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err) const;
        virtual void setResponseID(QBbgAbstractResponse* res, qint64 corrID) const;
        virtual QVariant elementToVariant(BloombergLP::blpapi::Element& val);
    protected:
        QBbgAbstractWorker* q_ptr;
    };

   



    

}
#endif // QBbgAbstractWorker_p_h__