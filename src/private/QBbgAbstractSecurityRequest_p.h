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

#ifndef QBbgAbstractSecurityRequest_p_h__
#define QBbgAbstractSecurityRequest_p_h__
#include "QBbgAbstractSecurityRequest.h"
#include "private/QBbgAbstractRequest_p.h"
#include <QString>
#include "QBbgSecurity.h"
namespace QBbgLib {
class QBbgAbstractSecurityRequestPrivate : public QBbgAbstractRequestPrivate
{
    Q_DECLARE_PUBLIC(QBbgAbstractSecurityRequest)
protected:
    QBbgAbstractRequest *q_ptr;

private:
    QBbgAbstractSecurityRequestPrivate(const QBbgAbstractSecurityRequestPrivate &other) = delete;

public:
    virtual ~QBbgAbstractSecurityRequestPrivate() = 0;
    QBbgAbstractSecurityRequestPrivate(QBbgAbstractSecurityRequest *q, QBbgAbstractRequest::RequestType typ);
    QBbgAbstractSecurityRequestPrivate(QBbgAbstractSecurityRequest *q, const QBbgAbstractSecurityRequestPrivate &other);
    virtual QBbgAbstractSecurityRequestPrivate &operator=(const QBbgAbstractSecurityRequestPrivate &other);
    QBbgSecurity m_Security;
};
}
#endif // QBbgAbstractSecurityRequest_p_h__
