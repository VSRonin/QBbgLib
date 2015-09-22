#include "QBbgPortfolioDataResponse.h"
#include "private/QBbgPortfolioDataResponse_p.h"
namespace QBbgLib {
    QBbgPortfolioDataResponsePrivate::QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse* q, const QBbgPortfolioDataResponsePrivate& other)
        :QBbgAbstractFieldResponsePrivate(q, other)
        , m_Security(other.m_Security)
        , m_Position(other.m_Position)
        , m_MarketValue(other.m_MarketValue)
        , m_Cost(other.m_Cost)
        , m_CostDate(other.m_CostDate)
        , m_CostFx(other.m_CostFx)
        , m_Weight(other.m_Weight)
    {}

    QBbgPortfolioDataResponsePrivate::QBbgPortfolioDataResponsePrivate(QBbgPortfolioDataResponse* q)
        : QBbgAbstractFieldResponsePrivate(q,QBbgAbstractResponse::ResponseType::PortfolioDataResponse)
    {}

    QBbgPortfolioDataResponsePrivate& QBbgPortfolioDataResponsePrivate::operator=(const QBbgPortfolioDataResponsePrivate& other)
    {
        QBbgAbstractFieldResponsePrivate::operator=(other);
        m_Security = other.m_Security;
        m_Position = other.m_Position;
        m_MarketValue = other.m_MarketValue;
        m_Cost = other.m_Cost;
        m_CostDate = other.m_CostDate;
        m_CostFx = other.m_CostFx;
        m_Weight = other.m_Weight;
        return *this;
    }

    size_t QBbgPortfolioDataResponse::size() const
    {
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_Security.size();
    }

    QBbgSecurity QBbgPortfolioDataResponse::security(size_t index) const
    {
        if (index < 0 || index >= size())
            return QBbgSecurity();
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_Security.at(index);
    }

    double QBbgPortfolioDataResponse::position(size_t index) const
    {
        if (index < 0 || index >= size() || !hasPosition())
            return 0.0;
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_Position.at(index);
    }

    double QBbgPortfolioDataResponse::marketValue(size_t index) const
    {
        if (index < 0 || index >= size() || !hasMarketValue())
            return 0.0;
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_MarketValue.at(index);
    }

    double QBbgPortfolioDataResponse::cost(size_t index) const
    {
        if (index < 0 || index >= size() || !hasCost())
            return 0.0;
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_Cost.at(index);
    }

    double QBbgPortfolioDataResponse::costFx(size_t index) const
    {
        if (index < 0 || index >= size() || !hasCostFx())
            return 0.0;
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_CostFx.at(index);
    }

    double QBbgPortfolioDataResponse::weight(size_t index) const
    {
        if (index < 0 || index >= size() || !hasWeight())
            return 0.0;
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_Weight.at(index);
    }

   QDate QBbgPortfolioDataResponse::costDate(size_t index) const
    {
        if (index < 0 || index >= size() || !hasCostDate())
            return QDate();
        Q_D(const QBbgPortfolioDataResponse);
        return d->m_CostDate.at(index);
    }

   bool QBbgPortfolioDataResponse::hasPosition() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_Position.isEmpty();
   }

   bool QBbgPortfolioDataResponse::hasMarketValue() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_MarketValue.isEmpty();
   }

   bool QBbgPortfolioDataResponse::hasCost() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_Cost.isEmpty();
   }

   bool QBbgPortfolioDataResponse::hasCostDate() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_CostDate.isEmpty();
   }

   bool QBbgPortfolioDataResponse::hasCostFx() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_CostFx.isEmpty();
   }

   bool QBbgPortfolioDataResponse::hasWeight() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return !d->m_Weight.isEmpty();
   }

   void QBbgPortfolioDataResponse::clear()
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_Security.clear();
       d->m_Position.clear();
       d->m_MarketValue.clear();
       d->m_Cost.clear();
       d->m_CostDate.clear();
       d->m_CostFx.clear();
       d->m_Weight.clear();
   }

   void QBbgPortfolioDataResponse::addSecurity(const QBbgSecurity& val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_Security.append(val);
   }

   void QBbgPortfolioDataResponse::addPosition(double val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_Position.append(val);
   }

   void QBbgPortfolioDataResponse::addMarketValue(double val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_MarketValue.append(val);
   }

   void QBbgPortfolioDataResponse::addCost(double val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_Cost.append(val);
   }

   void QBbgPortfolioDataResponse::addCostDate(const QDate& val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_CostDate.append(val);
   }

   void QBbgPortfolioDataResponse::addCostFx(double val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_CostFx.append(val);
   }

   void QBbgPortfolioDataResponse::addWeight(double val)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->m_Weight.append(val);
   }

   QBbgPortfolioDataResponse::QBbgPortfolioDataResponse(QBbgPortfolioDataResponse& other)
       :QBbgAbstractFieldResponse(new QBbgPortfolioDataResponsePrivate(this,*(other.d_func())))
   {}

   QBbgPortfolioDataResponse::QBbgPortfolioDataResponse()
       : QBbgAbstractFieldResponse(new QBbgPortfolioDataResponsePrivate(this))
   {
   }

   QBbgPortfolioDataResponse::QBbgPortfolioDataResponse(QBbgPortfolioDataResponsePrivate* dp)
       : QBbgAbstractFieldResponse(dp)
   {
   }
   QBbgPortfolioDataResponse& QBbgPortfolioDataResponse::operator=(QBbgPortfolioDataResponse& other)
   {
       Q_D(QBbgPortfolioDataResponse);
       d->operator=(*(other.d_func()));
       return *this;
   }

   bool QBbgPortfolioDataResponse::isEmpty() const
   {
       Q_D(const QBbgPortfolioDataResponse);
       return d->m_Security.isEmpty();
   }

}
