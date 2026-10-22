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

#ifndef QBbgInstrumentLookupResponse_h__
#define QBbgInstrumentLookupResponse_h__
#include "QBbgAbstractResponse.h"
#include <QDate>
#include <QList>

namespace QBbgLib {
class QBbgInstrumentLookupResponsePrivate;
//! A response for looking up a security
class QBBGLIB_EXPORT QBbgInstrumentLookupResponse : public QBbgAbstractResponse
{
    Q_GADGET
    /*!
    \brief Number of results
    \getter size()
    */
    Q_PROPERTY(int size READ size)
    /*!
    \brief All secutities found
    \getter secutities()
    */
    Q_PROPERTY(QStringList secutities READ secutities)
    /*!
    \brief All descriptions found
    \getter descriptions()
    */
    Q_PROPERTY(QStringList descriptions READ descriptions)
private:
    Q_DECLARE_PRIVATE(QBbgInstrumentLookupResponse)
public:
    //! Destructor
    virtual ~QBbgInstrumentLookupResponse();
    //! Creates an empty security lookup response
    QBbgInstrumentLookupResponse();
    //! Creates a copy of another security lookup response
    QBbgInstrumentLookupResponse(const QBbgInstrumentLookupResponse &other);
    //! Copies another security lookup response
    virtual QBbgInstrumentLookupResponse &operator=(const QBbgInstrumentLookupResponse &other);
    //! Number of values in the series
    virtual int size() const;
    //! \reimp
    bool isEmpty() const override;
    //! Returns the secutity for the selected index of results
    Q_INVOKABLE virtual QString secutity(int index) const;
    //! Returns the description for the selected index of results
    Q_INVOKABLE virtual QString description(int index) const;
    //! Returns all secutities found
    virtual const QStringList& secutities() const;
    //! Returns all descriptions found
    virtual const QStringList& descriptions() const;

protected:
    QBbgInstrumentLookupResponse(QBbgInstrumentLookupResponsePrivate *dp);
    virtual void addValue(const QString &sec, const QString &desc);
    virtual void clear();
    void saveToStream(QDataStream &stream) const override;
    void loadFromStream(QDataStream &stream) override;
    bool loadFromJsonResponse(const QJsonObject& obj) override;
    friend class QBbgRequestResponseWorker;
};
}
// Q_DECLARE_METATYPE(QBbgLib::QBbgInstrumentLookupResponse);
#endif
