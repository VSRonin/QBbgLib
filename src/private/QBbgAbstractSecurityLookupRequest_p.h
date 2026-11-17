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

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#ifndef QBbgAbstractSecurityLookupRequest_p_h__
#define QBbgAbstractSecurityLookupRequest_p_h__
#include "QBbgAbstractSecurityLookupRequest.h"
#include "private/QBbgAbstractRequest_p.h"
#include <QString>
namespace QBbgLib {
class QBbgAbstractSecurityLookupRequestPrivate : public QBbgAbstractRequestPrivate
{
    Q_DECLARE_PUBLIC(QBbgAbstractSecurityLookupRequest)
protected:
    QBbgAbstractRequest *q_ptr;

private:
    QBbgAbstractSecurityLookupRequestPrivate(const QBbgAbstractSecurityLookupRequestPrivate &other) = delete;

public:
    virtual ~QBbgAbstractSecurityLookupRequestPrivate() = 0;
    QBbgAbstractSecurityLookupRequestPrivate(QBbgAbstractSecurityLookupRequest *q, QBbgAbstractRequest::RequestType typ);
    QBbgAbstractSecurityLookupRequestPrivate(QBbgAbstractSecurityLookupRequest *q, const QBbgAbstractSecurityLookupRequestPrivate &other);
    virtual QBbgAbstractSecurityLookupRequestPrivate &operator=(const QBbgAbstractSecurityLookupRequestPrivate &other);
    QString m_query;
    int m_maxResults;
};
}
#endif // QBbgAbstractSecurityLookupRequest_p_h__
