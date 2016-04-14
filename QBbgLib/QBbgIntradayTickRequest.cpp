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

#include "QBbgIntradayTickRequest.h"
#include "private/QBbgIntradayTickRequest_p.h"
namespace QBbgLib {
    QBbgIntradayTickRequest::~QBbgIntradayTickRequest() = default;
    QBbgIntradayTickRequestPrivate::~QBbgIntradayTickRequestPrivate() = default;
    QBbgIntradayTickRequestPrivate::QBbgIntradayTickRequestPrivate(QBbgIntradayTickRequest* q)
        : QBbgAbstractIntradayRequestPrivate(q, QBbgAbstractRequest::RequestType::IntraDayTick)
        , m_includeConditionCodes(false)
        , m_includeNonPlottable(false)
        , m_includeExchangeCodes(false)
        , m_includeBrokerCodes(false)
        , m_includeRpsCodes(false)
        , m_includeBicMicCodes(false)
    {}
    QBbgIntradayTickRequestPrivate::QBbgIntradayTickRequestPrivate(QBbgIntradayTickRequest* q, const QBbgIntradayTickRequestPrivate& other)
        : QBbgAbstractIntradayRequestPrivate(q, other)
        , m_includeConditionCodes(other.m_includeConditionCodes)
        , m_includeNonPlottable(other.m_includeNonPlottable)
        , m_includeExchangeCodes(other.m_includeExchangeCodes)
        , m_includeBrokerCodes(other.m_includeBrokerCodes)
        , m_includeRpsCodes(other.m_includeRpsCodes)
        , m_includeBicMicCodes(other.m_includeBicMicCodes)
    {}
    QBbgIntradayTickRequestPrivate& QBbgIntradayTickRequestPrivate::operator=(const QBbgIntradayTickRequestPrivate& other)
    {
        QBbgAbstractIntradayRequestPrivate::operator=(other);
        m_includeConditionCodes = other.m_includeConditionCodes;
        m_includeNonPlottable = other.m_includeNonPlottable;
        m_includeExchangeCodes = other.m_includeExchangeCodes;
        m_includeBrokerCodes = other.m_includeBrokerCodes;
        m_includeRpsCodes = other.m_includeRpsCodes;
        m_includeBicMicCodes = other.m_includeBicMicCodes;
        return *this;
    }
    QBbgIntradayTickRequest::QBbgIntradayTickRequest()
        :QBbgAbstractIntradayRequest(new QBbgIntradayTickRequestPrivate(this))
    {}
    QBbgIntradayTickRequest::QBbgIntradayTickRequest(QBbgIntradayTickRequestPrivate* d)
        : QBbgAbstractIntradayRequest(d)
    {}
    QBbgIntradayTickRequest::QBbgIntradayTickRequest(const QBbgIntradayTickRequest& a)
        : QBbgAbstractIntradayRequest(new QBbgIntradayTickRequestPrivate(this, *(a.d_func())))
    {}

    bool QBbgIntradayTickRequest::sameOptions(const QBbgIntradayTickRequest& other) const
    {
        Q_D(const QBbgIntradayTickRequest);
        return
            d->m_includeConditionCodes == other.d_func()->m_includeConditionCodes
            && d->m_includeNonPlottable == other.d_func()->m_includeNonPlottable
            && d->m_includeExchangeCodes == other.d_func()->m_includeExchangeCodes
            && d->m_includeBrokerCodes == other.d_func()->m_includeBrokerCodes
            && d->m_includeRpsCodes == other.d_func()->m_includeRpsCodes
            && d->m_includeBicMicCodes == other.d_func()->m_includeBicMicCodes
            && d->m_startDate == other.d_func()->m_startDate
            && d->m_endDate == other.d_func()->m_endDate
            ;
    }

    QBbgIntradayTickRequest& QBbgIntradayTickRequest::operator=(const QBbgIntradayTickRequest& a)
    {
        Q_D(QBbgIntradayTickRequest);
        d->operator=(*(a.d_func()));
        return *this;
    }
    bool QBbgIntradayTickRequest::operator==(const QBbgIntradayTickRequest& a) const
    {
        Q_D(const QBbgIntradayTickRequest);
        return
            QBbgAbstractIntradayRequest::operator==(a)
            && d->m_includeConditionCodes == a.d_func()->m_includeConditionCodes
            && d->m_includeNonPlottable == a.d_func()->m_includeNonPlottable
            && d->m_includeExchangeCodes == a.d_func()->m_includeExchangeCodes
            && d->m_includeBrokerCodes == a.d_func()->m_includeBrokerCodes
            && d->m_includeRpsCodes == a.d_func()->m_includeRpsCodes
            && d->m_includeBicMicCodes == a.d_func()->m_includeBicMicCodes
            ;
    }

    bool QBbgIntradayTickRequest::includeBicMicCodes() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeBicMicCodes;
    }

    void QBbgIntradayTickRequest::setIncludeBicMicCodes(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeBicMicCodes = val;
    }

    bool QBbgIntradayTickRequest::includeRpsCodes() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeRpsCodes;
    }

    void QBbgIntradayTickRequest::setIncludeRpsCodes(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeRpsCodes = val;
    }

    bool QBbgIntradayTickRequest::includeBrokerCodes() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeBrokerCodes;
    }

    void QBbgIntradayTickRequest::setIncludeBrokerCodes(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeBrokerCodes = val;
    }

    bool QBbgIntradayTickRequest::includeExchangeCodes() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeExchangeCodes;
    }

    void QBbgIntradayTickRequest::setIncludeExchangeCodes(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeExchangeCodes = val;
    }

    bool QBbgIntradayTickRequest::includeNonPlottable() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeNonPlottable;
    }

    void QBbgIntradayTickRequest::setIncludeNonPlottable(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeNonPlottable = val;
    }

    bool QBbgIntradayTickRequest::includeConditionCodes() const
    {
        Q_D(const QBbgIntradayTickRequest);
        return d->m_includeConditionCodes;
    }

    void QBbgIntradayTickRequest::setIncludeConditionCodes(bool val)
    {
        Q_D(QBbgIntradayTickRequest);
        d->m_includeConditionCodes = val;
    }
}
