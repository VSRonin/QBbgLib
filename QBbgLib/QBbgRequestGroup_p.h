#ifndef QBbgRequest_p_h__
#define QBbgRequest_p_h__
#include "QBbgRequestGroup.h"
#include <QHash>
namespace QBbgLib {
    class QBbgRequestGroupPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgRequestGroup)
        QBbgRequestGroup* q_ptr;
        QBbgRequestGroupPrivate(const QBbgRequestGroupPrivate& a);
        QBbgAbstractRequest* createRequest(const QBbgAbstractRequest& a) const;
        qint64 increaseMaxID();
    public:
        QBbgRequestGroupPrivate(QBbgRequestGroup* q,const QBbgRequestGroupPrivate& a);
        QBbgRequestGroupPrivate(QBbgRequestGroup* q);
        QBbgRequestGroupPrivate& operator=(const QBbgRequestGroupPrivate& a);
        virtual ~QBbgRequestGroupPrivate();
        static qint64 MaxID;
        QHash<qint64, QBbgAbstractRequest*>  RequestTable;
        void clear();
        const QBbgAbstractRequest* request(qint64 ID) const;
        bool SameRequest(const QList<qint64>& a, const QList<qint64>& b) const;
    };

    

    

    

}
#endif // QBbgRequest_p_h__