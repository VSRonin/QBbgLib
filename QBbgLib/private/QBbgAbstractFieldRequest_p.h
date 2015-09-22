#include "QBbgAbstractFieldRequest.h"
#include "QBbgAbstractRequest_p.h"
#include "QBbgOverride.h"
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate : public QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgAbstractFieldRequest)
    private:
        QBbgAbstractFieldRequestPrivate(const QBbgAbstractFieldRequestPrivate& a);
    public:
        QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, const QBbgAbstractFieldRequestPrivate& a);
        QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, QBbgAbstractRequest::RequestType typ/*=QBbgAbstractRequest::Invalid*/);
        QBbgAbstractFieldRequestPrivate& operator=(const QBbgAbstractFieldRequestPrivate& a);
        bool operator==(const QBbgAbstractFieldRequestPrivate& a) const;
        QString m_Field;
        QBbgOverride m_Overrides;
        bool SameOverrides(const QBbgAbstractFieldRequestPrivate& a)const;
    };
}