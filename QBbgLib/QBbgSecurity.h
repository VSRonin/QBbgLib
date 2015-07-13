#ifndef QBbgSecurity_h__
#define QBbgSecurity_h__
#include <QString>
#include <QMetaType>
#include "QBbgProjectGlobals.h"
class QDataStream;
namespace QBbgLib { class QBbgSecurity; }
QBBG_EXPORT QDataStream& operator<<(QDataStream& stream, const QBbgLib::QBbgSecurity& obj);
QBBG_EXPORT QDataStream& operator>>(QDataStream& stream, QBbgLib::QBbgSecurity& obj);
namespace QBbgLib {
    class QBbgSecurityPrivate;
    class QBBG_EXPORT QBbgSecurity
    {
    private:
        enum { FirstPrefix=0x400 };
    public:
        enum YellowKeys
        {
            Invalid = -1
            //Proper yellow keys
            , Govt
            , Corp
            , Mtge
            , MMkt
            , Muni
            , Pfd
            , Equity
            , Comdty
            , Index
            , Curncy
            , Client
            //Prefixes
            //, ticker // still needs another yellow key
            , cusip = FirstPrefix
            , wpk
            , isin
            , buid
            , sedol1
            , sedol2
            , sicovam
            , common
            , bsid
            , svm
            , cins
            , cats
            , bbgid
        };
    private:
        Q_DECLARE_PRIVATE(QBbgSecurity)
        QBbgSecurityPrivate* d_ptr;
    protected:
        virtual void saveToStream(QDataStream& stream) const;
        virtual void loadFromStream(QDataStream& stream);
    public:
    	QBbgSecurity();
        QBbgSecurity(QString SecString);
        QBbgSecurity(const QString& SecName, YellowKeys SecKey);
        QBbgSecurity(const QBbgSecurity& other);
        QBbgSecurity& operator=(const QBbgSecurity& other);
    	virtual ~QBbgSecurity();
        const QString& name() const;
        void setName(const QString& val);
        const QString& exchange() const;
        void setExchange(const QString& val);
        const QString& pricingSource() const;
        void setPricingSource(const QString& val);
        YellowKeys extension() const;
        void setExtension(YellowKeys val);
        bool isValid() const;
        QString fullName() const;
        bool operator==(const QBbgSecurity& other) const;
        bool operator!=(const QBbgSecurity& other) const;
        static QString yellowKeyToString(YellowKeys a);
        static YellowKeys stringToYellowKey(QString a);
        friend QDataStream& ::operator<<(QDataStream& stream, const QBbgSecurity& obj);
        friend QDataStream& ::operator>>(QDataStream& stream, QBbgSecurity& obj);
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgSecurity);

QBBG_EXPORT uint qHash(const QBbgLib::QBbgSecurity&key, uint seed);
#endif // QBbgSecurity_h__
