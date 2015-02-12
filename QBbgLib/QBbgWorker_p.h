#ifndef QBbgWorker_p_h__
#define QBbgWorker_p_h__
#include <blpapi_session.h>
#include "QBbgWorker.h"
#include "QBbgGenerals.h"
#include <atomic>
namespace QBbgLib {
    class QBbgWorkerPrivate : private BloombergLP::blpapi::EventHandler
    {
    private:
        Q_DECLARE_PUBLIC(QBbgWorker)
        QBbgWorker* q_ptr;
        QBbgWorkerPrivate(const QBbgWorkerPrivate& a);
    public:
        QBbgWorkerPrivate(QBbgWorker* q);
        QBbgWorkerPrivate(QBbgWorker* q,const QBbgWorkerPrivate& a);
        QBbgWorkerPrivate& operator=(const QBbgWorkerPrivate& a);
        virtual ~QBbgWorkerPrivate();
        QHash<qint64, QList<qint64>* > Groups;
        QString ServerAddress;
        unsigned short ServerPort;
        QBbgRequestGroup m_Requests;
        QMap<qint64, QSingleBbgResult* > m_Results;
        QScopedPointer<BloombergLP::blpapi::Session> session;
        std::atomic_bool m_SessionFinished;
        bool m_UseSyncronous;
        void RunRequest();
        void handleResponseEvent(const BloombergLP::blpapi::Event& event);
        bool processEvent(const BloombergLP::blpapi::Event& event, BloombergLP::blpapi::Session *CurrentSession);
        void SetGlobalError(BbgErrorCodes Err);
        bool SetError(qint64 GroupID, qint64 RequestID, BbgErrorCodes Err);
        void Send();
        bool DataRecieved(qint64 GroupID, qint64 RequestID, const QString& Value, const QString& Header);
        bool DataRecieved(qint64 GroupID, qint64 RequestID, const QString& Header = QString());
        void DataRowRecieved(qint64 GroupID, qint64 RequestID, const QList<QString>&  Value, const QList<QString>&  Header);
        void EndOfProcess();
    };
}
#endif // QBbgWorker_p_h__