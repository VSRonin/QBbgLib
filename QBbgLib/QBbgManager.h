#ifndef QBbgManager_h__
#define QBbgManager_h__
#include "QBbgWorkerThread.h"
#include <QObject>
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgManagerPrivate;
    class QBbgRequestGroup;
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
        const QBbgAbstractResponse* const getResult(quint32 group, qint64 id);
    protected:
        QBbgManagerPrivate* d_ptr;
    protected slots:
        void handleResponse(qint64 reID, QBbgAbstractResponse* res);
        void handleThreadFinished();
    signals:
        void recieved(quint32, qint64);
        void finished(quint32);
    };
}
#endif // QBbgManager_h__
