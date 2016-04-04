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