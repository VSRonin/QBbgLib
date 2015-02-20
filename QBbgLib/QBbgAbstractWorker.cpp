#include "QBbgAbstractWorker.h"
#include "QBbgAbstractWorker_p.h"
#include <blpapi_session.h>
#include <QDate>
#include <QTime>
#include <QDateTime>
namespace QBbgLib {
    QBbgAbstractWorkerPrivate::QBbgAbstractWorkerPrivate(QBbgAbstractWorker* q, const BloombergLP::blpapi::SessionOptions& option)
        :q_ptr(q)
        , m_session(new BloombergLP::blpapi::Session(option,this))
        , m_SessionRunning(false)
    {}
    QBbgAbstractWorkerPrivate::~QBbgAbstractWorkerPrivate()
    {
        if (m_SessionRunning)
            m_session->stop();
    }
    QBbgAbstractWorker::QBbgAbstractWorker(QBbgAbstractWorkerPrivate* d, QObject* parent)
        : d_ptr(d)
        , QObject(parent)
    {}
    QBbgAbstractWorker::~QBbgAbstractWorker()
    {
        delete d_ptr;
    }

    bool QBbgAbstractWorker::isAvailable() const
    {
        Q_D(const QBbgAbstractWorker);
        return !d->m_SessionRunning;
    }
    void QBbgAbstractWorker::stop()
    {
        Q_D(QBbgAbstractWorker);
        if (d->m_SessionRunning)
            d->m_session->stopAsync();
    }
    void QBbgAbstractWorkerPrivate::setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err, const QString& errMsg) const
    {
        res->setErrorCode(err,errMsg);
    }
    void QBbgAbstractWorkerPrivate::setResponseID(QBbgAbstractResponse* res, qint64 corrID) const
    {
        res->setID(corrID);
    }
    QVariant QBbgAbstractWorkerPrivate::elementToVariant(BloombergLP::blpapi::Element& val)
    {
        if (val.isNull()) return QVariant();
        //if (val.isNullValue()) return QVariant();
        switch (val.datatype()) {
        case BloombergLP::blpapi::DataType::BOOL:
            return val.getValueAsBool();
        case BloombergLP::blpapi::DataType::CHAR:
            return val.getValueAsChar();
        case BloombergLP::blpapi::DataType::INT32:
            return qint32(val.getValueAsInt32());
        case BloombergLP::blpapi::DataType::INT64:
            return qint64(val.getValueAsInt64());
        case BloombergLP::blpapi::DataType::FLOAT32:
            return float(val.getValueAsFloat32());
        case BloombergLP::blpapi::DataType::FLOAT64:
            return double(val.getValueAsFloat64());
        case BloombergLP::blpapi::DataType::STRING:
            return QString(val.getValueAsString());
        case BloombergLP::blpapi::DataType::DATE:
            return QDate(
                val.getValueAsDatetime().year()
                , val.getValueAsDatetime().month()
                , val.getValueAsDatetime().day()
                );
        case BloombergLP::blpapi::DataType::TIME:
            return QTime(
                val.getValueAsDatetime().hours()
                , val.getValueAsDatetime().minutes()
                , val.getValueAsDatetime().seconds()
                , val.getValueAsDatetime().milliSeconds()
                );
        case BloombergLP::blpapi::DataType::DATETIME:
            return QDateTime(
                QDate(
                val.getValueAsDatetime().year()
                , val.getValueAsDatetime().month()
                , val.getValueAsDatetime().day()
                )
                , QTime(
                val.getValueAsDatetime().hours()
                , val.getValueAsDatetime().minutes()
                , val.getValueAsDatetime().seconds()
                , val.getValueAsDatetime().milliSeconds()
                )
                );
        default:
            Q_ASSERT_X(false, "QBbgAbstractWorkerPrivate::elementToVariant", "Unhandled element type");
            return QVariant();
        }
    }
}