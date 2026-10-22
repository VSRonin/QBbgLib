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

#ifndef QBbgInstrumentLookupRequest_h__
#define QBbgInstrumentLookupRequest_h__
#include <QObject>
#include "QBbgAbstractSecurityLookupRequest.h"
#include "QBbgSecurity.h"
#include <qbbglib_global.h>
namespace QBbgLib {
class QBbgInstrumentLookupRequest;
class QBbgInstrumentLookupRequestPrivate;
}
namespace QBbgLib {

//! Base class for all requests sent to Bloomberg regarding looking up a security
class QBBGLIB_EXPORT QBbgInstrumentLookupRequest : public QBbgAbstractSecurityLookupRequest
{
    Q_GADGET
    /*!
    \brief Filters the serach results based on a specific yellow key
    \getter yellowKeyFilter()
    \setter setYellowKeyFilter()
    */
    Q_PROPERTY(YellowKeyFilter yellowKeyFilter READ yellowKeyFilter WRITE setYellowKeyFilter)
    /*!
    \brief Filters the serach results based on a specific language
    \getter languageOverride()
    \setter setLanguageOverride()
    */
    Q_PROPERTY(LanguageOverride languageOverride READ languageOverride WRITE setLanguageOverride)
    Q_DECLARE_PRIVATE(QBbgInstrumentLookupRequest)
public:
    enum class YellowKeyFilter : qint16 {
        None = -1
        ,
        Govt /*!< Government Bond */
        ,
        Corp /*!< Corporate Bond */
        ,
        Mtge /*!< Asset Backed Security */
        ,
        MMkt /*!< Money Market */
        ,
        Muni /*!< Municipal Bond */
        ,
        Pfd /*!< Preferred */
        ,
        Equity /*!< Equity */
        ,
        Comdty /*!< Commodity */
        ,
        Index /*!< Index */
        ,
        Curncy /*!< Currency */
        ,
        Client /*!< Portfolio */
    };
    Q_ENUM(YellowKeyFilter)
    enum class LanguageOverride : qint16{
        None = -1,
        English,
        Kanji,
        French,
        German,
        Spanish,
        Portuguese,
        Italian,
        ChineseTraditional,
        Korean,
        ChineseSimplified,
        Russian
    };
    Q_ENUM(LanguageOverride)

    //! Constructor
    QBbgInstrumentLookupRequest();
    //! Copy Constructor
    QBbgInstrumentLookupRequest(const QBbgInstrumentLookupRequest& other);
    //! Destructor
    virtual ~QBbgInstrumentLookupRequest();
    //! Copies another request
    virtual QBbgInstrumentLookupRequest &operator=(const QBbgInstrumentLookupRequest &other);
    //! Gets the filter based on yellow keys
    YellowKeyFilter yellowKeyFilter() const;
    //! Sets the filter based on yellow keys
    void setYellowKeyFilter(YellowKeyFilter val);
    //! Gets the filter based on language
    LanguageOverride languageOverride() const;
    //! Gets the filter based on language
    void setLanguageOverride(LanguageOverride val);
    //! Checks if two requests are identical
    virtual bool operator==(const QBbgInstrumentLookupRequest &other) const;
    //! Converts a security yellow key to a filter
    static YellowKeyFilter yellowKeyFilterFromYellowKeys(QBbgSecurity::YellowKeys val);
    //! Converts a filter to a security yellow key
    static QBbgSecurity::YellowKeys yellowKeysFromYellowKeyFilter(YellowKeyFilter val);
protected:
    QBbgInstrumentLookupRequest(QBbgInstrumentLookupRequestPrivate *d);
    static QString yellowKeyFilterString(YellowKeyFilter val);
    static QString languageOverrideString(LanguageOverride val);
    void saveToStream(QDataStream &stream) const override;
    void loadFromStream(QDataStream &stream) override;
    void applyRequest(QJsonObject& obj) const override;
};
}

#endif
