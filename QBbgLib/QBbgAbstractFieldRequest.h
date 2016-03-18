#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgAbstractRequest.h"
#include <QString>
#include <QObject>
#include "QBbgOverride.h"
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBbgRequestGroup;
    class QBBG_EXPORT QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_GADGET
        Q_PROPERTY(QString field READ field WRITE setField)
        Q_PROPERTY(QBbgOverride overrides READ overrides WRITE setOverrides)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
        virtual ~QBbgAbstractFieldRequest() = 0;
        QBbgAbstractFieldRequest(RequestType typ);
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        virtual const QString& field() const;
        virtual void setField(const QString& val);
        virtual const QBbgOverride& overrides() const;
        virtual void setOverrides(const QBbgOverride& Overr);
        Q_INVOKABLE virtual void clearOverrides();
		virtual bool isValidReq() const;
	protected:
        virtual bool sameOverrides(const QBbgAbstractFieldRequest& a)const;
        QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d);
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestGroup;
	};
}
#endif // SingleBbgRequest_h__

