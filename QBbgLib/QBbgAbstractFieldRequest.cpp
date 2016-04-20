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

#include "QBbgAbstractFieldRequest.h"
#include "private/QBbgAbstractFieldRequest_p.h"
#include "QBbgOverride.h"
#include <QList> 
#include <QDataStream>
#include <QHash>
namespace QBbgLib {
    QBbgAbstractFieldRequest::~QBbgAbstractFieldRequest() = default;
    QBbgAbstractFieldRequestPrivate::~QBbgAbstractFieldRequestPrivate() = default;
    void QBbgAbstractFieldRequest::setField(const QString& val)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Field = val.simplified().toUpper();
        d->m_Field.replace(QChar(' '), QChar('_'));
    }
    QBbgAbstractFieldRequestPrivate::QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, QBbgAbstractRequest::RequestType typ)
        : QBbgAbstractRequestPrivate(q,typ)
    {}
    QBbgAbstractFieldRequestPrivate::QBbgAbstractFieldRequestPrivate(QBbgAbstractFieldRequest* q, const QBbgAbstractFieldRequestPrivate& a)
        : QBbgAbstractRequestPrivate(q,a)
        , m_Field(a.m_Field)
        , m_Overrides(a.m_Overrides)
    {}
    QBbgAbstractFieldRequestPrivate& QBbgAbstractFieldRequestPrivate::operator=(const QBbgAbstractFieldRequestPrivate& a)
    {
        QBbgAbstractRequestPrivate::operator=(a);
        m_Field = a.m_Field;
        m_Overrides = a.m_Overrides;
        return *this;
    }
    void QBbgAbstractFieldRequest::saveToStream(QDataStream& stream) const
    {
        Q_D(const QBbgAbstractFieldRequest);
        QBbgAbstractRequest::saveToStream(stream);
        stream << d->m_Field << d->m_Overrides;
    }

    void QBbgAbstractFieldRequest::loadFromStream(QDataStream& stream)
    {
        Q_D(QBbgAbstractFieldRequest);
        QBbgAbstractRequest::loadFromStream(stream);
        stream >> d->m_Field >> d->m_Overrides;
    }
    void QBbgAbstractFieldRequest::setOverrides(const QBbgOverride& Overr)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Overrides = Overr;
    }
    void QBbgAbstractFieldRequest::clearOverrides()
    {
        Q_D(QBbgAbstractFieldRequest);
        d->m_Overrides.clear();
    }
    bool QBbgAbstractFieldRequest::sameOverrides(const QBbgAbstractFieldRequest& a)const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->SameOverrides(*(a.d_func()));
    }
    bool QBbgAbstractFieldRequestPrivate::SameOverrides(const QBbgAbstractFieldRequestPrivate& a)const
    {
        return m_Overrides == a.m_Overrides;
    }

    bool QBbgAbstractFieldRequest::isValidReq() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return
            !d->m_Field.isEmpty()
            && d->m_Security.isValid()
            && (static_cast<qint32>(d->m_RqType) & FirstFielded)
            ;
    }
    bool QBbgAbstractFieldRequest::operator==(const QBbgAbstractFieldRequest& a) const
    {
        Q_D(const QBbgAbstractFieldRequest);
        if (
            !QBbgAbstractRequest::operator==(a)
            || (d->m_Field != a.d_func()->m_Field)
            )
            return false;
        return d->m_Overrides == a.d_func()->m_Overrides;
    }
    const QString& QBbgAbstractFieldRequest::field() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->m_Field;
    }
    const QBbgOverride& QBbgAbstractFieldRequest::overrides() const
    {
        Q_D(const QBbgAbstractFieldRequest);
        return d->m_Overrides;
    }

    QBbgAbstractFieldRequest::QBbgAbstractFieldRequest(QBbgAbstractFieldRequestPrivate* d)
        : QBbgAbstractRequest(d)
    {}

    QBbgAbstractFieldRequest& QBbgAbstractFieldRequest::operator=(const QBbgAbstractFieldRequest& a)
    {
        Q_D(QBbgAbstractFieldRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
}
