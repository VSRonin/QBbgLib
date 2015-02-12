#include "QBbgAbstractRequest.h"
#include "QBbgAbstractRequest_p.h"
namespace QBbgLib {
    QBbgAbstractRequest::QBbgAbstractRequest()
        : d_ptr(new QBbgAbstractRequestPrivate(this))
    {}
    QBbgAbstractRequest::QBbgAbstractRequest(const QBbgAbstractRequest& other)
        : d_ptr(new QBbgAbstractRequestPrivate(this, *(other.d_ptr)))
    {}

    QBbgAbstractRequest::QBbgAbstractRequest(QBbgAbstractRequestPrivate* d)
        : d_ptr(d)
    {}
    QBbgAbstractRequest::~QBbgAbstractRequest()
    {
        delete d_ptr;
    }
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q)
        : q_ptr(q)
        , m_ID(QBbgAbstractRequest::InvalidID)
        , m_RqType(QBbgAbstractRequest::Invalid)
    {}
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, const QBbgAbstractRequestPrivate& other)
        : q_ptr(q)
        , m_ID(other.m_ID)
        , m_Security(other.m_Security)
        , m_RqType(other.m_RqType)
    {}
    QBbgAbstractRequestPrivate& QBbgAbstractRequestPrivate::operator=(const QBbgAbstractRequestPrivate& other)
    {
        m_ID = other.m_ID;
        m_Security = other.m_Security;
        m_RqType = other.m_RqType;
        return *this;
    }
    void QBbgAbstractRequest::setSecurity(const QBbgSecurity& val)
    {
        Q_D(QBbgAbstractRequest);
        d->m_Security = val;
    }
    const QBbgSecurity& QBbgAbstractRequest::security() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_Security;
    }
    QBbgAbstractRequest& QBbgAbstractRequest::operator=(const QBbgAbstractRequest& other)
    {
        Q_D(QBbgAbstractRequest);
        d->operator=(*(other.d_ptr));
        return *this;
    }
    qint64 QBbgAbstractRequest::getID() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_ID;
    }
    void QBbgAbstractRequest::setID(qint64 val)
    {
        Q_D(QBbgAbstractRequest);
        if (val > 0)
            d->m_ID = val;
        else
            d->m_ID = InvalidID;
    }
    QString QBbgAbstractRequest::requestTypeToString(RequestType a)
    {
        switch (a) {
        case Beqs: return "BeqsRequest";
        case HistoricalData: return "HistoricalDataRequest";
        case ReferenceData: return "ReferenceDataRequest";
        case PortfolioData: return "PortfolioDataRequest";
        case IntraDayTick: return "IntraDayTickRequest";
        case IntraDayBar: return "IntraDayBarRequest";
        default: return QString();
        }
    }
    QBbgAbstractRequest::RequestType QBbgAbstractRequest::stringToRequestType(QString a)
    {
        a = a.toLower().trimmed();
        if (a == "beqsrequest") return Beqs;
        else if (a == "historicaldatarequest") return HistoricalData;
        else if (a == "referencedatarequest") return ReferenceData;
        else if (a == "portfoliodatarequest") return PortfolioData;
        else if (a == "intradaytickrequest") return IntraDayTick;
        else if (a == "intradaybarrequest") return IntraDayBar;
        else return Invalid;
    }

    bool QBbgAbstractRequest::isValidReq() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_Security.isValid() && d->m_ID > 0;
    }
    QBbgAbstractRequest::RequestType QBbgAbstractRequest::requestType() const
    {
        Q_D(const QBbgAbstractRequest);
        return d->m_RqType;
    }

}

