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

#ifndef QBbgAbstractRequest_p_h__
#define QBbgAbstractRequest_p_h__
#include "QBbgAbstractRequest.h"
#include <QString>
#include "QBbgSecurity.h"
namespace QBbgLib {
    class QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgAbstractRequest)
    protected:
        QBbgAbstractRequest* q_ptr;
    private:
        QBbgAbstractRequestPrivate(const QBbgAbstractRequestPrivate& other);
    public:
        virtual ~QBbgAbstractRequestPrivate();
        QBbgAbstractRequestPrivate(QBbgAbstractRequest* q, QBbgAbstractRequest::RequestType typ/*=QBbgAbstractRequest::Invalid*/);
        QBbgAbstractRequestPrivate(QBbgAbstractRequest* q,const QBbgAbstractRequestPrivate& other);
        virtual QBbgAbstractRequestPrivate& operator=(const QBbgAbstractRequestPrivate& other);
        qint64 m_ID;
        QBbgSecurity m_Security;
        const QBbgAbstractRequest::RequestType m_RqType;
    };
}
#endif // QBbgAbstractRequest_p_h__