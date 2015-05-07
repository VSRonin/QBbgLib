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
    class QBBG_EXPORT QBbgManager : public QObject
    {
        Q_OBJECT
    private:
        Q_DECLARE_PRIVATE(QBbgManager)
    public:
        QBbgManager(QObject* parent=NULL);
        virtual ~QBbgManager();
    public:
        quint32 startRequest(const QBbgRequestGroup& rq);
        const QHash<qint64, QBbgAbstractResponse* >& processRequest(const QBbgRequestGroup& rq);
        const QBbgAbstractResponse* const getResult(quint32 group, qint64 id) const;
        QList<quint32> getResultGroups() const;
        QList<qint64> getResultIDs(quint32 group) const;
    protected:
        QBbgManagerPrivate* d_ptr;
        QHash<quint32, QBbgWorkerThread* >::iterator createThread(const QBbgRequestGroup& rq);
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
