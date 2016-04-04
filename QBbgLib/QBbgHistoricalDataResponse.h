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

#ifndef QBbgHistoricalDataResponse_h__
#define QBbgHistoricalDataResponse_h__
#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
#include <QDate>
#include <QList>
#include <QVariant>
namespace QBbgLib {
    class QBbgHistoricalDataResponsePrivate;
    //! A response for historical data series
    class QBBG_EXPORT QBbgHistoricalDataResponse : public QBbgAbstractFieldResponse
    {
        Q_GADGET
        /*!
        \brief Number of values in the series
        \getter size()
        */
        Q_PROPERTY(int size READ size)
        /*!
        \brief All dates in the series
        \getter dates()
        */
        Q_PROPERTY(QList<QDate> dates READ dates)
        /*!
        \brief All period codes in the series
        \getter periods()
        */
        Q_PROPERTY(QList<QString> periods READ periods)
    private:
        Q_DECLARE_PRIVATE(QBbgHistoricalDataResponse)
    public:
        //! Destructor
        virtual ~QBbgHistoricalDataResponse();
        //! Creates an empty historical response
        QBbgHistoricalDataResponse();
        //! Creates a copy of another historical response
        QBbgHistoricalDataResponse(const QBbgHistoricalDataResponse& other);
        //! Copies another historical response
        virtual QBbgHistoricalDataResponse& operator=(const QBbgHistoricalDataResponse& other);
        //! Number of values in the series
        virtual int size() const;
        //! Reimplemented from QBbgAbstractResponse::isEmpty()
        virtual bool isEmpty() const;
        //! Returns the value associated for the selected date 
        Q_INVOKABLE virtual QVariant value(const QDate& a) const;
        /*! 
        \brief Returns the value associated with the selected period in the series
        \details Use: 
        <ul><li>CY1 yyyy for yearly data</li>
        <li>CS# yyyy for semiannual data where # is 1 or 2</li>
        <li>CQ# yyyy for quarterly data where # is 1, 2, 3 or 4</li></ul>
        replacing yyyy with the year you want to retrieve the data for
        \note This method will work only if you called QBbgHistoricalDataRequest::setUseRelativeDate(true) on its associated request
        */
        Q_INVOKABLE virtual QVariant value(const QString& period) const;
        //! Returns the value for the nth element in the series
        Q_INVOKABLE virtual QVariant value(int period) const;
        //! Returns all the dates for which the series has the selected value
        Q_INVOKABLE virtual QList<QDate> findValues(const QVariant& a) const;
        /*! 
        \brief Returns the period code for the selected date in the series
        \note This method will work only if you called QBbgHistoricalDataRequest::setUseRelativeDate(true) on its associated request
        */
        Q_INVOKABLE virtual QString periodForDate(const QDate& a)const;
        /*!
        \brief Returns the date associated with the selected period in the series
        \details Use:
        <ul><li>CY1 yyyy for yearly data</li>
        <li>CS# yyyy for semiannual data where # is 1 or 2</li>
        <li>CQ# yyyy for quarterly data where # is 1, 2, 3 or 4</li></ul>
        replacing yyyy with the year you want to retrieve the date for
        \note This method will work only if you called QBbgHistoricalDataRequest::setUseRelativeDate(true) on its associated request
        */
        Q_INVOKABLE virtual QDate dateForPeriod(const QString& period)const;
        //! Returns the nth date in the series
        Q_INVOKABLE virtual QDate date(int period) const;
        //! Returns all dates in the series
        virtual QList<QDate> dates() const;
        /*!
        \brief Returns all period codes in the series
        \note This method will work only if you called QBbgHistoricalDataRequest::setUseRelativeDate(true) on its associated request
        */
        virtual QList<QString> periods() const;
    protected:
        QBbgHistoricalDataResponse(QBbgHistoricalDataResponsePrivate* dp);
        virtual void setValue(const QDate& dt, const QVariant& val, const QString& period = QString(), const QString& Header = QString());
        virtual void clear();
        friend class QBbgRequestResponseWorker;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgHistoricalDataResponse);
#endif // QBbgHistoricalDataResponse_h__