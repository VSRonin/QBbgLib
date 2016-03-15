#ifndef QBbgReferenceDataResponse_h__
#define QBbgReferenceDataResponse_h__
#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
#include <QList>
class QVariant;
namespace QBbgLib {
    class QBbgRequestResponseWorker;
    class QBbgReferenceDataResponsePrivate;
    class QBBG_EXPORT QBbgReferenceDataResponse : public QBbgAbstractFieldResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgReferenceDataResponse)
    public:
    	QBbgReferenceDataResponse();
        virtual ~QBbgReferenceDataResponse();
        QBbgReferenceDataResponse(QBbgReferenceDataResponse& other);
        virtual QBbgReferenceDataResponse& operator=(QBbgReferenceDataResponse& other);
        virtual qint32 rows() const;
        virtual qint32 columns() const;
        virtual const QBbgReferenceDataResponse* getTableValue(qint32 r, qint32 c) const;
        virtual bool hasTable() const;
        virtual bool hasValue()const;
        virtual bool isEmpty() const;
        virtual const QVariant& value() const;
    protected:
        QBbgReferenceDataResponse(QBbgReferenceDataResponsePrivate* dp);
        virtual void setValue(const QVariant& val, const QString& Header = QString());
        virtual void addValueRow(const QList<QVariant>& val, const QList<QString>& Headers = QList<QString>());
        virtual void clear();

        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgReferenceDataResponse_h__