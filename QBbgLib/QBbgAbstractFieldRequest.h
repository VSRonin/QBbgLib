#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgAbstractRequest.h"
#include <QString>
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBbgRequestGroup;
    class QBbgOverride;
    class QBBG_EXPORT QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
        virtual ~QBbgAbstractFieldRequest()=0;
        QBbgAbstractFieldRequest(RequestType typ/*=QBbgAbstractRequest::Invalid*/);
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        virtual const QString& field() const;
        virtual void setField(const QString& val);
        virtual const QBbgOverride& overrides() const;
        virtual void setOverrides(const QBbgOverride& Overr);
        virtual void clearOverrides();
		virtual bool isValidReq() const;
	protected:
        virtual bool sameOverrides(const QBbgAbstractFieldRequest& a)const;
        QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestGroup;
	};
}
#endif // SingleBbgRequest_h__

