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

#ifndef QBbgRequest_p_h__
#define QBbgRequest_p_h__
#include "QBbgRequestGroup.h"
#include <QHash>
namespace QBbgLib {
    class QBbgRequestGroupPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgRequestGroup)
        QBbgRequestGroup* q_ptr;
        QBbgRequestGroupPrivate(const QBbgRequestGroupPrivate& a);
        QBbgAbstractRequest* createRequest(const QBbgAbstractRequest& a) const;
        qint64 increaseMaxID();
    public:
        QBbgRequestGroupPrivate(QBbgRequestGroup* q,const QBbgRequestGroupPrivate& a);
        QBbgRequestGroupPrivate(QBbgRequestGroup* q);
        QBbgRequestGroupPrivate& operator=(const QBbgRequestGroupPrivate& a);
        virtual ~QBbgRequestGroupPrivate();
        static qint64 MaxID;
        QHash<qint64, QBbgAbstractRequest*>  RequestTable;
        void clear();
        qint64 addRequest(const QBbgAbstractRequest& a);
        qint64 addRequest(QBbgAbstractRequest& a, qint64 preferredID);
        const QBbgAbstractRequest* request(qint64 ID) const;
        bool SameRequest(const QList<qint64>& a, const QList<qint64>& b) const;
        bool compatible(const QBbgAbstractRequest* a, const QBbgAbstractRequest* b) const; 
    };

    
}
#endif // QBbgRequest_p_h__