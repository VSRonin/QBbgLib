#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgRequestGroup.h"
#include "QSingleBbgResult.h"
#include "QBbgAbstractRequest.h"
#include <QHash>
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestGroupPrivate;
    class QBbgRequestGroup;
    class QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
		QBbgAbstractFieldRequest();
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        virtual const QString& field() const;
        virtual void setField(const QString& val);
        virtual const Overrides& overrides() const;
        virtual void setOverrides(const Overrides& Overr);
        virtual void setOverride(QString Name, const QVariant& Value);
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

