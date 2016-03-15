#include "private/QBbgAbstractWorker_p.h"
#include <blpapi_session.h>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <blpapi_session.h>
namespace QBbgLib {
    QBbgAbstractWorker::~QBbgAbstractWorker()
    {
        if (m_SessionRunning)
            m_session->stop();
    }
    QBbgAbstractWorker::QBbgAbstractWorker(const BloombergLP::blpapi::SessionOptions& option, QObject* parent)
        : m_session(new BloombergLP::blpapi::Session(option))
        , m_SessionRunning(false)
        , QObject(parent)
    {}
    bool QBbgAbstractWorker::isAvailable() const
    {
        return !m_SessionRunning;
    }
    void QBbgAbstractWorker::stop()
    {
        if (m_SessionRunning)
            m_session->stopAsync();
    }

    bool QBbgAbstractWorker::sessionRunning() const
    {
        return m_SessionRunning;
    }

    void QBbgAbstractWorker::setSessionRunning(bool val)
    {
        m_SessionRunning = val;
    }

    void QBbgAbstractWorker::setResponseError(QBbgAbstractResponse* res, QBbgAbstractResponse::BbgErrorCodes err, const QString& errMsg) const
    {
        res->setErrorCode(err,errMsg);
    }
    void QBbgAbstractWorker::setResponseID(QBbgAbstractResponse* res, qint64 corrID) const
    {
        res->setID(corrID);
    }
    QVariant QBbgAbstractWorker::elementToVariant(BloombergLP::blpapi::Element& val)
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
            return double(val.getValueAsFloat32());
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
            Q_UNREACHABLE(); //Unhandled element type
            return QVariant();
        }
    }

    QScopedPointer<BloombergLP::blpapi::Session>& QBbgAbstractWorker::session()
    {
        return m_session;
    }

}
