/*******************************************************************************\
* This file is part of QBbgLib.                                                 *
*                                                                               *
* QBbgLib is free software : you can redistribute it and / or modify            *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* QBbgLib is distributed in the hope that it will be useful,                    *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                   *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QBbgPortfolioDataResponse_h__
#define QBbgPortfolioDataResponse_h__

#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
class QDate;
namespace QBbgLib {
    class QBbgPortfolioDataResponsePrivate;
    class QBbgSecurity;
    class QBBG_EXPORT QBbgPortfolioDataResponse : public QBbgAbstractFieldResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgPortfolioDataResponse)
    public:
        virtual ~QBbgPortfolioDataResponse();
        QBbgPortfolioDataResponse();
        QBbgPortfolioDataResponse(QBbgPortfolioDataResponse& other);
        virtual QBbgPortfolioDataResponse& operator=(QBbgPortfolioDataResponse& other);
        virtual size_t size() const;
        virtual QBbgSecurity security(size_t index) const;
        virtual double position(size_t index) const;
        virtual double marketValue(size_t index) const;
        virtual double cost(size_t index) const;
        virtual QDate costDate(size_t index) const;
        virtual double costFx(size_t index) const;
        virtual double weight(size_t index) const;
        virtual bool hasPosition() const;
        virtual bool hasMarketValue() const;
        virtual bool hasCost() const;
        virtual bool hasCostDate() const;
        virtual bool hasCostFx() const;
        virtual bool hasWeight() const;
        virtual bool isEmpty() const;
    protected:
        QBbgPortfolioDataResponse(QBbgPortfolioDataResponsePrivate* dp);
        virtual void addSecurity(const QBbgSecurity& val);
        virtual void addPosition(double val);
        virtual void addMarketValue(double val);
        virtual void addCost(double val);
        virtual void addCostDate(const QDate& val);
        virtual void addCostFx(double val);
        virtual void addWeight(double val);
        virtual void clear();

        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgPortfolioDataResponse_h__