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

#ifndef QBbgOverride_h__
#define QBbgOverride_h__
#include <QString>
#include <QList>
#include <QObject>
#include "QBbgProjectGlobals.h"
class QDate;
class QTime;
class QVariant;
namespace BloombergLP { namespace blpapi { class Request; } }
namespace QBbgLib {
    class QBbgOverridePrivate;
    class QBbgRequestResponseWorker;
    /*!
    \brief A set of overrides
    \details This class is used to describe a series of overrides to attach to a security.<br/>
    Each override is a Name-Value pair describing the field to override and the value of that override<br/>
    The overrides names will be automatically normalized as all uppercase and with spaces replaced with underscore
    \warning If you set the same overrides twice using different names (e.g. if ID_ISIN and ID005 are both set to different values), there is now way of telling which will actually be applied
    */
    class QBBG_EXPORT QBbgOverride
    {
        Q_GADGET
        Q_PROPERTY(qint32 size READ size)
        Q_PROPERTY(bool isEmpty READ isEmpty)
        Q_DECLARE_PRIVATE(QBbgOverride)
    public:
        //! Construct an empty set of overrides
        QBbgOverride();
        //! Creates a copy of another set of overrides
        QBbgOverride(const QBbgOverride& other);
        //! Copies another set of overrides
        virtual QBbgOverride& operator=(const QBbgOverride& other);
        //! Destructor
        virtual ~QBbgOverride();
        //! Removes all overrides from the set
        Q_INVOKABLE virtual void clear();
        //! Returns the number of overrides set
        virtual qint32 size();
        /*!
        \brief Returns true if the set contains an overrides with the specific name
        \arg Name The name of the field to check
        \note This cannot recognize codes and explicit names e.g. ID_ISIN and ID005 will not be recognized as the same overrides
        */
        Q_INVOKABLE virtual bool contains(const QString& Name) const;
        //! Returns true if the set contains no overrides
        virtual bool isEmpty() const;
        /*! 
        \brief Sets an override
        \arg Name The field name to override
        \arg val The value to override with
        */
        Q_INVOKABLE virtual void setOverride(const QString& Name, const QVariant& val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, const QDate& val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, const QTime& val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, double val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, qint32 val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, qint64 val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, quint32 val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(const QString& Name, quint64 val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(QString Name, const QString& val);
        //! Overloaded version of setOverride(const QString&, const QVariant&)
        virtual void setOverride(QString Name, const char *const val);
        /*! 
        \brief Returns the override value associated with the field name
        \details Returns a null string if the override was not set
        */
        Q_INVOKABLE virtual QString overrideValue(const QString& Name) const;
        //! Returns a list of all field names overridden
        Q_INVOKABLE virtual QList<QString> getNames() const;
        //! Same as getNames
        virtual QList<QString> getKeys() const;
        //! Checks if two sets of overrides are identical
        virtual bool operator==(const QBbgOverride& other)const;
        //! Checks if two sets of overrides are different
        virtual bool operator!=(const QBbgOverride& other)const;
        /*!
        \brief Returns a reference to the override value associated with the field name
        \note If the set does not contain the field name it will be added to the set with a null string as value
        */
        virtual QString& operator[](const QString& Name);
        //! Same as overrideValue
        virtual QString operator[](const QString& Name) const;
    protected:
        void addOverrideToRequest(BloombergLP::blpapi::Request& rq) const;
        QBbgOverride(QBbgOverridePrivate* d);
        QBbgOverridePrivate* d_ptr;

        friend class QBbgRequestResponseWorker;
    };
}
#endif // QBbgOverride_h__