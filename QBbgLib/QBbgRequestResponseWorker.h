#ifndef QBbgRequestResponseWorker_h__
#define QBbgRequestResponseWorker_h__
#include <QtGlobal>
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractWorker.h"
namespace QBbgLib {
    class QBbgRequestResponseWorkerPrivate;
    class QBBG_EXPORT QBbgRequestResponseWorker : public QBbgAbstractWorker
    {
        Q_OBJECT
        Q_DECLARE_PRIVATE(QBbgRequestResponseWorker);
   
    };

}
#endif // QBbgRequestResponseWorker_h__