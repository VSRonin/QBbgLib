#ifndef QBbgPortfolioDataRequest_p_h__
#define QBbgPortfolioDataRequest_p_h__
#include "QbbgPortfolioDataRequest.h"
#include "QBbgAbstractFieldRequest_p.h"
namespace QBbgLib {
    class QBbgPortfolioDataRequestPrivate : public QBbgAbstractFieldRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgPortfolioDataRequest)
    public:
        virtual ~QBbgPortfolioDataRequestPrivate();
        QBbgPortfolioDataRequestPrivate(QBbgPortfolioDataRequest* q);
        QBbgPortfolioDataRequestPrivate(QBbgPortfolioDataRequest* q, const QBbgPortfolioDataRequestPrivate& other);
        virtual QBbgPortfolioDataRequestPrivate& operator=(const QBbgPortfolioDataRequestPrivate& other);
    private:
        QBbgPortfolioDataRequestPrivate(const QBbgPortfolioDataRequestPrivate& other);
        
    };

    

}
#endif // QBbgPortfolioDataRequest_p_h__