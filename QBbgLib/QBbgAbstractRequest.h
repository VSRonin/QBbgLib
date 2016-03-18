#ifndef QBbgAbstractRequest_h__
#define QBbgAbstractRequest_h__
#include <QObject>
#include "QBbgSecurity.h"
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate;
    class QBbgRequestGroup;
    class QBbgRequestResponseWorker;
    class QBBG_EXPORT QBbgAbstractRequest
    {
        Q_GADGET
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        Q_PROPERTY(qint64 securityID READ getID WRITE setID)
        Q_PROPERTY(bool isValidReq READ isValidReq)
        Q_PROPERTY(RequestType requestType READ requestType)
    protected:
        enum : qint32
        {
            FirstFielded=0x10
            , FirstRealTime = 0x20
        };
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
        enum SpecialIDs { 
            InvalidID = -1024 
        };
        Q_ENUM(SpecialIDs)
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
        Q_ENUM(RequestType)
    protected:
        Q_DECLARE_PRIVATE(QBbgAbstractRequest)
        QBbgAbstractRequestPrivate* d_ptr;
        QBbgAbstractRequest(QBbgAbstractRequestPrivate* d);
        static ServiceType serviceForRequest(RequestType a);
        static QString serviceStringForRequest(RequestType a);
        static QString serviceTypeToString(ServiceType a);
        static ServiceType stringToServiceType(const QString& a);
    public:
        //! Destructor
        virtual ~QBbgAbstractRequest() =0;
        //! Creates a request of type typ
        QBbgAbstractRequest(RequestType typ);
        //! Creates a copy of another request
        QBbgAbstractRequest(const QBbgAbstractRequest& other);
        //! Copies another request
        virtual QBbgAbstractRequest& operator=(const QBbgAbstractRequest& other);
        //! Returns the security associated with the request
        virtual const QBbgSecurity& security() const;
        //! Sets the security for the current request to the specified one
        virtual void setSecurity(const QBbgSecurity& val);
        /*!
        \brief Overloaded from setSecurity
        \arg SecName Name of the security to add
        \arg SecKey Yellow key or code identifier for the security
        \details Sets the security for the current request to the specified one
        */
        virtual void setSecurity(const QString& SecName, QBbgSecurity::YellowKeys SecKey);
        /*!
        \brief Returns the current ID for the request
        \details 
        */
        virtual qint64 getID() const;
        virtual void setID(qint64 val);
        virtual bool isValidReq() const;
        virtual RequestType requestType() const;
        Q_INVOKABLE static QString requestTypeToString(RequestType a);
        Q_INVOKABLE static RequestType stringToRequestType(QString a);
        friend class QBbgRequestGroup;
        friend class QBbgRequestGroupPrivate;
        friend class QBbgRequestResponseWorkerPrivate;
        friend class QBbgRequestResponseWorker;
    };
}
/*!
\brief Allows QBbgAbstractRequest::RequestType to be used as a key of a QHash
\relates QBbgLib::QBbgAbstractRequest
*/
QBBG_EXPORT uint qHash(QBbgLib::QBbgAbstractRequest::RequestType key, uint seed = 0);
#endif // QBbgAbstractRequest_h__