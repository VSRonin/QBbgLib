#ifndef QBbgPortfolioDataRequest_h__
#define QBbgPortfolioDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDate>
namespace QBbgLib {
    class QBbgPortfolioDataRequestPrivate;
    class QBBG_EXPORT QBbgPortfolioDataRequest : public QBbgAbstractFieldRequest
    {
        Q_DECLARE_PRIVATE(QBbgPortfolioDataRequest)
    public:
        enum PortfolioFields
        {
            PORTFOLIO_MPOSITION,
            PORTFOLIO_MWEIGHT,
            PORTFOLIO_DATA,
            PORTFOLIO_MEMBER
        };
        QBbgPortfolioDataRequest();
        QBbgPortfolioDataRequest(const QBbgPortfolioDataRequest& a);
        virtual QBbgPortfolioDataRequest& operator=(const QBbgPortfolioDataRequest& a);
        virtual void setPortfolio(const QString& tradingSystem, const QString& firmID, const QString& portfolioID);
        virtual void setField(const QString& val);
        virtual void setField(PortfolioFields val);
        virtual void setSecurity(const QBbgSecurity& val);
        using QBbgAbstractFieldRequest::setSecurity;
        virtual void setOverrides(const QBbgOverride& Overr);
        virtual void setReferenceDay(const QDate& val);
        virtual QDate referenceDay() const;
    protected:
        QBbgPortfolioDataRequest(QBbgPortfolioDataRequestPrivate* d);
    };
}
#endif // QBbgPortfolioDataRequest_h__