#ifndef QBbgAbstractResponse_p_h__
#define QBbgAbstractResponse_p_h__
#include "QBbgGenerals.h"
#include "QBbgAbstractResponse.h"
namespace QBbgLib {
    class QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractResponse)
        QBbgAbstractResponsePrivate(const QBbgAbstractResponsePrivate& other);
    public:
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q);
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, const QBbgAbstractResponsePrivate& other);
        virtual QBbgAbstractResponsePrivate& operator=(const QBbgAbstractResponsePrivate& other);
        QBbgAbstractResponse::BbgErrorCodes m_ErrorCode;
        QBbgAbstractResponse::ResponseType m_ResType;
        qint64 m_ID;
    protected:
        QBbgAbstractResponse* q_ptr;
    };

    

}
#endif // QBbgAbstractResponse_p_h__