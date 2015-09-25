#ifndef QBbgSecurity_p_h__
#define QBbgSecurity_p_h__
#include "QBbgSecurity.h"
#include <QString>
namespace QBbgLib {
    class QBbgSecurityPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgSecurity)
        QBbgSecurity* q_ptr;
        QBbgSecurityPrivate(const QBbgSecurityPrivate& other);
    public:
        virtual ~QBbgSecurityPrivate();
        QBbgSecurityPrivate(QBbgSecurity* q);
        QBbgSecurityPrivate(QBbgSecurity* q,const QBbgSecurityPrivate& other);
        QBbgSecurityPrivate& operator=(const QBbgSecurityPrivate& other);
        bool operator==(const QBbgSecurityPrivate& other) const;
        QString m_Name;
        QBbgSecurity::YellowKeys m_Extension;
        QString m_Exchange;
        QString m_PricingSource;
    };

   

    

    

    

}
#endif // QBbgSecurity_p_h__