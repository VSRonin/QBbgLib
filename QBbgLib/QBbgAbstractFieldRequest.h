#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgRequest.h"
#include "QSingleBbgResult.h"
#include "QBbgAbstractRequest.h"
#include <QHash>
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate;
    class QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
		QBbgAbstractFieldRequest();
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
        virtual bool operator==(const QBbgAbstractFieldRequest& a) const;
        virtual QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
        virtual const QString& GetField() const;
        virtual void SetField(const QString& val);
        virtual const Overrides& GetOverrides() const;
        virtual void SetOverrides(const Overrides& Overr);
        virtual void SetOverride(QString Name, const QVariant& Value);
        virtual void ClearOverrides();
		virtual bool IsValidReq() const;
	protected:
        virtual bool SameOverrides(const QBbgAbstractFieldRequest& a)const;
        QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d);
	};
}
#endif // SingleBbgRequest_h__

