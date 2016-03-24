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
class QVariant;
namespace QBbgLib {
    class QBbgHistoricalDataResponsePrivate;
    class QBBG_EXPORT QBbgHistoricalDataResponse : public QBbgAbstractFieldResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgHistoricalDataResponse)
    public:
        virtual ~QBbgHistoricalDataResponse();
        QBbgHistoricalDataResponse();
        QBbgHistoricalDataResponse(const QBbgHistoricalDataResponse& other);
        virtual QBbgHistoricalDataResponse& operator=(const QBbgHistoricalDataResponse& other);
        virtual qint32 size() const;
        virtual bool isEmpty() const;
        virtual QVariant value(const QDate& a) const;
        virtual QVariant value(const QString& period) const;
        virtual QVariant value(int period) const;
        virtual QList<QDate> findValues(const QVariant& a) const;
        virtual QString periodForDate(const QDate& a)const;
        virtual QDate dateForPeriod(const QString& period)const;
        virtual QDate date(int period) const;
        virtual QList<QDate> dates() const;
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