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
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

/*******************************************************************************\
* This file does not form part of the public API                                *
\*******************************************************************************/

#ifndef QBbgOverride_p_h__
#define QBbgOverride_p_h__
#include "QBbgOverride.h"
#include <QHash>
#include <QString>
namespace QBbgLib {
    class QBbgOverridePrivate
    {
        Q_DECLARE_PUBLIC(QBbgOverride)
        QBbgOverridePrivate(const QBbgOverridePrivate& other);
    public:
        virtual ~QBbgOverridePrivate();
        QBbgOverridePrivate(QBbgOverride* q);
        QBbgOverridePrivate(QBbgOverride* q, const QBbgOverridePrivate& other);
        QBbgOverridePrivate& operator=(const QBbgOverridePrivate& other);
    protected:
        QBbgOverride* q_ptr;
        QHash<QString, QString> m_Overrides;
    };
}
#endif // QBbgOverride_p_h__