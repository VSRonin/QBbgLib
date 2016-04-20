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

#include "QBbgReferenceDataRequest.h"
#include "private/QBbgReferenceDataRequest_p.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgReferenceDataRequest::~QBbgReferenceDataRequest() = default;
    QBbgReferenceDataRequestPrivate::~QBbgReferenceDataRequestPrivate() = default;
    QBbgReferenceDataRequestPrivate::QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q)
        : QBbgAbstractFieldRequestPrivate(q, QBbgAbstractRequest::RequestType::ReferenceData)
        , m_UseUTCTime(false)
    {
    }
    QBbgReferenceDataRequestPrivate::QBbgReferenceDataRequestPrivate(QBbgReferenceDataRequest* q, const QBbgReferenceDataRequestPrivate& other)
        : QBbgAbstractFieldRequestPrivate(q, other)
        , m_UseUTCTime(other.m_UseUTCTime)
    {
    }
    QBbgReferenceDataRequestPrivate& QBbgReferenceDataRequestPrivate::operator=(const QBbgReferenceDataRequestPrivate& other)
    {
        QBbgAbstractFieldRequestPrivate::operator=(other);
        m_UseUTCTime = other.m_UseUTCTime;
        return *this;
    }
    QBbgReferenceDataRequest::QBbgReferenceDataRequest()
        :QBbgAbstractFieldRequest(new QBbgReferenceDataRequestPrivate(this))
    {}
    QBbgReferenceDataRequest::QBbgReferenceDataRequest(QBbgReferenceDataRequestPrivate* d)
        : QBbgAbstractFieldRequest(d)
    {}
    QBbgReferenceDataRequest::QBbgReferenceDataRequest(const QBbgReferenceDataRequest& a)
        : QBbgAbstractFieldRequest(new QBbgReferenceDataRequestPrivate(this, *(a.d_func())))
    {}

    QBbgReferenceDataRequest& QBbgReferenceDataRequest::operator=(const QBbgReferenceDataRequest& a)
    {
        Q_D(QBbgReferenceDataRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
    bool QBbgReferenceDataRequest::operator==(const QBbgReferenceDataRequest& a) const
    {
        Q_D(const QBbgReferenceDataRequest);
        return 
            d->m_UseUTCTime == a.d_func()->m_UseUTCTime 
            && QBbgAbstractFieldRequest::operator==(a)
            ;
    }
    void QBbgReferenceDataRequest::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgReferenceDataRequest);
        QBbgAbstractFieldRequest::saveToStream(stream);
        stream << d->m_UseUTCTime;
    }

    void QBbgReferenceDataRequest::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgReferenceDataRequest);
        QBbgAbstractFieldRequest::loadFromStream(stream);
        stream >> d->m_UseUTCTime;
    }
    void QBbgReferenceDataRequest::setUseUTCtime(bool a)
    {
        Q_D(QBbgReferenceDataRequest);
        d->m_UseUTCTime = a;
    }
    bool QBbgReferenceDataRequest::useUTCtime() const
    {
        Q_D(const QBbgReferenceDataRequest);
        return d->m_UseUTCTime;
    }
    void QBbgReferenceDataRequest::setSecurity(const QBbgSecurity& val)
    {
        if (val.extension() != QBbgSecurity::Client) {
            QBbgAbstractFieldRequest::setSecurity(val);
        }
        else {
            QBbgAbstractRequest::setSecurity(QBbgSecurity());
        }
    }

}
