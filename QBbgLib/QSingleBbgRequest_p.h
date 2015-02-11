#include "QSingleBbgRequest.h"
namespace QBbgLib {
    class QSingleBbgRequestPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QSingleBbgRequest)
        QSingleBbgRequest* q_ptr;
        QSingleBbgRequestPrivate(const QSingleBbgRequestPrivate& a);
    public:
        QSingleBbgRequestPrivate(QSingleBbgRequest* q, const QSingleBbgRequestPrivate& a);
        QSingleBbgRequestPrivate(QSingleBbgRequest* q);
        QSingleBbgRequestPrivate& operator=(const QSingleBbgRequestPrivate& a);
        bool operator==(const QSingleBbgRequestPrivate& a) const;
        qint64 m_ResultID;
        QString m_Security;
        YellowKeys m_Extension;
        QString m_Field;
        Overrides m_Overrides;
        bool SameOverrides(const QSingleBbgRequestPrivate& a)const;
    };
}