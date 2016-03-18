#ifndef QBbgPortfolioDataRequest_h__
#define QBbgPortfolioDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDate>
#include <QObject>
namespace QBbgLib {
    class QBbgPortfolioDataRequestPrivate;
    class QBBG_EXPORT QBbgPortfolioDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        Q_PROPERTY(QString field READ field WRITE setField)
        Q_PROPERTY(QBbgOverride overrides READ overrides WRITE setOverrides)
        Q_PROPERTY(QDate referenceDay READ referenceDay WRITE setReferenceDay)
        Q_DECLARE_PRIVATE(QBbgPortfolioDataRequest)
    public:
        enum PortfolioFields
        {
            PORTFOLIO_MPOSITION,
            PORTFOLIO_MWEIGHT,
            PORTFOLIO_DATA,
            PORTFOLIO_MEMBERS
        };
        Q_ENUM(PortfolioFields)
        virtual ~QBbgPortfolioDataRequest();
        QBbgPortfolioDataRequest();
        QBbgPortfolioDataRequest(const QBbgPortfolioDataRequest& a);
        virtual QBbgPortfolioDataRequest& operator=(const QBbgPortfolioDataRequest& a);
        virtual void setPortfolio(const QString& tradingSystem, const QString& firmID, const QString& portfolioID);
        virtual void setField(const QString& val);
        Q_INVOKABLE virtual void setField(PortfolioFields val);
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