/*
This file is part of QBbgLib.

QBbgLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QBbgLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with QBbgLib.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QBbgSecurity_p_h__
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
* along with QBbgLib. If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#define QBbgSecurity_p_h__
#include "QBbgSecurity.h"
#include <QString>
namespace QBbgLib {
    class QBbgSecurityPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgSecurity)
        QBbgSecurity* q_ptr;
        QBbgSecurityPrivate(const QBbgSecurityPrivate& other);
    public:
        virtual ~QBbgSecurityPrivate();
        QBbgSecurityPrivate(QBbgSecurity* q);
        QBbgSecurityPrivate(QBbgSecurity* q,const QBbgSecurityPrivate& other);
        QBbgSecurityPrivate& operator=(const QBbgSecurityPrivate& other);
        bool operator==(const QBbgSecurityPrivate& other) const;
        QString m_Name;
        QBbgSecurity::YellowKeys m_Extension;
        QString m_Exchange;
        QString m_PricingSource;
    };
}
#endif // QBbgSecurity_p_h__