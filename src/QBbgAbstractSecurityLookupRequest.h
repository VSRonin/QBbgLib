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

#ifndef QBbgAbstractSecurityLookupRequest_h__
#define QBbgAbstractSecurityLookupRequest_h__
#include <QObject>
#include "QBbgAbstractRequest.h"
#include <qbbglib_global.h>
namespace QBbgLib {
class QBbgAbstractSecurityLookupRequest;
class QBbgAbstractSecurityLookupRequestPrivate;
}
namespace QBbgLib {

//! Base class for all requests sent to Bloomberg regarding looking up a security
class QBBGLIB_EXPORT QBbgAbstractSecurityLookupRequest : public QBbgAbstractRequest
{
    Q_GADGET
    /*!
    \brief The query associated with the request
    \getter query()
    \setter setQuery()
    */
    Q_PROPERTY(QString query READ query WRITE setQuery)
    /*!
    \brief The maximum number of results the request will bear
    \getter maxResults()
    \setter setMaxResults()
    */
    Q_PROPERTY(int maxResults READ maxResults WRITE setMaxResults)
protected:
    Q_DECLARE_PRIVATE(QBbgAbstractSecurityLookupRequest)
    QBbgAbstractSecurityLookupRequest(QBbgAbstractSecurityLookupRequestPrivate *d);
    QBbgAbstractSecurityLookupRequest() = delete;
    void saveToStream(QDataStream &stream) const override;
    void loadFromStream(QDataStream &stream) override;
    void applyRequest(QJsonObject& obj) const override =0;
public:
    //! Destructor
    virtual ~QBbgAbstractSecurityLookupRequest() = 0;
    //! Copies another request
    virtual QBbgAbstractSecurityLookupRequest &operator=(const QBbgAbstractSecurityLookupRequest &other);
    //! Returns the query associated with the request
    virtual const QString &query() const;
    //! Sets the query for the current request to the specified one
    virtual void setQuery(const QString &val);
    //! Returns the maximum number of results the request will bear
    virtual int maxResults() const;
    //! Sets the maximum number of results the request will bear
    virtual void setMaxResults(int val);

    //! Checks if the request is valid
    bool isValidReq() const override;
    //! Checks if two requests are identical
    virtual bool operator==(const QBbgAbstractSecurityLookupRequest &other) const;
};
}

#endif
