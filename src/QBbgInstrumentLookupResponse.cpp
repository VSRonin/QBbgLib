#include "QBbgInstrumentLookupResponse.h"
#include "private/QBbgInstrumentLookupResponse_p.h"
#include <QJsonObject>
#include <QJsonArray>
namespace QBbgLib {
QBbgInstrumentLookupResponse::~QBbgInstrumentLookupResponse() = default;
QBbgInstrumentLookupResponsePrivate::~QBbgInstrumentLookupResponsePrivate() = default;
QBbgInstrumentLookupResponse::QBbgInstrumentLookupResponse()
    : QBbgAbstractResponse(new QBbgInstrumentLookupResponsePrivate(this))
{ }

QBbgInstrumentLookupResponse::QBbgInstrumentLookupResponse(QBbgInstrumentLookupResponsePrivate *dp)
    : QBbgAbstractResponse(dp)
{ }

QBbgInstrumentLookupResponse::QBbgInstrumentLookupResponse(const QBbgInstrumentLookupResponse &other)
    : QBbgAbstractResponse(new QBbgInstrumentLookupResponsePrivate(this, *(other.d_func())))
{ }

QBbgInstrumentLookupResponse &QBbgInstrumentLookupResponse::operator=(const QBbgInstrumentLookupResponse &other)
{
    Q_D(QBbgInstrumentLookupResponse);
    d->operator=(*(other.d_func()));
    return *this;
}
QBbgInstrumentLookupResponsePrivate::QBbgInstrumentLookupResponsePrivate(QBbgInstrumentLookupResponse *q)
    : QBbgAbstractResponsePrivate(q, QBbgAbstractResponse::ResponseType::InstrumentListResponse)
{ }

QBbgInstrumentLookupResponsePrivate::QBbgInstrumentLookupResponsePrivate(QBbgInstrumentLookupResponse *q,
                                                                         const QBbgInstrumentLookupResponsePrivate &other)
    : QBbgAbstractResponsePrivate(q, other)
    , m_resultSecurity(other.m_resultSecurity)
    , m_resultDescription(other.m_resultDescription)
{ }

QBbgInstrumentLookupResponsePrivate &QBbgInstrumentLookupResponsePrivate::operator=(const QBbgInstrumentLookupResponsePrivate &other)
{
    QBbgAbstractResponsePrivate::operator=(other);
    m_resultSecurity = other.m_resultSecurity;
    m_resultDescription = other.m_resultDescription;
    return *this;
}
int QBbgInstrumentLookupResponse::size() const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultSecurity.size();
}

bool QBbgInstrumentLookupResponse::isEmpty() const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultSecurity.isEmpty();
}

QString QBbgInstrumentLookupResponse::secutity(int index) const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultSecurity.value(index, QString());
}

QString QBbgInstrumentLookupResponse::description(int index) const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultDescription.value(index, QString());
}

const QStringList &QBbgInstrumentLookupResponse::secutities() const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultSecurity;
}

const QStringList &QBbgInstrumentLookupResponse::descriptions() const
{
    Q_D(const QBbgInstrumentLookupResponse);
    return d->m_resultDescription;
}

void QBbgInstrumentLookupResponse::addValue(const QString &sec, const QString &desc)
{
    if (sec.isEmpty())
        return;
    Q_D(QBbgInstrumentLookupResponse);
    d->m_resultSecurity.append(sec);
    d->m_resultDescription.append(desc);
}

void QBbgInstrumentLookupResponse::clear()
{
    Q_D(QBbgInstrumentLookupResponse);
    d->m_resultSecurity.clear();
    d->m_resultDescription.clear();
}

void QBbgInstrumentLookupResponse::saveToStream(QDataStream &stream) const
{
    QBbgAbstractResponse::saveToStream(stream);
    Q_D(const QBbgInstrumentLookupResponse);
    stream << d->m_resultSecurity << d->m_resultDescription;
}

void QBbgInstrumentLookupResponse::loadFromStream(QDataStream &stream)
{
    QBbgAbstractResponse::loadFromStream(stream);
    Q_D(QBbgInstrumentLookupResponse);
    stream >> d->m_resultSecurity >> d->m_resultDescription;
}

bool QBbgInstrumentLookupResponse::loadFromJsonResponse(const QJsonObject &obj)
{
    const QJsonValue resultsValue = obj.value(QStringLiteral("results"));
    if (!resultsValue.isArray())
        return false;
    const QJsonArray resultsArray = resultsValue.toArray();
    if (resultsArray.isEmpty())
        return false;
    QStringList securitiesToAppend;
    QStringList descriptionsToAppend;
    for (const QJsonValue &resultValue : resultsArray) {
        if (!resultValue.isObject())
            return false;
        const QJsonObject resultObject = resultValue.toObject();
        const QJsonValue securityValue = resultObject.value(QStringLiteral("security"));
        const QJsonValue descriptionValue = resultObject.value(QStringLiteral("description"));
        if (!securityValue.isString() || !descriptionValue.isString())
            return false;
        securitiesToAppend.append(securityValue.toString());
        descriptionsToAppend.append(descriptionValue.toString());
    }
    Q_D(QBbgInstrumentLookupResponse);
    d->m_resultSecurity.append(securitiesToAppend);
    d->m_resultDescription.append(descriptionsToAppend);
    return true;
}

}
