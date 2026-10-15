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
#ifndef QBbgSessionMonitorWorker_h__
#define QBbgSessionMonitorWorker_h__
namespace QBbgLib {
class QBbgSessionMonitorWorker;
}
#ifndef QBbg_OFFLINE

#    include "private/QBbgAbstractWorker_p.h"
#    include "QBbgRequestGroup.h"
namespace QBbgLib {
class QBbgSessionMonitorWorker : public QBbgAbstractWorker
{
    Q_OBJECT
public:
    QBbgSessionMonitorWorker(const BloombergLP::blpapi::SessionOptions &option, QObject *parent = nullptr);
    virtual ~QBbgSessionMonitorWorker() = default;

protected:
    void handleResponseEvent(const BloombergLP::blpapi::Event &event, bool isFinal) override;
    bool processEvent(const BloombergLP::blpapi::Event &event, BloombergLP::blpapi::Session *CurrentSession) override;
public slots:
    bool start() override;
    void setRequest(const QBbgRequestGroup &req) override;
};
}
#endif // QBbg_OFFLINE
#endif // QBbgSessionMonitorWorker_h__
