#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgRequest.h"
#include "QSingleBbgResult.h"
#include "QBbgAbstractRequest.h"
#include <QHash>
namespace QBbgLib {
	class QBbgWorker;
    class QSingleBbgRequestPrivate;
    class QBbgRequestPrivate;
    class QBBG_EXPORT QSingleBbgRequest : public QBbgAbstractRequest
	{
        Q_DECLARE_PRIVATE(QSingleBbgRequest)
	public:
		QSingleBbgRequest();
		QSingleBbgRequest(const QSingleBbgRequest& a);
		bool operator==(const QSingleBbgRequest& a) const;
		QSingleBbgRequest& operator=(const QSingleBbgRequest& a);
		const QString& GetField() const;
		void SetField(const QString& val);
		const Overrides& GetOverrides() const;
		void SetOverrides(const Overrides& Overr);
		void SetOverride(QString Name, const QVariant& Value);
		void ClearOverrides();
		bool IsValidReq() const;
	protected:
		bool SameOverrides(const QSingleBbgRequest& a)const;
		friend class QBbgRequest;
        friend class QBbgRequestPrivate;
	};
}
#endif // SingleBbgRequest_h__

