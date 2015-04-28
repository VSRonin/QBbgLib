#include "QBbgAbstractRequest.h"
#include "private/QBbgAbstractRequest_p.h"
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
    void QBbgAbstractRequest::setSecurity(const QString& SecName, QBbgSecurity::YellowKeys SecKey)
    {
        setSecurity(QBbgSecurity(SecName, SecKey));
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
    QString QBbgAbstractRequest::serviceStringForRequest(RequestType a)
    {
        return serviceTypeToString(serviceForRequest(a));
    }
    QBbgAbstractRequest::ServiceType QBbgAbstractRequest::serviceForRequest(RequestType a)
    {
        switch (a) {
        case ReferenceData: 
        case PortfolioData:
        case HistoricalData:
            return refdata;
        default: 
            Q_UNREACHABLE(); //Unhandled service type
            return NoService;
        }
    }
   QString QBbgAbstractRequest::serviceTypeToString(ServiceType a)
   {
       switch (a) {           
       case QBbgLib::QBbgAbstractRequest::refdata:
           return "//blp/refdata";
       case QBbgLib::QBbgAbstractRequest::mktdata:
           return "//blp/mktdata";
       case QBbgLib::QBbgAbstractRequest::mktvwap:
           return "//blp/mktvwap";
       case QBbgLib::QBbgAbstractRequest::mktbar:
           return "//blp/mktbar";
       case QBbgLib::QBbgAbstractRequest::apiflds:
           return "//blp/apiflds";
       case QBbgLib::QBbgAbstractRequest::pagedata:
           return "//blp/pagedata";
       case QBbgLib::QBbgAbstractRequest::tasvc:
           return "//blp/tasvc";
       case QBbgLib::QBbgAbstractRequest::apiauth:
           return "//blp/apiauth";
       default:
           return QString();
       }
   }

   QBbgAbstractRequest::ServiceType QBbgAbstractRequest::stringToServiceType(const QString& a)
   {
       if (a == "//blp/refdata") return refdata;
       else if (a == "//blp/mktdata") return mktdata;
       else if (a == "//blp/mktvwap") return mktvwap;
       else if (a == "//blp/mktbar") return mktbar;
       else if (a == "//blp/apiflds") return apiflds;
       else if (a == "//blp/pagedata") return pagedata;
       else if (a == "//blp/tasvc") return tasvc;
       else if (a == "//blp/apiauth") return apiauth;
       else return NoService;
   }
    

}

