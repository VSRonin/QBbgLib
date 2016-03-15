#ifndef QBbgManager_p_h__
#define QBbgManager_p_h__
#include "QBbgManager.h"
#include <QHash>
#include <blpapi_sessionoptions.h>
namespace QBbgLib {
    class QBbgAbstractResponse;
    class QBbgWorkerThread;
    class QBbgManagerPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgManager)
        QBbgManagerPrivate(const QBbgManagerPrivate&);
    public:
        QBbgManagerPrivate(QBbgManager* qp);
        virtual ~QBbgManagerPrivate();
        QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* > m_ResultTable;
        QHash<quint32, QBbgWorkerThread* > m_ThreadPool;
        BloombergLP::blpapi::SessionOptions m_options;
    protected:
        QBbgManager* q_ptr;
        
    };
}
#endif // QBbgManager_p_h__