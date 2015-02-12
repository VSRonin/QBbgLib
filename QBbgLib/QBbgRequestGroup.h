#ifndef QBbgRequest_h__
#define QBbgRequest_h__

#include "QBbgProjectGlobals.h"
#include "QBbgGenerals.h"
#include "QBbgSecurity.h"
#include "QBbgAbstractRequest.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
    class QBbgRequestGroupPrivate;
	class QBBG_EXPORT QBbgRequestGroup
	{
    private:
        Q_DECLARE_PRIVATE(QBbgRequestGroup)
        QBbgRequestGroupPrivate* d_ptr;
	public:
		QBbgRequestGroup();
		QBbgRequestGroup(const QBbgRequestGroup& a);
		QBbgRequestGroup& operator=(const QBbgRequestGroup& a);
		virtual ~QBbgRequestGroup();
        virtual qint32 size() const;
        virtual const QBbgAbstractRequest* request(qint64 ID) const;
        virtual QList<qint64> findSecurity(const QBbgSecurity& Secur)const;
        virtual QList<qint64> IDList() const;
        void addRequest(const QBbgAbstractRequest& a);
		bool isValidReq() const;
		void clear();
        QList<QBbgAbstractRequest::RequestType> differentTypes() const;
	protected:
        QBbgAbstractRequest* FindEditRequest(qint64 ID);
		void RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID = 1i64)const;
	};
}
#endif // QBbgRequest_h__