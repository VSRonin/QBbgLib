#ifndef QBbgRequest_p_h__
#define QBbgRequest_p_h__
#include "QBbgRequest.h"
#include "QBbgGenerals.h"
namespace QBbgLib {
    class QBbgRequestPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgRequest)
        QBbgRequest* q_ptr;
        QBbgRequestPrivate(const QBbgRequestPrivate& a);
    public:
        QBbgRequestPrivate(QBbgRequest* q,const QBbgRequestPrivate& a);
        QBbgRequestPrivate(QBbgRequest* q);
        QBbgRequestPrivate& operator=(const QBbgRequestPrivate& a);
        virtual ~QBbgRequestPrivate();
        qint64 MaxID;
        BbgErrorCodes m_ErrorCode;
        QHash<qint64, QSingleBbgRequest*>  ResultTable;
        void ClearRequests();
        bool SameRequest(const QList<qint64>& a, const QList<qint64>& b) const;
        const QSingleBbgRequest* FindRequest(qint64 ID) const;
    };

}
#endif // QBbgRequest_p_h__