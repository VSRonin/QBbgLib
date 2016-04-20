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

#include "QBbgAbstractFieldResponse.h"
#include "private/QBbgAbstractFieldResponse_p.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgAbstractFieldResponse::~QBbgAbstractFieldResponse() = default;
    QBbgAbstractFieldResponsePrivate::~QBbgAbstractFieldResponsePrivate() = default;
    QBbgAbstractFieldResponsePrivate::QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, QBbgAbstractResponse::ResponseType typ)
        :QBbgAbstractResponsePrivate(q,typ)
    {}

    QBbgAbstractFieldResponsePrivate::QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, const QBbgAbstractFieldResponsePrivate& other)
        : QBbgAbstractResponsePrivate(q, other)
        , m_Header(other.m_Header)
    {}
    QBbgAbstractFieldResponsePrivate& QBbgAbstractFieldResponsePrivate::operator=(const QBbgAbstractFieldResponsePrivate& other)
    {
        QBbgAbstractResponsePrivate::operator=(other);
        m_Header = other.m_Header;
        return *this;
    }
 

    QBbgAbstractFieldResponse::QBbgAbstractFieldResponse(QBbgAbstractFieldResponsePrivate* d)
        : QBbgAbstractResponse(d)
    {}
    QBbgAbstractFieldResponse& QBbgAbstractFieldResponse::operator=(const QBbgAbstractFieldResponse& a)
    {
        Q_D(QBbgAbstractFieldResponse);
        d->operator=(*(a.d_func()));
        return *this;
    }
    const QString& QBbgAbstractFieldResponse::header() const
    {
        Q_D(const QBbgAbstractFieldResponse);
        return d->m_Header;
    }
    void QBbgAbstractFieldResponse::setHeader(const QString& Header)
    {
        Q_D(QBbgAbstractFieldResponse);
        d->m_Header=Header;
    }
    void QBbgAbstractFieldResponse::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgAbstractFieldResponse);
        QBbgAbstractResponse::saveToStream(stream);
        stream << d->m_Header;
    }

    void QBbgAbstractFieldResponse::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgAbstractFieldResponse);
        QBbgAbstractResponse::loadFromStream(stream);
        stream << d->m_Header;
    }
}
