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

#ifndef QBbgPortfolioDataResponse_h__
#define QBbgPortfolioDataResponse_h__

#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
class QDate;
namespace QBbgLib {
    class QBbgPortfolioDataResponsePrivate;
    class QBbgSecurity;
    /*! 
    \brief A response for portfolio information.
    \details The results will be ordered by currency then by yellow key then by security name. Cash will always appear at the end of the list.
    */
    class QBBG_EXPORT QBbgPortfolioDataResponse : public QBbgAbstractFieldResponse
    {
        Q_GADGET
        /*!
        \brief Number of securities in the portfolio
        \getter size()
        */
        Q_PROPERTY(int size READ size)
        /*!
        \brief The result contains the nominal amount of the securities in the portfolio
        \getter hasPosition()
        */
        Q_PROPERTY(bool hasPosition READ hasPosition)
        /*!
        \brief The result contains the market value of the securities in the portfolio
        \getter hasMarketValue()
        */
        Q_PROPERTY(bool hasMarketValue READ hasMarketValue)
        /*!
        \brief The result contains the cost of the securities in the portfolio
        \getter hasCost()
        */
        Q_PROPERTY(bool hasCost READ hasCost)
        /*!
        \brief The result contains the cost date of the securities in the portfolio
        \getter hasCostDate()
        */
        Q_PROPERTY(bool hasCostDate READ hasCostDate)
        /*!
        \brief The result contains the cost FX rate of the securities in the portfolio
        \getter hasCostFx()
        */
        Q_PROPERTY(bool hasCostFx READ hasCostFx)
        /*!
        \brief The result contains the relative weight of the securities in the portfolio
        \getter hasWeight()
        */
        Q_PROPERTY(bool hasWeight READ hasWeight)
    private:
        Q_DECLARE_PRIVATE(QBbgPortfolioDataResponse)
    public:
        //! Destructor
        virtual ~QBbgPortfolioDataResponse();
        //! Creates an empty portfolio response
        QBbgPortfolioDataResponse();
        //! Creates a copy of another portfolio response
        QBbgPortfolioDataResponse(const QBbgPortfolioDataResponse& other);
        //! Copies another portfolio response
        virtual QBbgPortfolioDataResponse& operator=(const QBbgPortfolioDataResponse& other);
        //! Returns the number of securities in the portfolio
        virtual int size() const;
        /*! 
        \brief Returns the nth security in the list
        \details If index is out of range an invalid security will be returned
        */
        Q_INVOKABLE virtual QBbgSecurity security(int index) const;
        /*!
        \brief Returns the nominal amount of the nth security in the portfolio
        \details If index is out of range or hasPosition() is false, 0 returned
        */
        Q_INVOKABLE virtual double position(int index) const;
        /*!
        \brief Returns the market value of the nth security in the portfolio
        \details If index is out of range or hasMarketValue() is false, 0 returned
        */
        Q_INVOKABLE virtual double marketValue(int index) const;
        /*!
        \brief Returns the cost of the nth security in the portfolio
        \details If index is out of range or hasCost() is false, 0 returned
        */
        Q_INVOKABLE virtual double cost(int index) const;
        /*!
        \brief Returns the cost date of the nth security in the portfolio
        \details If index is out of range or hasCostDate() is false, a null date is returned
        */
        Q_INVOKABLE virtual QDate costDate(int index) const;
        /*!
        \brief Returns the cost FX rate of the nth security in the portfolio
        \details If index is out of range or hasCostFx() is false, 0 returned
        */
        Q_INVOKABLE virtual double costFx(int index) const;
        /*!
        \brief Returns the cost relative weight of the nth security in the portfolio
        \details If index is out of range or hasWeight() is false, 0 returned
        */
        Q_INVOKABLE virtual double weight(int index) const;
        //! Checks if result contains the nominal amount of the securities in the portfolio
        virtual bool hasPosition() const;
        //! Checks if result contains the market value of the securities in the portfolio
        virtual bool hasMarketValue() const;
        //! Checks if result contains the cost of the securities in the portfolio
        virtual bool hasCost() const;
        //! Checks if result contains the cost date of the securities in the portfolio
        virtual bool hasCostDate() const;
        //! Checks if result contains the cost FX rate of the securities in the portfolio
        virtual bool hasCostFx() const;
        //! Checks if result contains the relative weight of the securities in the portfolio
        virtual bool hasWeight() const;
        //! Reimplemented from QBbgAbstractResponse::isEmpty()
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
Q_DECLARE_METATYPE(QBbgLib::QBbgPortfolioDataResponse);
#endif // QBbgPortfolioDataResponse_h__