#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgRequest.h"
#include "QSingleBbgResult.h"
#include "QBbgAbstractRequest.h"
#include <QHash>
namespace QBbgLib {
	class QBbgWorker;
    class QBbgAbstractFieldRequestPrivate;
    class QBbgRequestPrivate;
    class QBBG_EXPORT QBbgAbstractFieldRequest : public QBbgAbstractRequest
	{
        Q_DECLARE_PRIVATE(QBbgAbstractFieldRequest)
	public:
		QBbgAbstractFieldRequest();
		QBbgAbstractFieldRequest(const QBbgAbstractFieldRequest& a);
		bool operator==(const QBbgAbstractFieldRequest& a) const;
		QBbgAbstractFieldRequest& operator=(const QBbgAbstractFieldRequest& a);
		const QString& GetField() const;
		void SetField(const QString& val);
		const Overrides& GetOverrides() const;
		void SetOverrides(const Overrides& Overr);
		void SetOverride(QString Name, const QVariant& Value);
		void ClearOverrides();
		bool IsValidReq() const;
	protected:
		bool SameOverrides(const QBbgAbstractFieldRequest& a)const;
		friend class QBbgRequest;
        friend class QBbgRequestPrivate;
	};
}
#endif // SingleBbgRequest_h__

