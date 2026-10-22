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

#include "QBbgAbstractSecurityLookupRequest.h"
#include "private/QBbgAbstractSecurityLookupRequest_p.h"
#include <QHash>
#include <QDataStream>
#include <QJsonObject>
namespace QBbgLib {

QBbgAbstractSecurityLookupRequestPrivate::~QBbgAbstractSecurityLookupRequestPrivate() = default;

QBbgAbstractSecurityLookupRequest::QBbgAbstractSecurityLookupRequest(QBbgAbstractSecurityLookupRequestPrivate *d)
    : QBbgAbstractRequest(d)
{ }
QBbgAbstractSecurityLookupRequest::~QBbgAbstractSecurityLookupRequest() = default;



QBbgAbstractSecurityLookupRequestPrivate::QBbgAbstractSecurityLookupRequestPrivate(QBbgAbstractSecurityLookupRequest *q, const QBbgAbstractSecurityLookupRequestPrivate &other)
    : QBbgAbstractRequestPrivate(q, other)
    , m_query(other.m_query)
    , m_maxResults(other.m_maxResults)
{ }

QBbgAbstractSecurityLookupRequestPrivate::QBbgAbstractSecurityLookupRequestPrivate(QBbgAbstractSecurityLookupRequest *q, QBbgAbstractRequest::RequestType typ)
    : QBbgAbstractRequestPrivate(q, typ)
    , m_maxResults(100)
{ }

QBbgAbstractSecurityLookupRequestPrivate &QBbgAbstractSecurityLookupRequestPrivate::operator=(const QBbgAbstractSecurityLookupRequestPrivate &other)
{
    QBbgAbstractRequestPrivate::operator=(other);
    m_query = other.m_query;
    m_maxResults = other.m_maxResults;
    return *this;
}

void QBbgAbstractSecurityLookupRequest::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    QBbgAbstractRequest::saveToStream(stream);
    stream << d->m_query << d->m_maxResults;
}

void QBbgAbstractSecurityLookupRequest::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgAbstractSecurityLookupRequest);
    QBbgAbstractRequest::loadFromStream(stream);
    stream >> d->m_query >> d->m_maxResults;
}

void QBbgAbstractSecurityLookupRequest::applyRequest(QJsonObject& obj) const
{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    if(!obj.contains(QStringLiteral("query")))
        obj.insert(QStringLiteral("query"),d->m_query);
    if(!obj.contains(QStringLiteral("maxResults")))
        obj.insert(QStringLiteral("maxResults"),d->m_maxResults);
}
void QBbgAbstractSecurityLookupRequest::setQuery(const QString &val)
{
    Q_D(QBbgAbstractSecurityLookupRequest);
    d->m_query = val;
}

const QString &QBbgAbstractSecurityLookupRequest::query() const
{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    return d->m_query;
}

int QBbgAbstractSecurityLookupRequest::maxResults() const{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    return d->m_maxResults;
}

void QBbgAbstractSecurityLookupRequest::setMaxResults(int val){
    Q_D(QBbgAbstractSecurityLookupRequest);
    d->m_maxResults = val;
}

QBbgAbstractSecurityLookupRequest &QBbgAbstractSecurityLookupRequest::operator=(const QBbgAbstractSecurityLookupRequest &other)
{
    Q_D(QBbgAbstractSecurityLookupRequest);
    d->operator=(*(other.d_func()));
    return *this;
}

bool QBbgAbstractSecurityLookupRequest::isValidReq() const
{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    return d->m_maxResults>0 && !d->m_query.isEmpty() && QBbgAbstractRequest::isValidReq();
}

bool QBbgAbstractSecurityLookupRequest::operator==(const QBbgAbstractSecurityLookupRequest &other) const
{
    Q_D(const QBbgAbstractSecurityLookupRequest);
    return QBbgAbstractRequest::operator==(other) && d->m_query == other.d_func()->m_query && d->m_maxResults == other.d_func()->m_maxResults;
}

}
