#include <blpapi_request.h>
#include "QBbgInstrumentLookupRequest.h"
#include "private/QBbgInstrumentLookupRequest_p.h"
namespace QBbgLib {
QBbgInstrumentLookupRequest::~QBbgInstrumentLookupRequest() = default;
QBbgInstrumentLookupRequestPrivate::~QBbgInstrumentLookupRequestPrivate() = default;
QBbgInstrumentLookupRequestPrivate::QBbgInstrumentLookupRequestPrivate(QBbgInstrumentLookupRequest *q)
    : QBbgAbstractSecurityLookupRequestPrivate(q, QBbgAbstractRequest::RequestType::InstrumentLookup)
    , m_yellowKeyFilter(QBbgInstrumentLookupRequest::YellowKeyFilter::None)
    , m_languageOverride(QBbgInstrumentLookupRequest::LanguageOverride::None)
{ }

QBbgInstrumentLookupRequestPrivate::QBbgInstrumentLookupRequestPrivate(QBbgInstrumentLookupRequest *q,
                                                                       const QBbgInstrumentLookupRequestPrivate &other)
    : QBbgAbstractSecurityLookupRequestPrivate(q, other)
    , m_yellowKeyFilter(other.m_yellowKeyFilter)
    , m_languageOverride(other.m_languageOverride)
{ }

QBbgInstrumentLookupRequestPrivate &QBbgInstrumentLookupRequestPrivate::operator=(const QBbgInstrumentLookupRequestPrivate &other)
{
    QBbgAbstractSecurityLookupRequestPrivate::operator=(other);
    m_yellowKeyFilter = other.m_yellowKeyFilter;
    m_languageOverride = other.m_languageOverride;
    return *this;
}
QBbgInstrumentLookupRequest::QBbgInstrumentLookupRequest()
    : QBbgAbstractSecurityLookupRequest(new QBbgInstrumentLookupRequestPrivate(this))
{ }

QBbgInstrumentLookupRequest::QBbgInstrumentLookupRequest(const QBbgInstrumentLookupRequest &a)
    : QBbgAbstractSecurityLookupRequest(new QBbgInstrumentLookupRequestPrivate(this, *(a.d_func())))
{ }

QBbgInstrumentLookupRequest &QBbgInstrumentLookupRequest::operator=(const QBbgInstrumentLookupRequest &a)
{
    Q_D(QBbgInstrumentLookupRequest);
    d->operator=(*(a.d_func()));
    return *this;
}
QBbgInstrumentLookupRequest::YellowKeyFilter QBbgInstrumentLookupRequest::yellowKeyFilterFromYellowKeys(QBbgSecurity::YellowKeys val)
{
    switch (val) {
    case QBbgSecurity::YellowKeys::Govt:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Govt;
    case QBbgSecurity::YellowKeys::Corp:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Corp;
    case QBbgSecurity::YellowKeys::Mtge:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Mtge;
    case QBbgSecurity::YellowKeys::MMkt:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::MMkt;
    case QBbgSecurity::YellowKeys::Muni:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Muni;
    case QBbgSecurity::YellowKeys::Pfd:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Pfd;
    case QBbgSecurity::YellowKeys::Equity:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Equity;
    case QBbgSecurity::YellowKeys::Comdty:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Comdty;
    case QBbgSecurity::YellowKeys::Index:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Index;
    case QBbgSecurity::YellowKeys::Curncy:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Curncy;
    case QBbgSecurity::YellowKeys::Client:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::Client;
    default:
        return QBbgInstrumentLookupRequest::YellowKeyFilter::None;
    }
}

QBbgInstrumentLookupRequest::YellowKeyFilter QBbgInstrumentLookupRequest::yellowKeyFilter() const
{
    Q_D(const QBbgInstrumentLookupRequest);
    return d->m_yellowKeyFilter;
}

QBbgInstrumentLookupRequest::LanguageOverride QBbgInstrumentLookupRequest::languageOverride() const
{
    Q_D(const QBbgInstrumentLookupRequest);
    return d->m_languageOverride;
}

void QBbgInstrumentLookupRequest::setYellowKeyFilter(YellowKeyFilter val)
{
    Q_D(QBbgInstrumentLookupRequest);
    d->m_yellowKeyFilter = val;
}

void QBbgInstrumentLookupRequest::setLanguageOverride(LanguageOverride val)
{
    Q_D(QBbgInstrumentLookupRequest);
    d->m_languageOverride = val;
}

bool QBbgInstrumentLookupRequest::operator==(const QBbgInstrumentLookupRequest &other) const
{
    Q_D(const QBbgInstrumentLookupRequest);
    return QBbgAbstractSecurityLookupRequest::operator==(other) && d->m_yellowKeyFilter == other.d_func()->m_yellowKeyFilter
            && d->m_languageOverride == other.d_func()->m_languageOverride;
}

QBbgSecurity::YellowKeys QBbgInstrumentLookupRequest::yellowKeysFromYellowKeyFilter(YellowKeyFilter val)
{
    switch (val) {
    case YellowKeyFilter::Govt:
        return QBbgSecurity::YellowKeys::Govt;
    case YellowKeyFilter::Corp:
        return QBbgSecurity::YellowKeys::Corp;
    case YellowKeyFilter::Mtge:
        return QBbgSecurity::YellowKeys::Mtge;
    case YellowKeyFilter::MMkt:
        return QBbgSecurity::YellowKeys::MMkt;
    case YellowKeyFilter::Muni:
        return QBbgSecurity::YellowKeys::Muni;
    case YellowKeyFilter::Pfd:
        return QBbgSecurity::YellowKeys::Pfd;
    case YellowKeyFilter::Equity:
        return QBbgSecurity::YellowKeys::Equity;
    case YellowKeyFilter::Comdty:
        return QBbgSecurity::YellowKeys::Comdty;
    case YellowKeyFilter::Index:
        return QBbgSecurity::YellowKeys::Index;
    case YellowKeyFilter::Curncy:
        return QBbgSecurity::YellowKeys::Curncy;
    case YellowKeyFilter::Client:
        return QBbgSecurity::YellowKeys::Client;
    default:
        return QBbgSecurity::YellowKeys::Invalid;
    }
}

QString QBbgInstrumentLookupRequest::yellowKeyFilterString(YellowKeyFilter val)
{
    switch (val) {
    case YellowKeyFilter::None:
        return QString();
    case YellowKeyFilter::Govt:
        return QStringLiteral("YK_FILTER_GOVT");
    case YellowKeyFilter::Corp:
        return QStringLiteral("YK_FILTER_CORP");
    case YellowKeyFilter::Mtge:
        return QStringLiteral("YK_FILTER_MTGE");
    case YellowKeyFilter::MMkt:
        return QStringLiteral("YK_FILTER_MMKT");
    case YellowKeyFilter::Muni:
        return QStringLiteral("YK_FILTER_MUNI");
    case YellowKeyFilter::Pfd:
        return QStringLiteral("YK_FILTER_PRFD");
    case YellowKeyFilter::Equity:
        return QStringLiteral("YK_FILTER_EQTY");
    case YellowKeyFilter::Comdty:
        return QStringLiteral("YK_FILTER_CMDT");
    case YellowKeyFilter::Index:
        return QStringLiteral("YK_FILTER_INDX");
    case YellowKeyFilter::Curncy:
        return QStringLiteral("YK_FILTER_CURR");
    case YellowKeyFilter::Client:
        return QStringLiteral("YK_FILTER_CLNT");
    default:
        Q_UNREACHABLE();
    }
}

QString QBbgInstrumentLookupRequest::languageOverrideString(LanguageOverride val)
{
    switch (val) {
    case LanguageOverride::None:
        return QString();
    case LanguageOverride::English:
        return QStringLiteral("LANG_OVERRIDE_ENGLISH");
    case LanguageOverride::Kanji:
        return QStringLiteral("LANG_OVERRIDE_KANJI");
    case LanguageOverride::French:
        return QStringLiteral("LANG_OVERRIDE_FRENCH");
    case LanguageOverride::German:
        return QStringLiteral("LANG_OVERRIDE_GERMAN");
    case LanguageOverride::Spanish:
        return QStringLiteral("LANG_OVERRIDE_SPANISH");
    case LanguageOverride::Portuguese:
        return QStringLiteral("LANG_OVERRIDE_PORTUGUESE");
    case LanguageOverride::Italian:
        return QStringLiteral("LANG_OVERRIDE_ITALIAN");
    case LanguageOverride::ChineseTraditional:
        return QStringLiteral("LANG_OVERRIDE_CHINESE_TRAD");
    case LanguageOverride::Korean:
        return QStringLiteral("LANG_OVERRIDE_KOREAN");
    case LanguageOverride::ChineseSimplified:
        return QStringLiteral("LANG_OVERRIDE_CHINESE_SIMP");
    case LanguageOverride::Russian:
        return QStringLiteral("LANG_OVERRIDE_RUSSIAN");
    default:
        Q_UNREACHABLE();
    }
}

void QBbgInstrumentLookupRequest::applyRequest(QJsonObject &obj) const
{
    QBbgAbstractSecurityLookupRequest::applyRequest(obj);
    Q_D(const QBbgInstrumentLookupRequest);
    if (!obj.contains(QStringLiteral("yellowKeyFilter")) && d->m_yellowKeyFilter != YellowKeyFilter::None)
        obj.insert(QStringLiteral("yellowKeyFilter"), yellowKeyFilterString(d->m_yellowKeyFilter));
    if (!obj.contains(QStringLiteral("languageOverride")) && d->m_languageOverride != LanguageOverride::None)
        obj.insert(QStringLiteral("languageOverride"), languageOverrideString(d->m_languageOverride));
}

void QBbgInstrumentLookupRequest::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgInstrumentLookupRequest);
    QBbgAbstractSecurityLookupRequest::saveToStream(stream);
    stream << static_cast<std::underlying_type<YellowKeyFilter>::type>(d->m_yellowKeyFilter)
           << static_cast<std::underlying_type<LanguageOverride>::type>(d->m_languageOverride);
}

void QBbgInstrumentLookupRequest::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgInstrumentLookupRequest);
    QBbgAbstractSecurityLookupRequest::loadFromStream(stream);
    std::underlying_type<YellowKeyFilter>::type tempYellowKeyFilter;
    std::underlying_type<LanguageOverride>::type tempLanguageOverride;
    stream >> tempYellowKeyFilter >> tempLanguageOverride;
    d->m_yellowKeyFilter = static_cast<YellowKeyFilter>(tempYellowKeyFilter);
    d->m_languageOverride = static_cast<LanguageOverride>(tempLanguageOverride);
}

}
