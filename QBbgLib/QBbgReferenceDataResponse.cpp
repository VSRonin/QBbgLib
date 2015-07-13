#include "QBbgReferenceDataResponse.h"
#include "private/QBbgReferenceDataResponse_p.h"
namespace QBbgLib {
    bool QBbgReferenceDataResponse::hasValue() const
    {
        Q_D(const QBbgReferenceDataResponse);
        return !d->m_Value.isNull();
    }
    bool QBbgReferenceDataResponse::hasTable() const
    {
        Q_D(const QBbgReferenceDataResponse);
        return !(d->m_TableResultRows.isEmpty() || d->m_TableCols==0);
    }
    bool QBbgReferenceDataResponse::isEmpty() const
    {
        return !(hasTable() || hasValue());
    }
    qint32 QBbgReferenceDataResponse::rows() const
    {
        Q_D(const QBbgReferenceDataResponse);
        return d->m_TableResultRows.size();
    }
    qint32 QBbgReferenceDataResponse::columns() const
    {
        Q_D(const QBbgReferenceDataResponse);
        return d->m_TableCols;
    }
    const QBbgReferenceDataResponse* QBbgReferenceDataResponse::getTableValue(qint32 r, qint32 c) const
    {
        if (r < 0 || r >= rows() || c<0 || c>columns())
            return NULL;
        Q_D(const QBbgReferenceDataResponse);
        return d->m_TableResultRows.at(r) + c;
    }
    const QVariant& QBbgReferenceDataResponse::value() const
    {
        Q_D(const QBbgReferenceDataResponse);
        return d->m_Value;
    }
    void QBbgReferenceDataResponse::setValue(const QVariant& val, const QString& Header /*= QString()*/)
    {
        Q_D(QBbgReferenceDataResponse);
        if (hasTable())
            clear();
        d->m_Value=val;
        setHeader(Header);
    }
    void QBbgReferenceDataResponse::addValueRow(const QList<QVariant>& val, const QList<QString>& Headers /*= QList<QString>()*/)
    {
        Q_D(QBbgReferenceDataResponse);
        if (val.isEmpty()) return;
        bool GoodHead = Headers.size() == val.size();
        if (d->m_TableResultRows.isEmpty()) {
            clear();
            d->m_TableCols = val.size();
        }
        else if (d->m_TableCols != val.size()) {
            Q_UNREACHABLE(); //Columns of new row are different from columns of current table
            return;
        }
        QBbgReferenceDataResponse* newRow = new QBbgReferenceDataResponse[d->m_TableCols];
        for (qint32 i = 0; i < d->m_TableCols; ++i)
            newRow[i].setValue(val.at(i), GoodHead ? Headers.at(i) : QString());
        d->m_TableResultRows.append(newRow);
    }
    void QBbgReferenceDataResponse::clear()
    {
        Q_D(QBbgReferenceDataResponse);
        d->m_Value.clear();
        while (!d->m_TableResultRows.isEmpty()) {
            delete [] d->m_TableResultRows.takeFirst();
        }
        setHeader(QString());
        //TODO is resetting the error code necessary?
        setErrorCode(NoErrors);
    }

    QBbgReferenceDataResponse::~QBbgReferenceDataResponse()
    {
        clear();
    }
    QBbgReferenceDataResponse::QBbgReferenceDataResponse()
        :QBbgAbstractFieldResponse(new QBbgReferenceDataResponsePrivate(this))
    {
        Q_D(QBbgReferenceDataResponse);
        d->m_ResType = ReferenceDataResponse;
    }
    QBbgReferenceDataResponse::QBbgReferenceDataResponse(QBbgReferenceDataResponsePrivate* dp)
        : QBbgAbstractFieldResponse(dp)
    {
        Q_D(QBbgReferenceDataResponse);
        d->m_ResType = ReferenceDataResponse;
    }
    QBbgReferenceDataResponse::QBbgReferenceDataResponse(QBbgReferenceDataResponse& other)
        : QBbgAbstractFieldResponse(new QBbgReferenceDataResponsePrivate(this,*(other.d_func())))
    {}
    QBbgReferenceDataResponse& QBbgReferenceDataResponse::operator=(QBbgReferenceDataResponse& other)
    {
        Q_D(QBbgReferenceDataResponse);
        d->operator=(*(other.d_func()));
        return *this;
    }
    QBbgReferenceDataResponsePrivate::QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q)
        :QBbgAbstractFieldResponsePrivate(q)
        , m_TableCols(0)
    {}
    QBbgReferenceDataResponsePrivate::QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q, const QBbgReferenceDataResponsePrivate& other)
        : QBbgAbstractFieldResponsePrivate(q, other)
        , m_TableCols(other.m_TableCols)
        , m_Value(other.m_Value)
    {
        QBbgReferenceDataResponse* newRow = NULL;
        for (QList<QBbgReferenceDataResponse*>::const_iterator i = other.m_TableResultRows.constBegin(); i != other.m_TableResultRows.constEnd(); ++i) {
            newRow = new QBbgReferenceDataResponse[m_TableCols];
            for (qint32 j = 0; j < m_TableCols; ++j) {
                newRow[j] = (*i)[j];
            }
            m_TableResultRows.append(newRow);
        }
    }
    QBbgReferenceDataResponsePrivate& QBbgReferenceDataResponsePrivate::operator=(const QBbgReferenceDataResponsePrivate& other)
    {
        QBbgAbstractFieldResponsePrivate::operator=(other);
        m_TableCols = other.m_TableCols;
        m_Value=other.m_Value;
        QBbgReferenceDataResponse* newRow = NULL;
        for (QList<QBbgReferenceDataResponse*>::const_iterator i = other.m_TableResultRows.constBegin(); i != other.m_TableResultRows.constEnd(); ++i) {
            newRow = new QBbgReferenceDataResponse[m_TableCols];
            for (qint32 j = 0; j < m_TableCols; ++j) {
                newRow[j] = (*i)[j];
            }
            m_TableResultRows.append(newRow);
        }
        return *this;
    }
}
