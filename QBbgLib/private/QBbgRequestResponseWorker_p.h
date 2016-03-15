#ifndef QBbgRequestResponseWorker_h__
#define QBbgRequestResponseWorker_h__
#include <QHash>
#include "private/QBbgAbstractWorker_p.h"
#include "QBbgRequestGroup.h"
namespace BloombergLP {
    namespace blpapi {
        class Event;
        class Session;
    }
}
namespace QBbgLib {
    class QBbgRequestGroup;
    class QBbgRequestResponseWorker : public QBbgAbstractWorker
    {
        Q_OBJECT
    public:
        virtual ~QBbgRequestResponseWorker();
        QBbgRequestResponseWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent = nullptr);
        virtual const QBbgAbstractResponse* result(qint64 id) const;
    public slots:
        virtual void start();
        virtual void start(const QBbgRequestGroup& req);
        virtual void setRequest(const QBbgRequestGroup& req);     
        virtual void ClearResults();
    protected:
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
    private:
        QHash<qint64, QBbgAbstractResponse* > m_Results;
        QBbgRequestGroup m_Requests;
        QHash<qint64, QList<qint64>* > Groups;
        qint32 m_ResurnedResults;
    };

}
#endif // QBbgRequestResponseWorker_h__