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
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef QBbgSecurity_h__
#define QBbgSecurity_h__
#include <QString>
#include <QMetaType>
#include "QBbgProjectGlobals.h"
class QDataStream;
namespace QBbgLib { class QBbgSecurity; }
//! Write a security into a QDataStream
QBBG_EXPORT QDataStream& operator<<(QDataStream& stream, const QBbgLib::QBbgSecurity& obj);
//! Read a security from a QDataStream
QBBG_EXPORT QDataStream& operator>>(QDataStream& stream, QBbgLib::QBbgSecurity& obj);
namespace QBbgLib {
    class QBbgSecurityPrivate;
    /*!
    \brief A Bloomberg Security
    \details This class represents a security.<br/>It includes both the name, the extension and, optionally, the price source and public exchange
    */
    class QBBG_EXPORT QBbgSecurity
    {
        Q_GADGET
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString fullName READ fullName)
        Q_PROPERTY(bool isValid READ isValid)
        Q_PROPERTY(YellowKeys extension READ extension WRITE setExtension)
        Q_PROPERTY(QString pricingSource READ pricingSource WRITE setPricingSource)
        Q_PROPERTY(QString exchange READ exchange WRITE setExchange)
        
    private:
        enum { FirstPrefix=0x400 };
    public:
        /*!
        \brief Enumeration describing a security extensions
        \details Represents either a yellow key or an identifier used for the security
        */
        enum YellowKeys
        {
            Invalid = -1
            //Proper yellow keys
            , Govt
            , Corp
            , Mtge
            , MMkt
            , Muni
            , Pfd
            , Equity
            , Comdty
            , Index
            , Curncy
            , Client
            //Prefixes
            //, ticker // still needs another yellow key
            , cusip = FirstPrefix
            , wpk
            , isin
            , buid
            , sedol1
            , sedol2
            , sicovam
            , common
            , bsid
            , svm
            , cins
            , cats
            , bbgid
        };
        Q_ENUM(YellowKeys)
    private:
        Q_DECLARE_PRIVATE(QBbgSecurity)
        QBbgSecurityPrivate* d_ptr;
    protected:
        //! Writes the security data to the QDataStream
        virtual void saveToStream(QDataStream& stream) const;
        //! Reads the security data from the QDataStream
        virtual void loadFromStream(QDataStream& stream);
    public:
        /*!
        Creates a null security
        */
    	QBbgSecurity();
        /*!
        \brief Creates a security based on its string representation
        \details If the input is invalid, a null security will be created
        \arg SecString Examples of valid strings are IBM US Equity ,  /isin/XS1372839214
        */
        QBbgSecurity(QString SecString);
        /*!
        \brief Creates a security based on its name and a security extension
        \details If the input is invalid, a null security will be created
        \arg SecName The security name without extension
        \arg SecKey The security extension to use
        */
        QBbgSecurity(const QString& SecName, YellowKeys SecKey);
        //! Creates a copy of another security
        QBbgSecurity(const QBbgSecurity& other);
        //! Copy another security
        QBbgSecurity& operator=(const QBbgSecurity& other);
        //! Destructor
    	virtual ~QBbgSecurity();
        //! The security Name
        const QString& name() const;
        //! Set the security name
        void setName(const QString& val);
        //! The public exchange for the security
        const QString& exchange() const;
        //! Set the public exchange for the security
        void setExchange(const QString& val);
        //! The price source to use
        const QString& pricingSource() const;
        //! Set the price source to use
        void setPricingSource(const QString& val);
        //! The security Extension
        YellowKeys extension() const;
        //! Set the security Extension
        void setExtension(YellowKeys val);
        //! Check is the security is valid
        bool isValid() const;
        //! Returns the fully decorated security name including price source, exchange and extension
        QString fullName() const;
        //! Check if two securities are the same
        bool operator==(const QBbgSecurity& other) const;
        //! Check if two securities are different
        bool operator!=(const QBbgSecurity& other) const;
        //! Converts a security extension to its string representation
        Q_INVOKABLE static QString yellowKeyToString(YellowKeys a);
        //! Converts a string representation to a security extension
        Q_INVOKABLE static YellowKeys stringToYellowKey(QString a);
        friend QDataStream& ::operator<<(QDataStream& stream, const QBbgSecurity& obj);
        friend QDataStream& ::operator>>(QDataStream& stream, QBbgSecurity& obj);
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgSecurity);
/*! 
\brief Allows QBbgSecurity to be used as a key of a QHash
\relates QBbgLib::QBbgSecurity
*/
QBBG_EXPORT uint qHash(const QBbgLib::QBbgSecurity&key, uint seed);

#endif // QBbgSecurity_h__
