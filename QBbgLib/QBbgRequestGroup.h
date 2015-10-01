#ifndef QBbgRequest_h__
#define QBbgRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgSecurity.h"
#include "QBbgAbstractRequest.h"
#include <QList> 
#include <QHash>
#include <QString>
namespace QBbgLib {
    class QBbgRequestGroupPrivate;
    class QBbgRequestResponseWorker;
    class QBbgRequestResponseWorkerPrivate;
	class QBBG_EXPORT QBbgRequestGroup
	{
    private:
        Q_DECLARE_PRIVATE(QBbgRequestGroup)
        QBbgRequestGroupPrivate* d_ptr;
        virtual const QBbgAbstractRequest* const request(qint64 ID) const;
	public:
		QBbgRequestGroup();
		QBbgRequestGroup(const QBbgRequestGroup& a);
		QBbgRequestGroup& operator=(const QBbgRequestGroup& a);
		virtual ~QBbgRequestGroup();
        virtual qint32 size() const;
        virtual QList<qint64> findSecurity(const QBbgSecurity& Secur)const;
        virtual QList<qint64> IDList() const;
        qint64 addRequest(const QBbgAbstractRequest& a);
		bool isValidReq() const;
		void clear();
        QList<QBbgAbstractRequest::RequestType> differentTypes() const;
        template <class T = QBbgAbstractRequest> const T* const getRequest(qint64 ID) const
        {
            static_assert(std::is_base_of<QBbgAbstractRequest, T>::value, "getRequest Template type must be derived from QBbgAbstractRequest");
            const QBbgAbstractRequest* const genericRq = request(ID);
            if(!genericRq)
                return NULL;
            if (!std::is_same<QBbgAbstractRequest, T>::value) {
                switch (genericRq->requestType()) {
                case QBbgAbstractRequest::RequestType::ReferenceData:
                    if (!std::is_same<QBbgReferenceDataRequest, T>::value)
                        return NULL;
                    break;
                case QBbgAbstractRequest::RequestType::HistoricalData:
                    if (!std::is_same<QBbgHistoricalDataRequest, T>::value)
                        return NULL;
                    break;
                case QBbgAbstractRequest::RequestType::PortfolioData:
                    if (!std::is_same<QBbgPortfolioDataRequest, T>::value)
                        return NULL;
                    break;
                default:
                    Q_UNREACHABLE(); //Unhandled request type
                }
            }
            return static_cast<const T* const>(genericRq);
        }
	protected:
        QBbgAbstractRequest* FindEditRequest(qint64 ID);
		void RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID = 1i64)const;
        QList<QString> differentServices() const;

        friend class QBbgRequestResponseWorker;
        friend class QBbgRequestResponseWorkerPrivate;
	};
}
#endif // QBbgRequest_h__