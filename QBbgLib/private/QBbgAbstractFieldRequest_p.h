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

#ifndef QBbgAbstractFieldRequest_p_h__
#define QBbgAbstractFieldRequest_p_h__

#include "QBbgAbstractFieldRequest.h"
#include "QBbgAbstractRequest_p.h"
#include "QBbgOverride.h"
namespace QBbgLib {
    class QBbgAbstractFieldRequestPrivate : public QBbgAbstractRequestPrivate
    {
        Q_DECLARE_PUBLIC(QBbgAbstractFieldRequest)
    private:
        QBbgAbstractFieldRequestPrivate(const QBbgAbstractFieldRequestPrivate& a);
    public:
        virtual ~QBbgAbstractFieldRequestPrivate();
        QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, const QBbgAbstractFieldRequestPrivate& a);
        QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, QBbgAbstractRequest::RequestType typ/*=QBbgAbstractRequest::Invalid*/);
        QBbgAbstractFieldRequestPrivate& operator=(const QBbgAbstractFieldRequestPrivate& a);
        bool operator==(const QBbgAbstractFieldRequestPrivate& a) const;
        QString m_Field;
        QBbgOverride m_Overrides;
        bool SameOverrides(const QBbgAbstractFieldRequestPrivate& a)const;
    };
}
#endif // QBbgAbstractFieldRequest_p_h__