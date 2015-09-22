#ifndef QBbgAbstractRequest_h__
#define QBbgAbstractRequest_h__
#include <QtGlobal>
#include "QBbgSecurity.h"
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate;
    class QBbgRequestGroup;
    class QBbgRequestResponseWorkerPrivate;
    class QBbgRequestResponseWorker;
    class QBBG_EXPORT QBbgAbstractRequest
    {
    protected:
        enum : qint32
        {
            FirstFielded=0x10
            , FirstRealTime = 0x20
        };
        enum { InvalidID = -1024 };
        enum class ServiceType
        {
            NoService=0
            , refdata=1
            , mktdata
            , mktvwap
            , mktbar
            , apiflds
            , pagedata
            , tasvc
            , apiauth
        };
    public:
        enum class RequestType : qint32
        {
            Invalid =-1
            , Beqs
            , HistoricalData = FirstFielded
            , ReferenceData
            , PortfolioData
            , IntraDayTick = FirstRealTime
            , IntraDayBar
        };
    protected:
        Q_DECLARE_PRIVATE(QBbgAbstractRequest)
        QBbgAbstractRequestPrivate* d_ptr;
        QBbgAbstractRequest(QBbgAbstractRequestPrivate* d);
        static ServiceType serviceForRequest(RequestType a);
        static QString serviceStringForRequest(RequestType a);
        static QString serviceTypeToString(ServiceType a);
        static ServiceType stringToServiceType(const QString& a);
    public:
        QBbgAbstractRequest(RequestType typ/*=QBbgAbstractRequest::Invalid*/);
        QBbgAbstractRequest(const QBbgAbstractRequest& other);
        virtual ~QBbgAbstractRequest();
        virtual QBbgAbstractRequest& operator=(const QBbgAbstractRequest& other);
        virtual const QBbgSecurity& security() const;
        virtual void setSecurity(const QBbgSecurity& val);
        virtual void setSecurity(const QString& SecName, QBbgSecurity::YellowKeys SecKey);
        virtual qint64 getID() const;
        virtual void setID(qint64 val);
        virtual bool isValidReq() const;
        virtual RequestType requestType() const;
        static QString requestTypeToString(RequestType a);
        static RequestType stringToRequestType(QString a);
        friend class QBbgRequestGroup;
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestResponseWorkerPrivate;
        friend class QBbgRequestResponseWorker;
    };
}
QBBG_EXPORT uint qHash(QBbgLib::QBbgAbstractRequest::RequestType key, uint seed = 0);
#endif // QBbgAbstractRequest_h__