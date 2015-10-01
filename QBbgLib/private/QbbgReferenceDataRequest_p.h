#ifndef QbbgReferenceDataRequest_p_h__
#define QbbgReferenceDataRequest_p_h__
#include "QbbgReferenceDataRequest.h"
#include "QBbgAbstractFieldRequest_p.h"
namespace QBbgLib {
    class QBbgReferenceDataRequestPrivate : public QBbgAbstractFieldRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgReferenceDataRequest)
    public:
        virtual ~QBbgReferenceDataRequestPrivate();
        QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q);
        QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q, const QBbgReferenceDataRequestPrivate& other);
        virtual QBbgReferenceDataRequestPrivate& operator=(const QBbgReferenceDataRequestPrivate& other);
        virtual bool operator==(const QBbgReferenceDataRequestPrivate& a) const;
    private:
        QBbgReferenceDataRequestPrivate(const QBbgReferenceDataRequestPrivate& other);
        bool m_UseUTCTime;
    };
}
#endif // QbbgReferenceDataRequest_p_h__