#ifndef QBbgGenerals_h__
#define QBbgGenerals_h__

#include <QHash>
#include <QString>
#include "QBbgProjectGlobals.h"
namespace QBbgLib {
    enum YellowKeysF
    {
        Invalid = -1
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
    };
    Q_DECLARE_FLAGS(YellowKeys, YellowKeysF)
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
    Q_DECLARE_FLAGS(BbgErrorCodes, BbgErrorCodesF)

    typedef QHash<QString, QString> Overrides;
    QBBG_EXTERN QBBG_EXPORT QString BbgErrorCodes2String(BbgErrorCodes a);
    QBBG_EXTERN QBBG_EXPORT QString YellowKey2String(YellowKeys a);
    QBBG_EXTERN QBBG_EXPORT YellowKeys String2YellowKey(QString a);
}
Q_DECLARE_OPERATORS_FOR_FLAGS(QBbgLib::YellowKeys)
Q_DECLARE_OPERATORS_FOR_FLAGS(QBbgLib::BbgErrorCodes)
#endif // QBbgGenerals_h__
