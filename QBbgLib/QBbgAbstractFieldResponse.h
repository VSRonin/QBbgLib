#ifndef QBbgAbstractFieldResponse_h__
#define QBbgAbstractFieldResponse_h__
#include "QBbgAbstractResponse.h"
namespace QBbgLib {
    class QBbgAbstractFieldResponsePrivate;
    class QBbgRequestResponseWorkerPrivate;
    class QBBG_EXPORT QBbgAbstractFieldResponse : public QBbgAbstractResponse
    {
        Q_DECLARE_PRIVATE(QBbgAbstractFieldResponse)
    public:
        QBbgAbstractFieldResponse();
        QBbgAbstractFieldResponse(const QBbgAbstractFieldResponse& a);
        virtual QBbgAbstractFieldResponse& operator=(const QBbgAbstractFieldResponse& a);
        virtual const QString& header() const;
    protected:
        QBbgAbstractFieldResponse(QBbgAbstractFieldResponsePrivate* d);
        virtual void setHeader(const QString& Header = QString());

        friend class QBbgRequestResponseWorkerPrivate;
    };
}
#endif // QBbgAbstractFieldResponse_h__