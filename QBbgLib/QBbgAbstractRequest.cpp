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

#include "QBbgAbstractRequest.h"
#include "private/QBbgAbstractRequest_p.h"
#include <QHash>
#include <QDataStream>
namespace QBbgLib {

    QBbgAbstractRequestPrivate::~QBbgAbstractRequestPrivate() = default;

    QBbgAbstractRequest::QBbgAbstractRequest(QBbgAbstractRequestPrivate* d)
        : d_ptr(d)
    {}
    QBbgAbstractRequest::~QBbgAbstractRequest()
    {
        delete d_ptr;
    }
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, QBbgAbstractRequest::RequestType typ)
        : q_ptr(q)
        , m_ID(QBbgAbstractRequest::InvalidID)
        , m_RqType(typ)
    {}
    QBbgAbstractRequestPrivate::QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, const QBbgAbstractRequestPrivate& other)
        : q_ptr(q)
        , m_ID(other.m_ID)
        , m_Security(other.m_Security)
        , m_RqType(other.m_RqType)
    {}
    QBbgAbstractRequestPrivate& QBbgAbstractRequestPrivate::operator=(const QBbgAbstractRequestPrivate& other)
    {
        Q_ASSERT_X(m_RqType == other.m_RqType, "QBbgAbstractRequestPrivate::operator=", "Trying to copy between two diffrent Request types");
        m_ID = other.m_ID;
        m_Security = other.m_Security;
        return *this;
    }
    void QBbgAbstractRequest::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgAbstractRequest);
        stream << d->m_ID << d->m_Security;
    }

    void QBbgAbstractRequest::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgAbstractRequest);
        stream >> d->m_ID >> d->m_Security;
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
        case RequestType::Beqs: 
            return QStringLiteral("BeqsRequest");
        case RequestType::HistoricalData: 
            return QStringLiteral("HistoricalDataRequest");
        case RequestType::ReferenceData: 
            return QStringLiteral("ReferenceDataRequest");
        case RequestType::PortfolioData: 
            return QStringLiteral("PortfolioDataRequest");
        case RequestType::IntraDayTick: 
            return QStringLiteral("IntradayTickRequest");
            //return QStringLiteral("IntraDayTickRequest");  Wrong in documentation
        case RequestType::IntraDayBar:
            return QStringLiteral("IntradayBarRequest");
            //return QStringLiteral("IntraDayBarRequest");  Wrong in documentation
        case RequestType::Invalid:
            return QString();
        default: 
            Q_UNREACHABLE();
            return QString();
        }
    }
    QBbgAbstractRequest::RequestType QBbgAbstractRequest::stringToRequestType(QString a)
    {
        a = a.toLower().trimmed();
        if (a == "beqsrequest") return RequestType::Beqs;
        else if (a == "historicaldatarequest") return RequestType::HistoricalData;
        else if (a == "referencedatarequest") return RequestType::ReferenceData;
        else if (a == "portfoliodatarequest") return RequestType::PortfolioData;
        else if (a == "intradaytickrequest") return RequestType::IntraDayTick;
        else if (a == "intradaybarrequest") return RequestType::IntraDayBar;
        else return RequestType::Invalid;
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

    bool QBbgAbstractRequest::operator==(const QBbgAbstractRequest& other) const
    {
        Q_D(const QBbgAbstractRequest);
        return 
            d->m_RqType == other.d_func()->m_RqType
            && d->m_Security == other.d_func()->m_Security
            ;
    }

    QString QBbgAbstractRequest::serviceStringForRequest(RequestType a)
    {
        return serviceTypeToString(serviceForRequest(a));
    }
    QBbgAbstractRequest::ServiceType QBbgAbstractRequest::serviceForRequest(RequestType a)
    {
        switch (a) {
        case RequestType::ReferenceData:
        case RequestType::PortfolioData:
        case RequestType::HistoricalData:
        case RequestType::IntraDayTick:
        case RequestType::IntraDayBar:
            return ServiceType::refdata;
        default: 
            Q_UNREACHABLE(); //Unhandled service type
            return ServiceType::NoService;
        }
    }
   QString QBbgAbstractRequest::serviceTypeToString(ServiceType a)
   {
       switch (a) {           
       case QBbgLib::QBbgAbstractRequest::ServiceType::refdata:
           return "//blp/refdata";
       case QBbgLib::QBbgAbstractRequest::ServiceType::mktdata:
           return "//blp/mktdata";
       case QBbgLib::QBbgAbstractRequest::ServiceType::mktvwap:
           return "//blp/mktvwap";
       case QBbgLib::QBbgAbstractRequest::ServiceType::mktbar:
           return "//blp/mktbar";
       case QBbgLib::QBbgAbstractRequest::ServiceType::apiflds:
           return "//blp/apiflds";
       case QBbgLib::QBbgAbstractRequest::ServiceType::pagedata:
           return "//blp/pagedata";
       case QBbgLib::QBbgAbstractRequest::ServiceType::tasvc:
           return "//blp/tasvc";
       case QBbgLib::QBbgAbstractRequest::ServiceType::apiauth:
           return "//blp/apiauth";
       default:
           return QString();
       }
   }

   QBbgAbstractRequest::ServiceType QBbgAbstractRequest::stringToServiceType(const QString& a)
   {
       if (a == "//blp/refdata") return ServiceType::refdata;
       else if (a == "//blp/mktdata") return ServiceType::mktdata;
       else if (a == "//blp/mktvwap") return ServiceType::mktvwap;
       else if (a == "//blp/mktbar") return ServiceType::mktbar;
       else if (a == "//blp/apiflds") return ServiceType::apiflds;
       else if (a == "//blp/pagedata") return ServiceType::pagedata;
       else if (a == "//blp/tasvc") return ServiceType::tasvc;
       else if (a == "//blp/apiauth") return ServiceType::apiauth;
       else return ServiceType::NoService;
   }
    

}

uint qHash(QBbgLib::QBbgAbstractRequest::RequestType key, uint seed)
{
    return qHash(static_cast<std::underlying_type<decltype(key)>::type>(key), seed);
}

QDataStream& operator<<(QDataStream& stream, const QBbgLib::QBbgAbstractRequest& obj)
{
    obj.saveToStream(stream);
    return stream;
}

QDataStream& operator>>(QDataStream& stream, QBbgLib::QBbgAbstractRequest& obj)
{
    obj.loadFromStream(stream);
    return stream;
}