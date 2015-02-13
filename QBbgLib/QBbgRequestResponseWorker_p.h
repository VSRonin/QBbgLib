#ifndef QBbgRequestResponseWorker_p_h__
#define QBbgRequestResponseWorker_p_h__
#include "QBbgAbstractWorker_p.h"
#include "QBbgRequestResponseWorker.h"
#include "QBbgAbstractResponse.h"
#include "QBbgRequestGroup.h"
#include <QHash>
namespace QBbgLib {
    class QBbgRequestResponseWorkerPrivate : public QBbgAbstractWorkerPrivate
    {
        Q_DECLARE_PUBLIC(QBbgRequestResponseWorker);
        QBbgRequestResponseWorkerPrivate(const QBbgRequestResponseWorkerPrivate& other);
    public:
        QBbgRequestResponseWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& options);
        virtual ~QBbgRequestResponseWorkerPrivate();
        QHash<qint64, QBbgAbstractResponse* > m_Results;
        QBbgRequestGroup m_Requests;
        QHash<qint64, QList<qint64>* > Groups;
        virtual void handleResponseEvent(const BloombergLP::blpapi::Event& event);
        virtual bool processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession);
        virtual bool SetError(qint64 RequestID, QBbgAbstractResponse::BbgErrorCodes Err);
        virtual bool DataPointRecieved(qint64 RequestID, const QVariant& Value, const QString& Header);
        virtual bool HeaderRecieved(qint64 RequestID, const QString& Header);
        virtual bool DataRecieved(qint64 RequestID);
        virtual void DataRowRecieved(qint64 RequestID, const QList<QVariant>&  Value, const QList<QString>&  Header);
        virtual qint64 CorrelationForService(const QString& a) const;
        virtual void SendRequ(QBbgAbstractRequest::ServiceType serv);
    };

    

    

}
#endif // QBbgRequestResponseWorker_p_h__