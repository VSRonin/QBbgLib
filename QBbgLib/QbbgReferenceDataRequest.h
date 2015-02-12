#ifndef QbbgReferenceDataRequest_h__
#define QbbgReferenceDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
namespace QBbgLib {
    class QBbgReferenceDataRequestPrivate;
    class QBBG_EXPORT QBbgReferenceDataRequest : public QBbgAbstractFieldRequest
    {
        Q_DECLARE_PRIVATE(QBbgReferenceDataRequest)
    public:
    	QBbgReferenceDataRequest();
        QBbgReferenceDataRequest(const QBbgReferenceDataRequest& a);
        virtual QBbgReferenceDataRequest& operator=(const QBbgReferenceDataRequest& a);
        virtual bool operator==(const QBbgReferenceDataRequest& a) const;
        bool useUTCtime() const;
        void setUseUTCtime(bool a);
    protected:
        QBbgReferenceDataRequest(QBbgReferenceDataRequestPrivate* d);
    };
}
#endif // QbbgReferenceDataRequest_h__