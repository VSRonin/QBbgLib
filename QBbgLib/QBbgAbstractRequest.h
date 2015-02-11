#ifndef QBbgAbstractRequest_h__
#define QBbgAbstractRequest_h__
#include <QtGlobal>
namespace QBbgLib {
    class QBbgAbstractRequestPrivate;
    class QBbgSecurity;
    class QBbgAbstractRequest
    {
    protected:
        enum {
            FirstFielded=0x10
            , FirstRealTime = 0x20
        };
    public:
        enum RequestType
        {
            Beqs
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
        virtual qint64 getID() const;
        virtual void setID(qint64 val);
        virtual bool IsValidReq() const =0;
        static QString requestTypeToString(RequestType a);
        static RequestType stringToRequestType(QString a);
    };
}
#endif // QBbgAbstractRequest_h__