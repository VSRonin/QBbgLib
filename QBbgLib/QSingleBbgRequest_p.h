#include "QSingleBbgRequest.h"
#include "QBbgAbstractRequest_p.h"
namespace QBbgLib {
    class QSingleBbgRequestPrivate : public QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QSingleBbgRequest)
    private:
        QSingleBbgRequestPrivate(const QSingleBbgRequestPrivate& a);
    public:
        QSingleBbgRequestPrivate(QSingleBbgRequest* q, const QSingleBbgRequestPrivate& a);
        QSingleBbgRequestPrivate(QSingleBbgRequest* q);
        QSingleBbgRequestPrivate& operator=(const QSingleBbgRequestPrivate& a);
        bool operator==(const QSingleBbgRequestPrivate& a) const;
        QString m_Field;
        Overrides m_Overrides;
        bool SameOverrides(const QSingleBbgRequestPrivate& a)const;
    };
}