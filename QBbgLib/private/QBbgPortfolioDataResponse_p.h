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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

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
        double positionMultiplier(QBbgLib::QBbgSecurity::YellowKeys val) const;

    };
    
}
#endif // QBbgPortfolioDataResponse_p_h__