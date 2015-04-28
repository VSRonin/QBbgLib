#include "QBbgSecurity.h"
#include "private/QBbgSecurity_p.h"
#include <QRegExp>
namespace QBbgLib {
    QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity* q)
        : q_ptr(q)
        , m_Extension(QBbgSecurity::Invalid)
    {}
    QBbgSecurityPrivate::QBbgSecurityPrivate(QBbgSecurity* q, const QBbgSecurityPrivate& other)
        : q_ptr(q)
        , m_Name(other.m_Name)
        , m_Extension(other.m_Extension)
        , m_Exchange(other.m_Exchange)
        , m_PricingSource(other.m_PricingSource)
    {}
    QBbgSecurity::QBbgSecurity()
        :d_ptr(new QBbgSecurityPrivate(this))
    {}
    QBbgSecurity::QBbgSecurity(const QBbgSecurity& other)
        : d_ptr(new QBbgSecurityPrivate(this,*(other.d_ptr)))
    {}
    QBbgSecurity::QBbgSecurity(const QString& SecName, YellowKeys SecKey)
        : d_ptr(new QBbgSecurityPrivate(this))
    {
        setName(SecName);
        setExtension(SecKey);
    }
    QBbgSecurity::QBbgSecurity(QString SecString)
        :d_ptr(new QBbgSecurityPrivate(this))
    {
        SecString = SecString.simplified();
        if (SecString.at(0) == '/') {
            setExtension(stringToYellowKey(SecString.mid(1, SecString.indexOf('/', 1))));
            SecString = SecString.mid(SecString.indexOf('/', 1) + 1);
        }
        else {
            setExtension(stringToYellowKey(SecString.right(SecString.size() - SecString.lastIndexOf(' '))));
            SecString = SecString.left(SecString.lastIndexOf(' '));
        }
        QRegExp priceSourceRegExp("\\S@(\\S)[\\s$]");
        if (priceSourceRegExp.indexIn(SecString) >= 0) {
            setPricingSource(priceSourceRegExp.cap(1));
            SecString.replace(QRegExp("@\\S"), QString());
        }
        setName(SecString);
    }
    QBbgSecurity::~QBbgSecurity()
    {
        delete d_ptr;
    }
    const QString& QBbgSecurity::name() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Name;
    }
    void QBbgSecurity::setName(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_Name = val;
    }
    const QString& QBbgSecurity::exchange() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Exchange;
    }
    void QBbgSecurity::setExchange(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_Exchange = val;
    }
    const QString& QBbgSecurity::pricingSource() const
    {
        Q_D(const QBbgSecurity);
        return d->m_PricingSource;
    }
    void QBbgSecurity::setPricingSource(const QString& val)
    {
        Q_D(QBbgSecurity);
        d->m_PricingSource = val;
    }
    QBbgSecurity::YellowKeys QBbgSecurity::extension() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Extension;
    }
    void QBbgSecurity::setExtension(YellowKeys val)
    {
        Q_D(QBbgSecurity);
        d->m_Extension = val;
    }
    bool QBbgSecurity::isValid() const
    {
        Q_D(const QBbgSecurity);
        return d->m_Extension != Invalid && !(d->m_Name.isEmpty());
    }
    QString QBbgSecurity::yellowKeyToString(QBbgSecurity::YellowKeys a)
    {
        switch (a) {
        case Govt: return "Govt";
        case Corp: return "Corp";
        case Mtge: return "Mtge";
        case MMkt: return "MMkt";
        case Muni: return "Muni";
        case Pfd: return "Pfd";
        case Equity: return "Equity";
        case Comdty: return "Comdty";
        case Index: return "Index";
        case Curncy: return "Curncy";
        case Client: return "Client";
        //case ticker: return "ticker";
        case cusip: return "cusip";
        case wpk: return "wpk";
        case isin: return "isin";
        case buid: return "buid";
        case sedol1: return "sedol1";
        case sedol2: return "sedol2";
        case sicovam: return "sicovam";
        case common: return "common";
        case bsid: return "bsid";
        case svm: return "svm";
        case cins: return "cins";
        case cats: return "cats";
        case bbgid: return "bbgid";
        default: return QString();
        }
    }
    QBbgSecurity::YellowKeys QBbgSecurity::stringToYellowKey(QString a)
    {
        a = a.toLower().trimmed();
        if (a == "govt") return Govt;
        else if (a == "corp") return Corp;
        else if (a == "mtge") return Mtge;
        else if (a == "mmkt") return MMkt;
        else if (a == "muni") return Muni;
        else if (a == "pfd") return Pfd;
        else if (a == "equity") return Equity;
        else if (a == "comdty") return Comdty;
        else if (a == "index") return Index;
        else if (a == "curncy") return Curncy;
        else if (a == "client") return Client;
        //else if (a == "ticker") return ticker;
        else if (a == "cusip") return cusip;
        else if (a == "wpk") return wpk;
        else if (a == "isin") return isin;
        else if (a == "buid") return buid;
        else if (a == "sedol1") return sedol1;
        else if (a == "sedol2") return sedol2;
        else if (a == "sicovam") return sicovam;
        else if (a == "common") return common;
        else if (a == "bsid") return bsid;
        else if (a == "svm") return svm;
        else if (a == "cins") return cins;
        else if (a == "cats") return cats;
        else if (a == "bbgid") return bbgid;
        else return Invalid;
    }

    QString QBbgSecurity::fullName() const
    {
        QString Result;
        if (!isValid())
            return Result;
        Q_D(const QBbgSecurity);
        if (d->m_Extension & FirstPrefix)
            Result += '/' + yellowKeyToString(d->m_Extension) + '/';
        Result += d->m_Name;
        if (!(d->m_PricingSource.isEmpty()))
            Result += '@' + d->m_PricingSource;
        if (!(d->m_Extension & FirstPrefix)) {
            Result += ' ';
            if (!(d->m_Exchange.isEmpty()))
                Result += d->m_Exchange + ' ';
            Result += yellowKeyToString(d->m_Extension);
        }
        return Result;
    }

    bool QBbgSecurity::operator!=(const QBbgSecurity& other) const
    {
        return !operator==(other);
    }

    bool QBbgSecurity::operator==(const QBbgSecurity& other) const
    {
        Q_D(const QBbgSecurity);
        return d->operator==(*(other.d_func()));
    }

    QBbgSecurity& QBbgSecurity::operator=(const QBbgSecurity& other)
    {
        Q_D(QBbgSecurity);
        d->operator=(*(other.d_func()));
        return *this;
    }

    bool QBbgSecurityPrivate::operator==(const QBbgSecurityPrivate& other) const
    {
        return
            m_Name == other.m_Name
            && m_Extension == other.m_Extension
            && m_Exchange == other.m_Exchange
            && m_PricingSource == other.m_PricingSource
            ;
    }
    QBbgSecurityPrivate& QBbgSecurityPrivate::operator=(const QBbgSecurityPrivate& other)
    {
        m_Name = other.m_Name;
        m_Extension = other.m_Extension;
        m_Exchange = other.m_Exchange;
        m_PricingSource = other.m_PricingSource;
        return *this;
    }
}
