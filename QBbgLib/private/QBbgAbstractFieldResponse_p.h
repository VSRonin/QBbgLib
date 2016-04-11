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
#ifndef QBbgAbstractFieldResponse_p_h__
#define QBbgAbstractFieldResponse_p_h__

#include "QBbgAbstractFieldResponse.h"
#include "QBbgAbstractResponse_p.h"
#include <QString>
#include <QVariant>
namespace QBbgLib {
    class QBbgAbstractFieldResponsePrivate : public QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractFieldResponse)
        QBbgAbstractFieldResponsePrivate(const QBbgAbstractFieldResponsePrivate& other)=delete;
    public:
        virtual ~QBbgAbstractFieldResponsePrivate()=0;
        QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, QBbgAbstractResponse::ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, const QBbgAbstractFieldResponsePrivate& other);
        virtual QBbgAbstractFieldResponsePrivate& operator=(const QBbgAbstractFieldResponsePrivate& other);
        QString m_Header;
    };
}
#endif // QBbgAbstractFieldResponse_p_h__