#ifndef QBbgHistoricalDataResponse_h__
#define QBbgHistoricalDataResponse_h__
#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
#include <QDate>
#include <QList>
class QVariant;
namespace QBbgLib {
    class QBbgRequestResponseWorkerPrivate;
    class QBbgHistoricalDataResponsePrivate;
    class QBBG_EXPORT QBbgHistoricalDataResponse : public QBbgAbstractFieldResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgHistoricalDataResponse)
    public:
        virtual ~QBbgHistoricalDataResponse();
        QBbgHistoricalDataResponse();
        QBbgHistoricalDataResponse(QBbgHistoricalDataResponse& other);
        virtual QBbgHistoricalDataResponse& operator=(QBbgHistoricalDataResponse& other);
        virtual qint32 size() const;
        virtual bool isEmpty() const;
        virtual QVariant value(const QDate& a) const;
        virtual QVariant value(const QString& period) const;
        virtual QVariant value(int period) const;
        virtual QList<QDate> findValues(const QVariant& a) const;
        virtual QString periodForDate(const QDate& a)const;
        virtual QDate dateForPeriod(const QString& period)const;
        virtual QList<QDate> dates() const;
        virtual QList<QString> periods() const;
    protected:
        QBbgHistoricalDataResponse(QBbgHistoricalDataResponsePrivate* dp);
        virtual void setValue(const QDate& dt, const QVariant& val, const QString& period = QString(), const QString& Header = QString());
        virtual void clear();
        friend class QBbgRequestResponseWorkerPrivate;
    };
}
#endif // QBbgHistoricalDataResponse_h__