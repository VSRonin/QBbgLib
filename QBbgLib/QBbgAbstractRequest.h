#ifndef QBbgAbstractRequest_h__
#define QBbgAbstractRequest_h__
#include <QtGlobal>
#include "QBbgSecurity.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate;
    class QBbgRequestGroup;
    class QBbgAbstractRequest
    {
    protected:
        enum {
            FirstFielded=0x10
            , FirstRealTime = 0x20
        };
        enum { InvalidID = -1024 };
    public:
        enum RequestType
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
    public:
        QBbgAbstractRequest();
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
    };
}
#endif // QBbgAbstractRequest_h__