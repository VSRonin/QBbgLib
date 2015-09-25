#ifndef QBbgAbstractRequest_p_h__
#define QBbgAbstractRequest_p_h__
#include "QBbgAbstractRequest.h"
#include <QString>
#include "QBbgSecurity.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgAbstractRequest)
    protected:
        QBbgAbstractRequest* q_ptr;
    private:
        QBbgAbstractRequestPrivate(const QBbgAbstractRequestPrivate& other);
    public:
        virtual ~QBbgAbstractRequestPrivate();
        QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, QBbgAbstractRequest::RequestType typ/*=QBbgAbstractRequest::Invalid*/);
        QBbgAbstractRequestPrivate(QBbgAbstractRequest* q,const QBbgAbstractRequestPrivate& other);
        virtual QBbgAbstractRequestPrivate& operator=(const QBbgAbstractRequestPrivate& other);
        qint64 m_ID;
        QBbgSecurity m_Security;
        const QBbgAbstractRequest::RequestType m_RqType;
    };
}
#endif // QBbgAbstractRequest_p_h__