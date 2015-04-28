#include "QBbgHistoricalDataResponse.h"
#include "private/QBbgHistoricalDataResponse_p.h"
namespace QBbgLib {
    qint32 QBbgHistoricalDataResponse::size() const
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
        return  *(d->m_values.begin() + period);
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
        Q_D(QBbgHistoricalDataResponse);
        d->m_ResType = HistoricalDataResponse;
    }

    QBbgHistoricalDataResponse::QBbgHistoricalDataResponse(QBbgHistoricalDataResponsePrivate* dp)
        : QBbgAbstractFieldResponse(dp)
    {
        Q_D(QBbgHistoricalDataResponse);
        d->m_ResType = HistoricalDataResponse;
    }

    QBbgHistoricalDataResponse::QBbgHistoricalDataResponse(QBbgHistoricalDataResponse& other)
        : QBbgAbstractFieldResponse(new QBbgHistoricalDataResponsePrivate(this, *(other.d_func())))
    {}

    QBbgHistoricalDataResponse& QBbgHistoricalDataResponse::operator=(QBbgHistoricalDataResponse& other)
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
        :QBbgAbstractFieldResponsePrivate(q)
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

