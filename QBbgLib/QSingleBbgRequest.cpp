#include "QSingleBbgRequest.h"
#include "QSingleBbgRequest_p.h"
#include <QList> 
#include <QHash>
namespace QBbgLib {
    void QSingleBbgRequest::SetSecurity(const QString& val)
    {
        Q_D(QSingleBbgRequest);
        d->m_Security = val.trimmed().toUpper();
    }
    void QSingleBbgRequest::SetField(const QString& val)
    {
        Q_D(QSingleBbgRequest);
        d->m_Field = val.simplified().toUpper();
        d->m_Field.replace(QChar(' '), QChar('_'));
    }
    QSingleBbgRequestPrivate::QSingleBbgRequestPrivate(QSingleBbgRequest* q)
        : q_ptr(q)
        , m_ResultID(-1)
        , m_Extension(Mtge)
    {}
    QSingleBbgRequestPrivate::QSingleBbgRequestPrivate(QSingleBbgRequest* q, const QSingleBbgRequestPrivate& a)
        : q_ptr(q)
        , m_ResultID(a.m_ResultID)
        , m_Security(a.m_Security)
        , m_Field(a.m_Field)
        , m_Overrides(a.m_Overrides)
        , m_Extension(a.m_Extension)
    {}
    QSingleBbgRequestPrivate& QSingleBbgRequestPrivate::operator=(const QSingleBbgRequestPrivate& a)
    {
        m_ResultID = a.m_ResultID;
        m_Security = a.m_Security;
        m_Field = a.m_Field;
        m_Overrides = a.m_Overrides;
        m_Extension = a.m_Extension;
        return *this;
    }
    void QSingleBbgRequest::SetExtension(const QString& val)
    {
        Q_D(QSingleBbgRequest);
        d->m_Extension = String2YellowKey(val.trimmed());
    }

    void QSingleBbgRequest::SetOverrides(const Overrides& Overr)
    {
        Q_D(QSingleBbgRequest);
        ClearOverrides();
        for (auto i = Overr.constBegin(); i != Overr.constEnd(); i++) {
            if (i.value().isEmpty()) continue;
            if (i.key().isEmpty()) continue;
            QString TempKey = i.key().simplified().toUpper();
            TempKey.replace(QChar(' '), QChar('_'));
            d->m_Overrides.insert(TempKey, i.value().simplified());
        }
    }
    void QSingleBbgRequest::SetOverride(QString Name, const QString& Value)
    {
        Q_D(QSingleBbgRequest);
        Name = Name.simplified().toUpper();
        Name.replace(QChar(' '), QChar('_'));
        d->m_Overrides.insert(Name, Value.simplified());
    }
    void QSingleBbgRequest::ClearOverrides()
    {
        Q_D(QSingleBbgRequest);
        d->m_Overrides.clear();
    }
    bool QSingleBbgRequest::SameOverrides(const QSingleBbgRequest& a)const
    {
        Q_D(const QSingleBbgRequest);
        return d->SameOverrides(*(a.d_ptr));
    }
    bool QSingleBbgRequestPrivate::SameOverrides(const QSingleBbgRequestPrivate& a)const
    {
        return m_Overrides == a.m_Overrides;
    }

    bool QSingleBbgRequest::IsValidReq() const
    {
        Q_D(const QSingleBbgRequest);
        return
            !d->m_Field.isEmpty()
            && !d->m_Security.isEmpty()
            && d->m_Extension != Invalid
            ;
    }

    bool QSingleBbgRequestPrivate::operator==(const QSingleBbgRequestPrivate& a) const
    {
        if (
            (m_Security != a.m_Security)
            || (m_Field != a.m_Field)
            || (m_Extension != a.m_Extension)
            )
            return false;
        return m_Overrides == a.m_Overrides;
    }
    bool QSingleBbgRequest::operator==(const QSingleBbgRequest& a) const
    {
        Q_D(const QSingleBbgRequest);
        return d->operator==(*(a.d_ptr));
    }
    qint64 QSingleBbgRequest::GetResultID() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_ResultID;
    }

    const QString& QSingleBbgRequest::GetSecurity() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Security;
    }

    const QString& QSingleBbgRequest::GetField() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Field;
    }

    void QSingleBbgRequest::SetResultID(qint64 val)
    {
        Q_D(QSingleBbgRequest);
        d->m_ResultID = val;
    }

    const Overrides& QSingleBbgRequest::GetOverrides() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Overrides;
    }

    QString QSingleBbgRequest::GetExtensionString() const
    {
        Q_D(const QSingleBbgRequest);
        return YellowKey2String(d->m_Extension);
    }

    QString QSingleBbgRequest::GetFullSecurity() const
    {
        return GetSecurity() + ' ' + GetExtensionString();
    }

    YellowKeys QSingleBbgRequest::GetExtension() const
    {
        Q_D(const QSingleBbgRequest);
        return d->m_Extension;
    }

    void QSingleBbgRequest::SetExtension(YellowKeys val)
    {
        Q_D(QSingleBbgRequest);
        d->m_Extension = val;
    }

    QBbgLib::QSingleBbgRequest::QSingleBbgRequest()
        :d_ptr(new QSingleBbgRequestPrivate(this))
    {}

    QBbgLib::QSingleBbgRequest::QSingleBbgRequest(const QSingleBbgRequest& a)
        : d_ptr(new QSingleBbgRequestPrivate(this, *(a.d_ptr)))
    {}

    QSingleBbgRequest& QBbgLib::QSingleBbgRequest::operator=(const QSingleBbgRequest& a)
    {
        Q_D(QSingleBbgRequest);
        d->operator=(*(a.d_ptr));
        return *this;
    }

    QBbgLib::QSingleBbgRequest::~QSingleBbgRequest()
    {
        delete d_ptr;
    }
}