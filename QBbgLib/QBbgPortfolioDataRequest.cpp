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

#include "QbbgPortfolioDataRequest.h"
#include "private/QbbgPortfolioDataRequest_p.h"
#include "QBbgSecurity.h"
namespace QBbgLib {
    QBbgPortfolioDataRequest::~QBbgPortfolioDataRequest() = default;
    QBbgPortfolioDataRequestPrivate::~QBbgPortfolioDataRequestPrivate() = default;
    void QBbgPortfolioDataRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() == QBbgSecurity::Client) {
            QBbgAbstractFieldRequest::setSecurity(val);
        }
    }
    void QBbgPortfolioDataRequest::setOverrides(const QBbgOverride& Overr)
    {
        if (Overr.contains("REFERENCE_DATE")) {
            QBbgOverride NewOverr;
            NewOverr.setOverride("REFERENCE_DATE", Overr.overrideValue("REFERENCE_DATE"));
            QBbgAbstractFieldRequest::setOverrides(NewOverr);
            return;
        }
        clearOverrides();
    }
    void QBbgPortfolioDataRequest::setReferenceDay(const QDate& val)
    {
        if (val.isNull()) return clearOverrides();
        QBbgOverride NewOverr;
        NewOverr.setOverride("REFERENCE_DATE", val);
        QBbgAbstractFieldRequest::setOverrides(NewOverr);
    }

    QDate QBbgPortfolioDataRequest::referenceDay() const
    {
        Q_D(const QBbgPortfolioDataRequest);
        if (d->m_Overrides.contains("REFERENCE_DATE"))
            return QDate::fromString(d->m_Overrides.overrideValue("REFERENCE_DATE"),"yyyyMMdd");
        return QDate();
    }

    QBbgPortfolioDataRequest::QBbgPortfolioDataRequest()
        :QBbgAbstractFieldRequest(new QBbgPortfolioDataRequestPrivate(this))
    {}
    QBbgPortfolioDataRequest::QBbgPortfolioDataRequest(const QBbgPortfolioDataRequest& a)
        : QBbgAbstractFieldRequest(new QBbgPortfolioDataRequestPrivate(this,*(a.d_func())))
    {}

    QBbgPortfolioDataRequest& QBbgPortfolioDataRequest::operator=(const QBbgPortfolioDataRequest& a)
    {
        QBbgAbstractFieldRequest::operator=(a);
        return *this;
    }
    void QBbgPortfolioDataRequest::setPortfolio(const QString& tradingSystem, const QString& firmID, const QString& portfolioID)
    {
        return setSecurity((tradingSystem.isEmpty() ? QString():(tradingSystem + '-')) + firmID + '-' + portfolioID, QBbgSecurity::Client);
    }

    void QBbgPortfolioDataRequest::setField(const QString& val)
    {
        QBbgAbstractFieldRequest::setField(val);
        if (
            field() != "PORTFOLIO_MPOSITION"
            && field() != "PORTFOLIO_MWEIGHT"
            && field() != "PORTFOLIO_DATA"
            && field() != "PORTFOLIO_MEMBERS"
        ) 
            QBbgAbstractFieldRequest::setField(QString());
    }

    void QBbgPortfolioDataRequest::setField(PortfolioFields val)
    {
        switch (val) {
        case PortfolioFields::PORTFOLIO_MPOSITION:
            return setField("PORTFOLIO_MPOSITION");
        case PortfolioFields::PORTFOLIO_MWEIGHT:
            return setField("PORTFOLIO_MWEIGHT");
        case PortfolioFields::PORTFOLIO_DATA:
            return setField("PORTFOLIO_DATA");
        case PortfolioFields::PORTFOLIO_MEMBERS:
            return setField("PORTFOLIO_MEMBERS");
        default:
            Q_UNREACHABLE();
        }
    }

    QBbgPortfolioDataRequestPrivate::QBbgPortfolioDataRequestPrivate(QBbgPortfolioDataRequest* q)
        :QBbgAbstractFieldRequestPrivate(q, QBbgAbstractRequest::RequestType::PortfolioData)
    {
    }
    QBbgPortfolioDataRequestPrivate::QBbgPortfolioDataRequestPrivate(QBbgPortfolioDataRequest* q, const QBbgPortfolioDataRequestPrivate& other)
        : QBbgAbstractFieldRequestPrivate(q, other)
    {
    }
    QBbgPortfolioDataRequestPrivate& QBbgPortfolioDataRequestPrivate::operator=(const QBbgPortfolioDataRequestPrivate& other)
    {
        QBbgAbstractFieldRequestPrivate::operator=(other);
        return *this;
    }
}

