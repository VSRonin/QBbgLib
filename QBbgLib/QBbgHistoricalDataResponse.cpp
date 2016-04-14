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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/ >.             *
*                                                                               *
\*******************************************************************************/

#include "QBbgHistoricalDataResponse.h"
#include "private/QBbgHistoricalDataResponse_p.h"
namespace QBbgLib {
    QBbgHistoricalDataResponse::~QBbgHistoricalDataResponse() = default;
    QBbgHistoricalDataResponsePrivate::~QBbgHistoricalDataResponsePrivate() = default;
    int QBbgHistoricalDataResponse::size() const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return d->m_values.size();
    }

    bool QBbgHistoricalDataResponse::isEmpty() const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return d->m_values.isEmpty();
    }

    QVariant QBbgHistoricalDataResponse::value(const QDate& a) const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return  d->m_values.value(a, QVariant());
    }

    QVariant QBbgHistoricalDataResponse::value(const QString& period) const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return  d->m_values.value(dateForPeriod(period), QVariant());
    }

    QVariant QBbgHistoricalDataResponse::value(int period) const
    {
        if (period < 0 || period >= size()) return QVariant();
        Q_D(const QBbgHistoricalDataResponse);
        return  (d->m_values.constBegin() + period).value();
    }
    QDate QBbgHistoricalDataResponse::date(int period) const
    {
        if (period < 0 || period >= size()) return QDate();
        Q_D(const QBbgHistoricalDataResponse);
        return  (d->m_values.constBegin() + period).key();
    }

    QList<QDate> QBbgHistoricalDataResponse::findValues(const QVariant& a) const
    {
        QList<QDate> result;
        Q_D(const QBbgHistoricalDataResponse);
        for (QMap<QDate, QVariant>::const_iterator i = d->m_values.constBegin(); i != d->m_values.constEnd(); ++i) {
            if (i.value() == a)
                result.append(i.key());
        }
        return result;
    }

    QString QBbgHistoricalDataResponse::periodForDate(const QDate& a) const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return  d->m_relDates.value(a, QString());
    }

    QDate QBbgHistoricalDataResponse::dateForPeriod(const QString& period) const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return d->m_relDates.key(period, QDate());
    }

    QList<QDate> QBbgHistoricalDataResponse::dates() const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return d->m_values.keys();
    }

    QList<QString> QBbgHistoricalDataResponse::periods() const
    {
        Q_D(const QBbgHistoricalDataResponse);
        return d->m_relDates.values();
    }

    QBbgHistoricalDataResponse::QBbgHistoricalDataResponse()
        :QBbgAbstractFieldResponse(new QBbgHistoricalDataResponsePrivate(this))
    {
    }

    QBbgHistoricalDataResponse::QBbgHistoricalDataResponse(QBbgHistoricalDataResponsePrivate* dp)
        : QBbgAbstractFieldResponse(dp)
    {
    }

    QBbgHistoricalDataResponse::QBbgHistoricalDataResponse(const QBbgHistoricalDataResponse& other)
        : QBbgAbstractFieldResponse(new QBbgHistoricalDataResponsePrivate(this, *(other.d_func())))
    {}

    QBbgHistoricalDataResponse& QBbgHistoricalDataResponse::operator=(const QBbgHistoricalDataResponse& other)
    {
        Q_D(QBbgHistoricalDataResponse);
        d->operator=(*(other.d_func()));
        return *this;
    }

    void QBbgHistoricalDataResponse::setValue(const QDate& dt, const QVariant& val, const QString& period /*= QString()*/, const QString& Header /*= QString()*/)
    {
        setHeader(Header);
        if (dt.isNull()) return;
        Q_D(QBbgHistoricalDataResponse);
        d->m_values[dt] = val;
        if (!period.isEmpty()) {
            d->m_relDates[dt] = period;
        }
    }

    void QBbgHistoricalDataResponse::clear()
    {
        Q_D(QBbgHistoricalDataResponse);
        d->m_values.clear();
        d->m_relDates.clear();
        setHeader(QString());
        //TODO is resetting the error code necessary?
        setErrorCode(NoErrors);
    }
    QBbgHistoricalDataResponsePrivate::QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q)
        :QBbgAbstractFieldResponsePrivate(q, QBbgAbstractResponse::ResponseType::HistoricalDataResponse)
    {}

    QBbgHistoricalDataResponsePrivate::QBbgHistoricalDataResponsePrivate(QBbgHistoricalDataResponse* q, const QBbgHistoricalDataResponsePrivate& other)
        : QBbgAbstractFieldResponsePrivate(q, other)
        , m_values(other.m_values)
        , m_relDates(other.m_relDates)
    {}

    QBbgHistoricalDataResponsePrivate& QBbgHistoricalDataResponsePrivate::operator=(const QBbgHistoricalDataResponsePrivate& other)
    {
        QBbgAbstractFieldResponsePrivate::operator=(other);
        m_values = other.m_values;
        m_relDates = other.m_relDates;
        return *this;
    }
}

