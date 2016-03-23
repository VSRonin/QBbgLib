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

#ifndef QBbgPortfolioDataRequest_h__
#define QBbgPortfolioDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QDate>
#include <QObject>
namespace QBbgLib {
    class QBbgPortfolioDataRequestPrivate;
    /*!
    \brief A portfolio request
    \details This class allows to request data regarding portfolios set up in PRTU on the terminal.<br/>
    Only securities with the QBbgSecurity::Client extension can be used.<br/>
    This is equivalent to using BDS() bloomberg function with a Client security in excel.
    */
    class QBBG_EXPORT QBbgPortfolioDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        /*!
        \brief The security associated with the request
        \getter security()
        \setter setSecurity()
        */
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        /*!
        \brief The field associated with the request
        \getter field()
        \setter setField()
        */
        Q_PROPERTY(QString field READ field WRITE setField)
        /*!
        \brief The overrides applied to the request
        \getter overrides()
        \setter setOverrides()
        */
        Q_PROPERTY(QBbgOverride overrides READ overrides WRITE setOverrides)
        /*!
        \brief The portfolio reference date
        \getter referenceDay()
        \setter setReferenceDay()
        */
        Q_PROPERTY(QDate referenceDay READ referenceDay WRITE setReferenceDay)
        Q_DECLARE_PRIVATE(QBbgPortfolioDataRequest)
    public:
        //! Available fields for the request
        enum class PortfolioFields
        {
            PORTFOLIO_MPOSITION, /*!< The list of securities and nominal of holdings in the portfolio */
            PORTFOLIO_MWEIGHT, /*!< The list of securities and relative weight of holdings in the portfolio */
            PORTFOLIO_DATA, /*!< All available portfolio data */
            PORTFOLIO_MEMBERS /*!< The list of securities in the portfolio */
        };
        Q_ENUM(PortfolioFields)
        //! Destructor
        virtual ~QBbgPortfolioDataRequest();
        //! Creates an empty portfolio request
        QBbgPortfolioDataRequest();
        //! Creates a copy of another portfolio request
        QBbgPortfolioDataRequest(const QBbgPortfolioDataRequest& a);
        //! Copies another portfolio request
        virtual QBbgPortfolioDataRequest& operator=(const QBbgPortfolioDataRequest& a);
        /*!
        \brief AIM/TOMS users can download their portfolios specifying the parameters
        \arg tradingSystem The trading system code (e.g. TS)
        \arg firmID the firm id shown in all AIM/TOMS pages in the command bar, without # or spaces
        \arg portfolioID The id of the portfolio shown in the rightmost column of PRTU
        */
        virtual void setPortfolio(const QString& tradingSystem, const QString& firmID, const QString& portfolioID);
        //! Reimplemented from QBbgAbstractFieldRequest::setField
        virtual void setField(const QString& val);
        //! Sets the field to one of the 4 allowed ones for portfolio requests
        Q_INVOKABLE virtual void setField(PortfolioFields val);
        //! Reimplemented from QBbgAbstractRequest::setSecurity
        virtual void setSecurity(const QBbgSecurity& val);
        /*!
        \brief Reimplemented from QBbgAbstractFieldRequest::setOverrides
        \note The only allowed override is for this request is REFERENCE_DATE
        */
        virtual void setOverrides(const QBbgOverride& Overr);
        /*!
        \brief Sets the date for which to retrieve the portfolio
        \details a null QDate will retrieve the current live portfolio
        */
        virtual void setReferenceDay(const QDate& val);
        //! Returns the portfolio reference date or null if not set
        virtual QDate referenceDay() const;
        using QBbgAbstractFieldRequest::setSecurity;
    protected:
        QBbgPortfolioDataRequest(QBbgPortfolioDataRequestPrivate* d);
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgPortfolioDataRequest);
#endif // QBbgPortfolioDataRequest_h__