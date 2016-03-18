#ifndef QBbgAbstractFieldResponse_h__
#define QBbgAbstractFieldResponse_h__
#include "QBbgAbstractResponse.h"
namespace QBbgLib {
    class QBbgAbstractFieldResponsePrivate;
    class QBbgRequestResponseWorker;
    class QBBG_EXPORT QBbgAbstractFieldResponse : public QBbgAbstractResponse
    {
        Q_DECLARE_PRIVATE(QBbgAbstractFieldResponse)
    public:
        virtual ~QBbgAbstractFieldResponse() = 0;
        QBbgAbstractFieldResponse(ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractFieldResponse(const QBbgAbstractFieldResponse& a);
        virtual QBbgAbstractFieldResponse& operator=(const QBbgAbstractFieldResponse& a);
        virtual const QString& header() const;
    protected:
        QBbgAbstractFieldResponse(QBbgAbstractFieldResponsePrivate* d);
        virtual void setHeader(const QString& Header = QString());

        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgAbstractFieldResponse_h__