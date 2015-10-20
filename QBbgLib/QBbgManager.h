#ifndef QBbgManager_h__
#define QBbgManager_h__
#include "QBbgWorkerThread.h"
#include <QObject>
#include "QBbgProjectGlobals.h"
#include <QHash>
#include <QList>
namespace QBbgLib {
    class QBbgManagerPrivate;
    class QBbgRequestGroup;
    class QBbgWorkerThread;
    class QBbgAbstractRequest;

    class QBbgReferenceDataRequest;
    class QBbgHistoricalDataRequest;
    class QBbgPortfolioDataRequest;
    class QBbgReferenceDataResponse;
    class QBbgHistoricalDataResponse;
    class QBbgPortfolioDataResponse;
    class QBBG_EXPORT QBbgManager : public QObject
    {
        Q_OBJECT
    private:
        Q_DECLARE_PRIVATE(QBbgManager)
    protected:
        
        QBbgManagerPrivate* d_ptr;
        QHash<quint32, QBbgWorkerThread* >::iterator createThread(const QBbgRequestGroup& rq);
        const QBbgAbstractResponse* const getResultGeneric(quint32 group, qint64 id) const;
    public:
        QBbgManager(QObject* parent=NULL);
        virtual ~QBbgManager();
        quint32 startRequest(const QBbgRequestGroup& rq);
        quint32 startRequest(const QBbgAbstractRequest& rq);
        const QHash<qint64, QBbgAbstractResponse* >& processRequest(const QBbgRequestGroup& rq);
        const QBbgReferenceDataResponse* const processRequest(const QBbgReferenceDataRequest& rq);
        const QBbgHistoricalDataResponse* const processRequest(const QBbgHistoricalDataRequest& rq);
        const QBbgPortfolioDataResponse* const processRequest(const QBbgPortfolioDataRequest& rq);
        const QBbgAbstractResponse* const processRequest(const QBbgAbstractRequest& rq);
        template <class T = QBbgAbstractResponse> const T* const getResult(quint32 group, qint64 id) const
        {
            static_assert(std::is_base_of<QBbgAbstractResponse, T>::value, "getResult Template type must be derived from QBbgAbstractResponse");
            const QBbgAbstractResponse* const genericRes = getResultGeneric(group, id);
            if (!genericRes)
                return NULL;
            if (!std::is_same<QBbgAbstractResponse, T>::value) {
                switch (genericRes->responseType()) {
                case QBbgAbstractResponse::ResponseType::ReferenceDataResponse:
                    if (!std::is_same<QBbgReferenceDataResponse, T>::value)
                        return NULL;
                    break;
                case QBbgAbstractResponse::ResponseType::HistoricalDataResponse:
                    if (!std::is_same<QBbgHistoricalDataResponse, T>::value)
                        return NULL;
                    break;
                case QBbgAbstractResponse::ResponseType::PortfolioDataResponse:
                    if (!std::is_same<QBbgPortfolioDataResponse, T>::value)
                        return NULL;
                    break;
                default:
                    Q_UNREACHABLE(); //Unhandled response type
                }
            }
            return static_cast<const T* const>(genericRes);
        }
        QList<quint32> getResultGroups() const;
        QList<qint64> getResultIDs(quint32 group) const;
    protected slots:
        void handleResponse(qint64 reID, QBbgAbstractResponse* res);
        void handleThreadFinished();
    signals:
        void recieved(quint32, qint64);
        void finished(quint32);
        void allFinished();
    };
}
#endif // QBbgManager_h__
