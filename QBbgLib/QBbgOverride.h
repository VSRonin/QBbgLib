#ifndef QBbgOverride_h__
#define QBbgOverride_h__
#include <QString>
#include <QList>
#include "QBbgProjectGlobals.h"
class QDate;
class QTime;
class QVariant;
namespace BloombergLP { namespace blpapi { class Request; } }
namespace QBbgLib {
    class QBbgOverridePrivate;
    class QBbgRequestResponseWorkerPrivate;
    class QBBG_EXPORT QBbgOverride
    {
        Q_DECLARE_PRIVATE(QBbgOverride)
    public:
        QBbgOverride();
        QBbgOverride(const QBbgOverride& other);
        virtual QBbgOverride& operator=(const QBbgOverride& other);
        virtual ~QBbgOverride();
        virtual void clear();
        virtual qint32 size();
        virtual bool contains(const QString& Name) const;
        virtual bool isEmpty() const;
        virtual void setOverride(const QString& Name, const QVariant& val);
        virtual void setOverride(const QString& Name, const QDate& val);
        virtual void setOverride(const QString& Name, const QTime& val);
        virtual void setOverride(const QString& Name, double val);
        virtual void setOverride(const QString& Name, qint32 val);
        virtual void setOverride(const QString& Name, qint64 val);
        virtual void setOverride(const QString& Name, quint32 val);
        virtual void setOverride(const QString& Name, quint64 val);
        virtual void setOverride(QString Name, const QString& val);
        virtual void setOverride(QString Name, const char* val);
        virtual QString overrideValue(const QString& Name) const;
        virtual QList<QString> getKeys() const;
        virtual bool operator==(const QBbgOverride& other)const;
        virtual bool operator!=(const QBbgOverride& other)const;
        virtual QString& operator[](const QString& Name);
        virtual const QString operator[](const QString& Name) const;
    protected:
        void addOverrideToRequest(BloombergLP::blpapi::Request& rq) const;
        QBbgOverride(QBbgOverridePrivate* d);
        QBbgOverridePrivate* d_ptr;

        friend class QBbgRequestResponseWorkerPrivate;
    };
}
#endif // QBbgOverride_h__