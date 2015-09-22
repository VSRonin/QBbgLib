#ifndef QBbgAbstractResponse_p_h__
#define QBbgAbstractResponse_p_h__
#include "QBbgAbstractResponse.h"
#include <QString>
namespace QBbgLib {
    class QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractResponse)
        QBbgAbstractResponsePrivate(const QBbgAbstractResponsePrivate& other);
    public:
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, QBbgAbstractResponse::ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, const QBbgAbstractResponsePrivate& other);
        virtual QBbgAbstractResponsePrivate& operator=(const QBbgAbstractResponsePrivate& other);
        QBbgAbstractResponse::BbgErrorCodes m_ErrorCode;
        QString m_ErrorMessage;
        const QBbgAbstractResponse::ResponseType m_ResType;
        qint64 m_ID;
    protected:
        QBbgAbstractResponse* q_ptr;
    };

    

}
#endif // QBbgAbstractResponse_p_h__