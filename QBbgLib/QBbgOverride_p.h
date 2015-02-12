#ifndef QBbgOverride_p_h__
#define QBbgOverride_p_h__
#include "QBbgOverride.h"
#include <QHash>
#include <QString>
namespace QBbgLib {
    class QBbgOverridePrivate
    {
        Q_DECLARE_PUBLIC(QBbgOverride)
        QBbgOverridePrivate(const QBbgOverridePrivate& other);
    public:
        QBbgOverridePrivate(QBbgOverride* q);
        QBbgOverridePrivate(QBbgOverride* q, const QBbgOverridePrivate& other);
        QBbgOverridePrivate& operator=(const QBbgOverridePrivate& other);
    protected:
        QBbgOverride* q_ptr;
        QHash<QString, QString> m_Overrides;
    };
}
#endif // QBbgOverride_p_h__