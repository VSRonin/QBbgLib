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
        Q_OBJECT
        Q_DECLARE_PUBLIC(QBbgRequestResponseWorker);
        QBbgRequestResponseWorkerPrivate(const QBbgRequestResponseWorkerPrivate& other);
    public:
        QBbgRequestResponseWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& options);
        virtual ~QBbgRequestResponseWorkerPrivate();
        QHash<qint64, QBbgAbstractResponse* > m_Results;
        QBbgRequestGroup m_Requests;
        QHash<qint64, QList<qint64>* > Groups;
        qint32 m_ResurnedResults;
        virtual void handleResponseEvent(const BloombergLP::blpapi::Event& event, bool isFinal);
        virtual bool processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession);
        virtual void SetError(qint64 RequestID, QBbgAbstractResponse::BbgErrorCodes Err, const QString& errMsg);
        virtual void DataPointRecieved(qint64 RequestID, const QVariant& Value, const QString& Header);
        virtual void HeaderRecieved(qint64 RequestID, const QString& Header);
        virtual void DataRecieved(qint64 RequestID);
        virtual void DataRowRecieved(qint64 RequestID, const QList<QVariant>&  Value, const QList<QString>&  Header);
        virtual void HistDataRecieved(qint64 RequestID, const QDate& dt, const QVariant& val, const QString& period = QString(), const QString& Header = QString());
        virtual qint64 CorrelationForService(const QString& a) const;
        virtual void SendRequ(QBbgAbstractRequest::ServiceType serv);
        virtual void PortfolioDataRecieved(qint64 RequestID, const QString& Sec, const double* pos, const double* mkVal, const double* cst, const QDate* cstDt, const double* cstFx, const double* wei);
        virtual void fillNoData();
    };

    
    
    

    

    

}
#endif // QBbgRequestResponseWorker_p_h__