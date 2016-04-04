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

#ifndef QBbgAbstractResponse_p_h__
#define QBbgAbstractResponse_p_h__
#include "QBbgAbstractResponse.h"
#include <QString>
namespace QBbgLib {
    class QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractResponse)
        QBbgAbstractResponsePrivate(const QBbgAbstractResponsePrivate& other);
    public:
        virtual ~QBbgAbstractResponsePrivate();
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, QBbgAbstractResponse::ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractResponsePrivate(QBbgAbstractResponse* q, const QBbgAbstractResponsePrivate& other);
        virtual QBbgAbstractResponsePrivate& operator=(const QBbgAbstractResponsePrivate& other);
        QBbgAbstractResponse::BbgErrorCodes m_ErrorCode;
        QString m_ErrorMessage;
        const QBbgAbstractResponse::ResponseType m_ResType;
        qint64 m_ID;
    protected:
        QBbgAbstractResponse* q_ptr;
    };

    

}
#endif // QBbgAbstractResponse_p_h__