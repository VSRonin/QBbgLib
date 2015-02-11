#include "QSingleBbgResult.h"
#include "QSingleBbgResult_p.h"
namespace QBbgLib {
    QSingleBbgResultPrivate::QSingleBbgResultPrivate(QSingleBbgResult* q)
        : q_ptr(q)
        , m_ErrorCode(NoErrors)
        , TableResultCols(0)
        , m_StringValue(NULL)
        , m_DateValue(NULL)
        , m_DoubleValue(NULL)
    {}
    QSingleBbgResultPrivate::QSingleBbgResultPrivate(QSingleBbgResult* q, const QSingleBbgResultPrivate& a)
        : TableResultCols(0)
    {
        operator=(a);
    }
    QSingleBbgResult::QSingleBbgResult()
        : d_ptr(new QSingleBbgResultPrivate(this))
    {}
    QSingleBbgResult::QSingleBbgResult(const QSingleBbgResult& a)
        : d_ptr(new QSingleBbgResultPrivate(this, *(a.d_ptr)))
    {}
    qint32 QSingleBbgResult::GetErrorCode() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_ErrorCode;
    }
    bool QSingleBbgResult::HasErrors() const
    {
        return GetErrorCode() != NoErrors;
    }
    void QSingleBbgResult::SetErrorCode(BbgErrorCodes val)
    {
        Q_D(QSingleBbgResult);
        if (val == NoErrors)  d->m_ErrorCode = NoErrors;
        else  d->m_ErrorCode = d->m_ErrorCode | val;
    }

    QString QSingleBbgResult::GetErrorString() const
    {
        Q_D(const QSingleBbgResult);
        return BbgErrorCodes2String(d->m_ErrorCode);
    }
    QSingleBbgResultPrivate& QSingleBbgResultPrivate::operator= (const QSingleBbgResultPrivate& a)
    {
        Clear();
        m_ErrorCode = a.m_ErrorCode;
        m_Header = a.m_Header;
        if (a.m_StringValue) m_StringValue = new QString(*(a.m_StringValue));
        if (a.m_DateValue) m_DateValue = new QDate(*(a.m_DateValue));
        if (a.m_DoubleValue) m_DoubleValue = new double(*(a.m_DoubleValue));
        if (a.HasTable()) {
            TableResultCols = a.TableResultCols;
            for (QList<QSingleBbgResult*>::const_iterator i = m_TableResultRows.constBegin(); i != m_TableResultRows.constEnd(); i++) {
                QSingleBbgResult* TableRow = new QSingleBbgResult[TableResultCols];
                for (quint32 j = 0; j < TableResultCols; j++) {
                    TableRow[j] = (*i)[j];
                }
                m_TableResultRows.append(TableRow);
            }
        }
        else {
            TableResultCols = 0;
        }
        return *this;
    }
    QSingleBbgResultPrivate::~QSingleBbgResultPrivate()
    {
        Clear();
    }
    QSingleBbgResult::~QSingleBbgResult()
    {
        delete d_ptr;
    }

    void QSingleBbgResultPrivate::Clear()
    {
        if (m_StringValue) delete m_StringValue;
        if (m_DateValue)delete m_DateValue;
        if (m_DoubleValue)delete m_DoubleValue;
        while (!m_TableResultRows.isEmpty()) {
            delete[] m_TableResultRows.takeFirst();
        }
        m_StringValue = NULL;
        m_DateValue = NULL;
        m_DoubleValue = NULL;
        TableResultCols = 0;
        m_Header.clear();
        m_ErrorCode = NoErrors;
    }
    void QSingleBbgResult::SetValue(const QString& val, const QString& Header)
    {
        Q_D(QSingleBbgResult);
        d->SetValue(val, Header);
    }
    void QSingleBbgResultPrivate::SetValue(const QString& val, const QString& Header)
    {
        if (val.isEmpty()) return;
        Clear();
        m_Header = Header;
        m_StringValue = new QString(val);
        QDate TempDate = QDate::fromString(val, "yyyy-MM-dd");
        if (!TempDate.isNull()) {
            m_DateValue = new QDate(TempDate);
        }
        bool DoubleCheck = false;
        double TempDouble = val.toDouble(&DoubleCheck);
        if (DoubleCheck) {
            m_DoubleValue = new double(TempDouble);
        }
    }
    void QSingleBbgResult::AddValueRow(const QList<QString>&  val, const QList<QString>&  Headers)
    {
        Q_D(QSingleBbgResult);
        d->AddValueRow(val, Headers);
    }
    void QSingleBbgResultPrivate::AddValueRow(const QList<QString>&  val, const QList<QString>&  Headers)
    {
        if (val.isEmpty()) return;
        bool GoodHead = Headers.size() == val.size();
        if (m_TableResultRows.empty()) {
            Clear();
            TableResultCols = val.size();
        }
        else {
            if (TableResultCols != val.size()) return;
        }
        QSingleBbgResult* TableRow = new QSingleBbgResult[TableResultCols];
        for (quint32 i = 0; i < TableResultCols; i++) {
            TableRow[i].SetValue(val.at(i), GoodHead ? Headers.at(i) : "");
        }
        m_TableResultRows.append(TableRow);
    }

    const QSingleBbgResult* QSingleBbgResult::GetTableResult(quint32 r, quint32 c) const
    {
        Q_D(const QSingleBbgResult);
        if (r >= d->m_TableResultRows.size() || c >= d->TableResultCols)
            return nullptr;
        QSingleBbgResult* const & TempRow = d->m_TableResultRows.at(r);
        return TempRow + c;
    }

    qint32 QSingleBbgResult::GetNumCols() const
    {
        Q_D(const QSingleBbgResult);
        return d->TableResultCols;
    }

    qint32 QSingleBbgResult::GetNumRows() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_TableResultRows.size();
    }

    double QSingleBbgResult::GetDouble() const
    {
        Q_D(const QSingleBbgResult);
        if (d->m_DoubleValue)
            return *(d->m_DoubleValue);
        return 0.0;
    }

    QDate QSingleBbgResult::GetDate() const
    {
        Q_D(const QSingleBbgResult);
        if (d->m_DateValue)
            return *(d->m_DateValue);
        return QDate();
    }

    QString QSingleBbgResult::GetString() const
    {
        Q_D(const QSingleBbgResult);
        if (d->m_StringValue)
            return *(d->m_StringValue);
        return QString();
    }

    const QString& QSingleBbgResult::GetHeader() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_Header;
    }

    bool QSingleBbgResult::HasValue() const
    {
        return HasString();
    }
    bool QSingleBbgResult::HasTable() const
    {
        Q_D(const QSingleBbgResult);
        return d->HasTable();
    }
    bool QSingleBbgResultPrivate::HasTable() const
    {
        return (!m_TableResultRows.empty()) && TableResultCols > 0;
    }

    bool QSingleBbgResult::HasDouble() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_DoubleValue != NULL;
    }

    bool QSingleBbgResult::HasDate() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_DateValue != NULL;
    }

    bool QSingleBbgResult::HasString() const
    {
        Q_D(const QSingleBbgResult);
        return d->m_StringValue != NULL;
    }

    bool QSingleBbgResult::IsEmpty() const
    {
        return !HasString() && !HasTable();
    }

    QSingleBbgResult& QSingleBbgResult::operator=(const QSingleBbgResult& a)
    {
        Q_D(QSingleBbgResult);
        d->operator=(*(a.d_ptr));
        return *this;
    }

    void QSingleBbgResult::SetHeader(const QString& Header)
    {
        Q_D(QSingleBbgResult);
        d->m_Header = Header;
    }

}
