#ifndef SingleBbgRequest_h__
#define SingleBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgRequest.h"
#include "QSingleBbgResult.h"
#include <QHash>
namespace QBbgLib {
	class QBbgWorker;
    class QSingleBbgRequestPrivate;
    class QBbgRequestPrivate;
	class QBBG_EXPORT QSingleBbgRequest
	{
    private:
        Q_DECLARE_PRIVATE(QSingleBbgRequest)
        QSingleBbgRequestPrivate* d_ptr;
	public:
		QSingleBbgRequest();
        virtual ~QSingleBbgRequest();
		QSingleBbgRequest(const QSingleBbgRequest& a);
		bool operator==(const QSingleBbgRequest& a) const;
		QSingleBbgRequest& operator=(const QSingleBbgRequest& a);
		qint64 GetResultID() const;
		const QString& GetSecurity() const;
		const QString& GetField() const;
		void SetResultID(qint64 val);
		void SetSecurity(const QString& val);
		void SetField(const QString& val);
		const Overrides& GetOverrides() const;
		void SetOverrides(const Overrides& Overr);
		void SetOverride(QString Name, const QString& Value);
		void ClearOverrides();
		bool IsValidReq() const;
		QString GetExtensionString() const;
		QString GetFullSecurity() const;
		YellowKeys GetExtension()const;
		void SetExtension(const QString& val);
		void SetExtension(YellowKeys val);
	protected:
		bool SameOverrides(const QSingleBbgRequest& a)const;
		friend class QBbgRequest;
        friend class QBbgRequestPrivate;
	};
}
#endif // SingleBbgRequest_h__

