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
    //! Enables retrieval of tick-by-tick history
    class QBBG_EXPORT QBbgIntradayTickRequest : public QBbgAbstractIntradayRequest
    {
        Q_GADGET
        /*!
        \brief Include bank or market identifier code
        \details The BIC, or Bank Identifier Code, as a 4-character unique identifier for each bank that executed and reported the OTC trade, as required by MiFID.<br/>
        BICs are assigned and maintained by SWIFT (Society for Worldwide Interbank Financial Telecommunication).<br/>
        The MIC is the Market Identifier Code, and this indicates the venue on which the trade was executed.
        \getter includeBicMicCodes()
        \setter setIncludeBicMicCodes()
        */
        Q_PROPERTY(bool includeBicMicCodes READ includeBicMicCodes WRITE setIncludeBicMicCodes)
        /*!
        \brief Include transaction codes
        \details The Reporting Party Side. The following values appear:<br/>
        -B: A customer transaction where the dealer purchases securities from the customer.<br/>
        -S: A customer transaction where the dealer sells securities to the customer.<br/>
        -D: An inter-dealer transaction (always from the sell side).<br/>
        \getter includeRpsCodes()
        \setter setIncludeRpsCodes()
        */
        Q_PROPERTY(bool includeRpsCodes READ includeRpsCodes WRITE setIncludeRpsCodes)
        /*!
        \brief Include the broker codes of the trade
        \details The broker code for Canadian, Finnish, Mexican, Philippine, and Swedish equities only.<br/>
        The Market Maker Lookup screen, MMTK<GO>, displays further information on market makers and their corresponding codes.
        \getter includeBrokerCodes()
        \setter setIncludeBrokerCodes()
        */
        Q_PROPERTY(bool includeBrokerCodes READ includeBrokerCodes WRITE setIncludeBrokerCodes)
        /*!
        \brief Include the exchange code of the trade
        \details The exchange code where this tick originated.<br/>
        Review QR<GO> for more information.
        \getter includeExchangeCodes()
        \setter setIncludeExchangeCodes()
        */
        Q_PROPERTY(bool includeExchangeCodes READ includeExchangeCodes WRITE setIncludeExchangeCodes)
        /*!
        \brief Include ticks in the response that have condition codes
        \getter includeNonPlottable()
        \setter setIncludeNonPlottable()
        */
        Q_PROPERTY(bool includeNonPlottable READ includeNonPlottable WRITE setIncludeNonPlottable)
        /*!
        \brief Include any condition codes that may be associated to a tick, which identifies extraordinary trading and quoting circumstances.
        \details A comma delimited list of exchange condition codes associated with the event.<br/>
        Review QR<GO> for more information on each code eturned.
        \getter includeConditionCodes()
        \setter setIncludeConditionCodes()
        */
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
        /*!
        \sa includeBicMicCodes
        */
        bool includeBicMicCodes() const;
        /*!
        \sa includeBicMicCodes
        */
        void setIncludeBicMicCodes(bool val);
        /*!
        \sa includeRpsCodes
        */
        bool includeRpsCodes() const;
        /*!
        \sa includeRpsCodes
        */
        void setIncludeRpsCodes(bool val);
        /*!
        \sa includeBrokerCodes
        */
        bool includeBrokerCodes() const;
        /*!
        \sa includeBrokerCodes
        */
        void setIncludeBrokerCodes(bool val);
        /*!
        \sa includeExchangeCodes
        */
        bool includeExchangeCodes() const;
        /*!
        \sa includeExchangeCodes
        */
        void setIncludeExchangeCodes(bool val);
        /*!
        \sa includeNonPlottable
        */
        bool includeNonPlottable() const;
        /*!
        \sa includeNonPlottable
        */
        void setIncludeNonPlottable(bool val);
        /*!
        \sa includeConditionCodes
        */
        bool includeConditionCodes() const;
        /*!
        \sa includeConditionCodes
        */
        void setIncludeConditionCodes(bool val);
    protected:
        QBbgIntradayTickRequest(QBbgIntradayTickRequestPrivate* d);
        bool sameOptions(const QBbgIntradayTickRequest& other) const;
        friend class QBbgRequestGroupPrivate;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgIntradayTickRequest);
#endif // QBbgIntradayTickRequest_h__