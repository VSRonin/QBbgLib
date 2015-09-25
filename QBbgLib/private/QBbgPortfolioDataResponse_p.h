#ifndef QBbgPortfolioDataResponse_p_h__
#define QBbgPortfolioDataResponse_p_h__
#include "QBbgPortfolioDataResponse.h"
#include "QBbgAbstractFieldResponse_p.h"
#include "QBbgSecurity.h"
#include <QList>
#include <QDate>
namespace QBbgLib {
    class QBbgPortfolioDataResponsePrivate : public QBbgAbstractFieldResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgPortfolioDataResponse)
            QBbgPortfolioDataResponsePrivate(const QBbgPortfolioDataResponsePrivate& other);
    public:
        virtual ~QBbgPortfolioDataResponsePrivate();
        QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse* q, const QBbgPortfolioDataResponsePrivate& other);
        QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse* q);
        virtual QBbgPortfolioDataResponsePrivate& operator=(const QBbgPortfolioDataResponsePrivate& other);
        QList<QBbgSecurity> m_Security;
        QList<double> m_Position;
        QList<double> m_MarketValue;
        QList<double> m_Cost;
        QList<QDate> m_CostDate;
        QList<double> m_CostFx;
        QList<double> m_Weight;

    };

    
}
#endif // QBbgPortfolioDataResponse_p_h__