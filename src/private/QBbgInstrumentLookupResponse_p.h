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

#ifndef QBbgInstrumentLookupResponse_p_h__
#define QBbgInstrumentLookupResponse_p_h__
#include "QBbgInstrumentLookupResponse.h"
#include "private/QBbgAbstractResponse_p.h"
#include <QList>
namespace QBbgLib {
class QBbgInstrumentLookupResponsePrivate : public QBbgAbstractResponsePrivate
{
private:
    Q_DECLARE_PUBLIC(QBbgInstrumentLookupResponse)
    QBbgInstrumentLookupResponsePrivate(const QBbgInstrumentLookupResponsePrivate &other) = delete;

public:
    virtual ~QBbgInstrumentLookupResponsePrivate();
    QBbgInstrumentLookupResponsePrivate(QBbgInstrumentLookupResponse *q, const QBbgInstrumentLookupResponsePrivate &other);
    QBbgInstrumentLookupResponsePrivate(QBbgInstrumentLookupResponse *q);
    virtual QBbgInstrumentLookupResponsePrivate &operator=(const QBbgInstrumentLookupResponsePrivate &other);
    QStringList m_resultSecurity;
    QStringList m_resultDescription;
};

}
#endif
