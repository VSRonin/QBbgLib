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

#ifndef QBbgManager_p_h__
#define QBbgManager_p_h__
#include "QBbgManager.h"
#include <QHash>
#include <memory>
class QThread;
namespace BloombergLP { namespace blpapi { class SessionOptions; } }
namespace QBbgLib {
    class QBbgAbstractResponse;
    class QBbgAbstractWorker;
    class QBbgManagerPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgManager)
        QBbgManagerPrivate(const QBbgManagerPrivate&)=delete;
    public:
        QBbgManagerPrivate(QBbgManager* qp);
        virtual ~QBbgManagerPrivate();
        QHash<quint32, QHash<qint64, QBbgAbstractResponse* >* > m_ResultTable;
        QHash<quint32, std::pair<QThread*, QBbgAbstractWorker*> > m_ThreadPool;
        BloombergLP::blpapi::SessionOptions* m_options;
    protected:
        QBbgManager* q_ptr;
        
    };
}
#endif // QBbgManager_p_h__