#ifndef QBbgHistoricalDataResponse_p_h__
#define QBbgHistoricalDataResponse_p_h__
#include "QBbgHistoricalDataResponse.h"
#include "QBbgAbstractFieldResponse_p.h"
#include "QBbgSecurity.h"
#include <QList>
#include <QDate>
namespace QBbgLib {
    class QBbgHistoricalDataResponsePrivate : public QBbgAbstractFieldResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgHistoricalDataResponse)
        QBbgHistoricalDataResponsePrivate(const QBbgHistoricalDataResponsePrivate& other);
    public:
        QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q, const QBbgHistoricalDataResponsePrivate& other);
        QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q);
        virtual QBbgHistoricalDataResponsePrivate& operator=(const QBbgHistoricalDataResponsePrivate& other);
        QMap<QDate, QVariant> m_values;
        QMap<QDate, QString> m_relDates;
    };

    

}
#endif // QBbgHistoricalDataResponse_p_h__