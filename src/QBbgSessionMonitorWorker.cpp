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

#ifndef QBbg_OFFLINE

#    include "private/QBbgSessionMonitorWorker_p.h"
#    include <blpapi_session.h>

namespace QBbgLib {

bool QBbgSessionMonitorWorker::processEvent(const BloombergLP::blpapi::Event &event, BloombergLP::blpapi::Session *CurrentSession)
{
    if (!sessionRunning())
        return false;
    switch (event.eventType()) {
    case BloombergLP::blpapi::Event::SESSION_STATUS: {
        BloombergLP::blpapi::MessageIterator iter(event);
        while (iter.next() && sessionRunning()) {
            BloombergLP::blpapi::Message message = iter.message();
            QString MessageType = QString::fromLocal8Bit(message.messageType().string(), -1);
            if (MessageType == QStringLiteral("SessionStarted")) {
                setSessionRunning(true);
                emit started(); // Emit signal
            } else if (MessageType == QStringLiteral("SessionConnectionUp"))
                continue;
            else if (MessageType == QStringLiteral("SessionTerminated") || MessageType == QStringLiteral("SessionConnectionDown")
                     || MessageType == QStringLiteral("SessionStartupFailure")) {
                setSessionRunning(false);
                emit finished();
            }
        }
    } break;
    default:
        break;
    }
    return true;
}

bool QBbgSessionMonitorWorker::start()
{
    if (sessionRunning())
        return false;
    return session()->startAsync();
}

QBbgSessionMonitorWorker::QBbgSessionMonitorWorker(const BloombergLP::blpapi::SessionOptions &option, QObject *parent)
    : QBbgAbstractWorker(option, parent)
{ }

void QBbgSessionMonitorWorker::handleResponseEvent(const BloombergLP::blpapi::Event &event, bool isFinal)
{
    Q_UNUSED(event)
    Q_UNUSED(isFinal)
    // No Op
    return;
}

void QBbgSessionMonitorWorker::setRequest(const QBbgRequestGroup &req)
{
    Q_UNUSED(req)
    // No Op
    return;
}

}

#endif // QBbg_OFFLINE
