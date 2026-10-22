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

#include "QBbgAbstractSecurityRequest.h"
#include "private/QBbgAbstractSecurityRequest_p.h"
#include <QHash>
#include <QDataStream>
namespace QBbgLib {

QBbgAbstractSecurityRequestPrivate::~QBbgAbstractSecurityRequestPrivate() = default;

QBbgAbstractSecurityRequest::QBbgAbstractSecurityRequest(QBbgAbstractSecurityRequestPrivate *d)
    : QBbgAbstractRequest(d)
{ }
QBbgAbstractSecurityRequest::~QBbgAbstractSecurityRequest() = default;



QBbgAbstractSecurityRequestPrivate::QBbgAbstractSecurityRequestPrivate(QBbgAbstractSecurityRequest *q, const QBbgAbstractSecurityRequestPrivate &other)
    : QBbgAbstractRequestPrivate(q, other)
    , m_Security(other.m_Security)
{ }

QBbgAbstractSecurityRequestPrivate::QBbgAbstractSecurityRequestPrivate(QBbgAbstractSecurityRequest *q, QBbgAbstractRequest::RequestType typ)
    : QBbgAbstractRequestPrivate(q, typ)
{ }

QBbgAbstractSecurityRequestPrivate &QBbgAbstractSecurityRequestPrivate::operator=(const QBbgAbstractSecurityRequestPrivate &other)
{
    QBbgAbstractRequestPrivate::operator=(other);
    m_Security = other.m_Security;
    return *this;
}
void QBbgAbstractSecurityRequest::saveToStream(QDataStream &stream) const
{
    Q_D(const QBbgAbstractSecurityRequest);
    QBbgAbstractRequest::saveToStream(stream);
    stream << d->m_Security;
}

void QBbgAbstractSecurityRequest::loadFromStream(QDataStream &stream)
{
    Q_D(QBbgAbstractSecurityRequest);
    QBbgAbstractRequest::loadFromStream(stream);
    stream >> d->m_Security;
}

void QBbgAbstractSecurityRequest::applyRequest(QJsonObject& obj) const
{
    Q_UNREACHABLE(); //TODO Implement
}
void QBbgAbstractSecurityRequest::setSecurity(const QBbgSecurity &val)
{
    Q_D(QBbgAbstractSecurityRequest);
    d->m_Security = val;
}
void QBbgAbstractSecurityRequest::setSecurity(const QString &SecName, QBbgSecurity::YellowKeys SecKey)
{
    setSecurity(QBbgSecurity(SecName, SecKey));
}
const QBbgSecurity &QBbgAbstractSecurityRequest::security() const
{
    Q_D(const QBbgAbstractSecurityRequest);
    return d->m_Security;
}
QBbgAbstractSecurityRequest &QBbgAbstractSecurityRequest::operator=(const QBbgAbstractSecurityRequest &other)
{
    Q_D(QBbgAbstractSecurityRequest);
    d->operator=(*(other.d_func()));
    return *this;
}

bool QBbgAbstractSecurityRequest::isValidReq() const
{
    Q_D(const QBbgAbstractSecurityRequest);
    return d->m_Security.isValid() && QBbgAbstractRequest::isValidReq();
}

bool QBbgAbstractSecurityRequest::operator==(const QBbgAbstractSecurityRequest &other) const
{
    Q_D(const QBbgAbstractSecurityRequest);
    return QBbgAbstractRequest::operator==(other) && d->m_Security == other.d_func()->m_Security;
}

}
