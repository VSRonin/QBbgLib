/*******************************************************************************\
* This file is part of QBbgLib.                                                 *
*                                                                               *
* QBbgLib is free software : you can redistribute it and / or modify            *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* QBbgLib is distributed in the hope that it will be useful,                    *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                   *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/ >.             *
*                                                                               *
\*******************************************************************************/

#include "QBbgAbstractResponse.h"
#include "private/QBbgAbstractResponse_p.h"
#include <QHash>
#include <QDataStream>
namespace QBbgLib {

QBbgAbstractResponsePrivate::~QBbgAbstractResponsePrivate() = default;

QBbgAbstractResponse::~QBbgAbstractResponse()
{
    delete d_ptr;
}
QBbgAbstractResponse::QBbgAbstractResponse(QBbgAbstractResponsePrivate *d)
    : d_ptr(d)
{ }
void QBbgAbstractResponse::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgAbstractResponse);
    stream << d->m_ID << d->m_ErrorMessage << static_cast<std::underlying_type<BbgErrorCodesF>::type>(int(d->m_ErrorCode));
}

void QBbgAbstractResponse::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgAbstractResponse);
    std::underlying_type<BbgErrorCodesF>::type errInt;
    stream >> d->m_ID >> d->m_ErrorMessage >> errInt;
    d->m_ErrorCode = static_cast<BbgErrorCodesF>(errInt);
}
void QBbgAbstractResponse::setErrorCode(BbgErrorCodes ErrCd, const QString &errMsg)
{
    Q_D(QBbgAbstractResponse);
    if (ErrCd == NoErrors) {
        d->m_ErrorCode = NoErrors;
        d->m_ErrorMessage.clear();
    } else {
        d->m_ErrorCode |= ErrCd;
        d->m_ErrorMessage = errMsg;
    }
}
bool QBbgAbstractResponse::hasErrors() const
{
    return errorCode() != NoErrors;
}
QBbgAbstractResponse::BbgErrorCodes QBbgAbstractResponse::errorCode() const
{
    Q_D(const QBbgAbstractResponse);
    return d->m_ErrorCode;
}
QString QBbgAbstractResponse::errorString() const
{
    return bbgErrorCode2String(errorCode());
}
QBbgAbstractResponse &QBbgAbstractResponse::operator=(const QBbgAbstractResponse &other)
{
    Q_D(QBbgAbstractResponse);
    d->operator=(*(other.d_func()));
    return *this;
}
void QBbgAbstractResponse::setID(qint64 val)
{
    Q_D(QBbgAbstractResponse);
    d->m_ID = val;
}
qint64 QBbgAbstractResponse::getID() const
{
    Q_D(const QBbgAbstractResponse);
    return d->m_ID;
}
QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse *q, QBbgAbstractResponse::ResponseType typ)
    : q_ptr(q)
    , m_ErrorCode(QBbgAbstractResponse::NoErrors)
    , m_ResType(typ)
    , m_ID(0)
{ }
QBbgAbstractResponsePrivate::QBbgAbstractResponsePrivate(QBbgAbstractResponse *q, const QBbgAbstractResponsePrivate &other)
    : q_ptr(q)
    , m_ErrorCode(other.m_ErrorCode)
    , m_ResType(other.m_ResType)
    , m_ID(other.m_ID)
{ }
QBbgAbstractResponsePrivate &QBbgAbstractResponsePrivate::operator=(const QBbgAbstractResponsePrivate &other)
{
    Q_ASSERT_X(m_ResType == other.m_ResType, "QBbgAbstractRequestPrivate::operator=", "Trying to copy between two diffrent Response types");
    m_ErrorCode = other.m_ErrorCode;
    m_ID = other.m_ID;
    return *this;
}
QString QBbgAbstractResponse::bbgErrorCode2String(BbgErrorCodes a)
{
    if (a == NoErrors)
        return QStringLiteral("No Errors");
    QString Result;
    if (a & ResponseError)
        Result += QLatin1String("Response Error, ");
    if (a & SecurityError)
        Result += QLatin1String("Invalid Security, ");
    if (a & InvalidInputs)
        Result += QLatin1String("Invalid Inputs, ");
    if (a & SessionError)
        Result += QLatin1String("Session Error, ");
    if (a & ServiceError)
        Result += QLatin1String("Service Error, ");
    if (a & FieldError)
        Result += QLatin1String("Invalid Field, ");
    if (a & UnknownError)
        Result += QLatin1String("Unknown Error, ");
    if (a & SessionStopped)
        Result += QLatin1String("Session Stopped, ");
    if (a & NoData)
        Result += QLatin1String("No Data, ");
    Result.chop(2);
    return Result;
}

QBbgAbstractResponse::ResponseType QBbgAbstractResponse::responseType() const
{
    Q_D(const QBbgAbstractResponse);
    return d->m_ResType;
}
QBbgAbstractResponse::ResponseType QBbgAbstractResponse::stringToResponseType(QString a)
{
    a = a.toLower().trimmed();
    if (a == QStringLiteral("BeqsResponse"))
        return ResponseType::BeqsResponse;
    else if (a == QStringLiteral("historicaldataresponse"))
        return ResponseType::HistoricalDataResponse;
    else if (a == QStringLiteral("referencedataresponse"))
        return ResponseType::ReferenceDataResponse;
    else if (a == QStringLiteral("portfoliodataresponse"))
        return ResponseType::PortfolioDataResponse;
    else if (a == QStringLiteral("intradaytickresponse"))
        return ResponseType::IntraDayTickResponse;
    else if (a == QStringLiteral("intradaybarresponse"))
        return ResponseType::IntraDayBarResponse;
    else
        return ResponseType::Invalid;
}
QString QBbgAbstractResponse::responseTypeToString(ResponseType a)
{
    switch (a) {
    case QBbgLib::QBbgAbstractResponse::ResponseType::BeqsResponse:
        return QStringLiteral("BeqsResponse");
    case QBbgLib::QBbgAbstractResponse::ResponseType::HistoricalDataResponse:
        return QStringLiteral("HistoricalDataResponse");
    case QBbgLib::QBbgAbstractResponse::ResponseType::ReferenceDataResponse:
        return QStringLiteral("ReferenceDataResponse");
    case QBbgLib::QBbgAbstractResponse::ResponseType::PortfolioDataResponse:
        return QStringLiteral("PortfolioDataResponse");
    case QBbgLib::QBbgAbstractResponse::ResponseType::IntraDayTickResponse:
        return QStringLiteral("IntraDayTickResponse");
    case QBbgLib::QBbgAbstractResponse::ResponseType::IntraDayBarResponse:
        return QStringLiteral("IntraDayBarResponse");
    default:
        return QString();
    }
}
QString QBbgAbstractResponse::errorMessage() const
{
    Q_D(const QBbgAbstractResponse);
    return errorString() + QLatin1String(" - ") + d->m_ErrorMessage;
}
}

uint qHash(QBbgLib::QBbgAbstractResponse::ResponseType key, uint seed)
{
    return qHash(static_cast<std::underlying_type<decltype(key)>::type>(key), seed);
}

QDataStream &operator<<(QDataStream &stream, const QBbgLib::QBbgAbstractResponse &obj)
{
    obj.saveToStream(stream);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QBbgLib::QBbgAbstractResponse &obj)
{
    obj.loadFromStream(stream);
    return stream;
}
