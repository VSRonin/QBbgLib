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

#ifndef QBbgIntradayTickRequest_h__
#define QBbgIntradayTickRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractIntradayRequest.h"
#include <QObject>
namespace QBbgLib {
    class QBbgRequestGroupPrivate;
    class QBbgIntradayTickRequestPrivate;
    class QBBG_EXPORT QBbgIntradayTickRequest : public QBbgAbstractIntradayRequest
    {
        Q_GADGET
        Q_PROPERTY(bool includeBicMicCodes READ includeBicMicCodes WRITE setIncludeBicMicCodes)
        Q_PROPERTY(bool includeRpsCodes READ includeRpsCodes WRITE setIncludeRpsCodes)
        Q_PROPERTY(bool includeBrokerCodes READ includeBrokerCodes WRITE setIncludeBrokerCodes)
        Q_PROPERTY(bool includeExchangeCodes READ includeExchangeCodes WRITE setIncludeExchangeCodes)
        Q_PROPERTY(bool includeNonPlottable READ includeNonPlottable WRITE setIncludeNonPlottable)
        Q_PROPERTY(bool includeConditionCodes READ includeConditionCodes WRITE setIncludeConditionCodes)
        Q_DECLARE_PRIVATE(QBbgIntradayTickRequest)
    public:
        //! Destructor
        virtual ~QBbgIntradayTickRequest();
        //! Creates an empty intraday tick request
        QBbgIntradayTickRequest();
        //! Creates a copy of a intraday tick request
        QBbgIntradayTickRequest(const QBbgIntradayTickRequest& a);
        //! Copies another intraday tick request
        virtual QBbgIntradayTickRequest& operator=(const QBbgIntradayTickRequest& a);
        //! Checks if two requests are identical
        virtual bool operator==(const QBbgIntradayTickRequest& a) const;
        bool includeBicMicCodes() const;
        void setIncludeBicMicCodes(bool val);
        bool includeRpsCodes() const;
        void setIncludeRpsCodes(bool val);
        bool includeBrokerCodes() const;
        void setIncludeBrokerCodes(bool val);
        bool includeExchangeCodes() const;
        void setIncludeExchangeCodes(bool val);
        bool includeNonPlottable() const;
        void setIncludeNonPlottable(bool val);
        bool includeConditionCodes() const;
        void setIncludeConditionCodes(bool val);
    protected:
        QBbgIntradayTickRequest(QBbgIntradayTickRequestPrivate* d);
        bool sameOptions(const QBbgIntradayTickRequest& other) const;
        friend class QBbgRequestGroupPrivate;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgIntradayTickRequest);
#endif // QBbgIntradayTickRequest_h__