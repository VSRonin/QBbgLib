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

#ifndef QBbgReferenceDataResponse_p_h__
#define QBbgReferenceDataResponse_p_h__
#include "QBbgReferenceDataResponse.h"
#include "private/QBbgAbstractFieldResponse_p.h"
#include <QList>
namespace QBbgLib {
    class QBbgReferenceDataResponsePrivate : public QBbgAbstractFieldResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgReferenceDataResponse)
        QBbgReferenceDataResponsePrivate(const QBbgReferenceDataResponsePrivate& other)=delete;
    public:
        virtual ~QBbgReferenceDataResponsePrivate();
        QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q, const QBbgReferenceDataResponsePrivate& other);
        QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q);
        virtual QBbgReferenceDataResponsePrivate& operator=(const QBbgReferenceDataResponsePrivate& other);
        QVariant m_Value;
        QList<QBbgReferenceDataResponse*> m_TableResultRows;
        qint32 m_TableCols;
    	
    };

    

   

    

}
#endif // QBbgReferenceDataResponse_p_h__