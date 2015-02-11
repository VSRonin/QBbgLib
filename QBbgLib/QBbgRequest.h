#ifndef QBbgRequest_h__
#define QBbgRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgGenerals.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
	class QBbgWorker;
    class QBbgWorkerPrivate;
    class QBbgAbstractRequest;
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
        virtual qint32 NumRequests() const;
        virtual const QBbgAbstractRequest* FindRequest(qint64 ID) const;
        virtual QList<qint64> FindSecurity(QString Secur)const;
        virtual QList<qint64> FindField(QString Field)const;
        virtual QList<qint64> FindSecurityField(QString Secur, QString Field)const;
        virtual QList<qint64> IdList() const;
        void AddRequest(const QBbgAbstractRequest& a);
		qint32 GetErrorCode() const;
		QString GetErrorString() const;
		bool HasErrors() const;
		bool IsValidReq() const;
		void ClearRequests();
	protected:
        QBbgAbstractRequest* GetEditRequest(quint32 Index);
        QBbgAbstractRequest* FindEditRequest(qint64 ID);
		void RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID = 1i64)const;
		void ClearResults();
		void SetErrorCode(BbgErrorCodes ErrCd);
		friend class QBbgWorker;
        friend class QBbgWorkerPrivate;
	};
}
#endif // QBbgRequest_h__