#ifndef QBbgAbstractResponse_h__
#define QBbgAbstractResponse_h__
#include "QBbgGenerals.h"
#include <QString>
namespace QBbgLib {
    class QBbgAbstractResponsePrivate;
    class QBbgAbstractResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgAbstractResponse)
        enum BbgErrorCodesF
        {
            NoErrors = 0
            , ResponseError = 0x1
            , SecurityError = 0x2
            , InvalidInputs = 0x4
            , SessionError = 0x8
            , ServiceError = 0x10
            , FieldError = 0x20
            , UnknownError = 0x40
            , SessionStopped = 0x80
            , NoData = 0x100
        };
    protected:
        enum
        {
            FirstFielded = 0x10
            , FirstRealTime = 0x20
        };
    public:
        Q_DECLARE_FLAGS(BbgErrorCodes, BbgErrorCodesF)
        enum ResponseType
        {
            Invalid=-1
            , BeqsResponse
            , HistoricalDataResponse = FirstFielded
            , ReferenceDataResponse
            , PortfolioDataResponse
            , IntraDayTickResponse = FirstRealTime
            , IntraDayBarResponse
        };
    	QBbgAbstractResponse();
        QBbgAbstractResponse(const QBbgAbstractResponse& other);
    	virtual ~QBbgAbstractResponse();
        virtual BbgErrorCodes errorCode() const;
        virtual QString errorString() const;
        virtual bool hasErrors() const;
        virtual bool isEmpty() const =0;
        static QString bbgErrorCode2String(BbgErrorCodes a);
    protected:
        QBbgAbstractResponsePrivate* d_ptr;
        QBbgAbstractResponse(QBbgAbstractResponsePrivate* d);
        virtual void setErrorCode(BbgErrorCodes ErrCd);
    };
}
Q_DECLARE_OPERATORS_FOR_FLAGS(QBbgLib::QBbgAbstractResponse::BbgErrorCodes)
#endif // QBbgAbstractResponse_h__