#ifndef QBbgRequest_h__
#define QBbgRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgGenerals.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
	class QBbgWorker;
    class QBbgWorkerPrivate;
	class QBbgAbstractFieldRequest;
    class QBbgRequestPrivate;
	class QBBG_EXPORT QBbgRequest
	{
    private:
        Q_DECLARE_PRIVATE(QBbgRequest)
        QBbgRequestPrivate* d_ptr;
	public:
		QBbgRequest();
		QBbgRequest(const QBbgRequest& a);
		QBbgRequest& operator=(const QBbgRequest& a);
		virtual ~QBbgRequest();
		qint32 NumRequests() const;
		const QBbgAbstractFieldRequest* GetRequest(quint32 Index) const;
		const QBbgAbstractFieldRequest* FindRequest(qint64 ID) const;
		QList<qint64> FindSecurity(QString Secur)const;
		QList<qint64> FindField(QString Field)const;
		QList<qint64> FindSecurityField(QString Secur, QString Field)const;
		QList<qint64> IdList() const;
		void AddRequest(const QBbgAbstractFieldRequest& a);
		void AddRequest(qint64 ID, const QString& Secur, const QString& Field, YellowKeys YellowKey = Mtge);
		void AddRequest(const QString& Secur, const QString& Field, YellowKeys YellowKey = Mtge);
		void AddRequest(qint64 ID, const QString& Secur, const QString& Field, const Overrides& Overr, YellowKeys YellowKey = Mtge);
		void AddRequest(const QString& Secur, const QString& Field, const Overrides& Overr, YellowKeys YellowKey = Mtge);
		qint32 GetErrorCode() const;
		QString GetErrorString() const;
		bool HasErrors() const;
		bool IsValidReq() const;
		void ClearRequests();
	protected:
		QBbgAbstractFieldRequest* GetEditRequest(quint32 Index);
		QBbgAbstractFieldRequest* FindEditRequest(qint64 ID);
		void RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID = 1)const;
		void ClearResults();
		void SetErrorCode(BbgErrorCodes ErrCd);
		friend class QBbgWorker;
        friend class QBbgWorkerPrivate;
	};
}
#endif // QBbgRequest_h__