#include "QBbgGenerals.h"
QString QBbgLib::BbgErrorCodes2String(QBbgLib::BbgErrorCodes a)
{
    if (a == 0) return "NoErrors";
    QString Result = "";
    if (a & ResponseError) Result += "Response Error, ";
    if (a & SecurityError) Result += "Invalid Security, ";
    if (a & InvalidInputs) Result += "Invalid Inputs, ";
    if (a & SessionError) Result += "Session Error, ";
    if (a & ServiceError) Result += "Service Error, ";
    if (a & FieldError) Result += "Invalid Field, ";
    if (a & UnknownError) Result += "Unknown Error, ";
    if (a & SessionStopped) Result += "Session Stopped, ";
    if (a & NoData) Result += "No Data, ";
    Result.chop(2);
    return Result;
}

QString QBbgLib::YellowKey2String(QBbgLib::YellowKeys a)
{
    switch (a) {
    case Govt: return "Govt";
    case Corp: return "Corp";
    case Mtge: return "Mtge";
    case MMkt: return "MMkt";
    case Muni: return "Muni";
    case Pfd: return "Pfd";
    case Equity: return "Equity";
    case Comdty: return "Comdty";
    case Index: return "Index";
    case Curncy: return "Curncy";
    default: return "";
    }
}
QBbgLib::YellowKeys QBbgLib::String2YellowKey(QString a)
{
    a = a.toLower();
    if (a == "govt") return Govt;
    else if (a == "corp") return Corp;
    else if (a == "mtge") return Mtge;
    else if (a == "mmkt") return MMkt;
    else if (a == "muni") return Muni;
    else if (a == "pfd") return Pfd;
    else if (a == "equity") return Equity;
    else if (a == "comdty") return Comdty;
    else if (a == "index") return Index;
    else if (a == "curncy") return Curncy;
    else return Invalid;
}