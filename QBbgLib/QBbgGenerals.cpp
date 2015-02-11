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

