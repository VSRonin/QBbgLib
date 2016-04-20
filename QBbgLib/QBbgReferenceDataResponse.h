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

#ifndef QBbgReferenceDataResponse_h__
#define QBbgReferenceDataResponse_h__
#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
#include <QList>
#include <QVariant>
namespace QBbgLib {
    class QBbgRequestResponseWorker;
    class QBbgReferenceDataResponsePrivate;
    /*! 
    \brief Response for static data
    \details The result can be either a single value or a table depending on the request
    */
    class QBBG_EXPORT QBbgReferenceDataResponse : public QBbgAbstractFieldResponse
    {
        Q_GADGET
        /*!
        \brief The number of rows in the tabular result
        \getter rows()
        */
        Q_PROPERTY(qint32 rows READ rows)
        /*!
        \brief The number of columns in the tabular result
        \getter columns()
        */
        Q_PROPERTY(qint32 columns READ columns)
        /*!
        \brief Whether the response has tabular results or not
        \getter hasTable()
        */
        Q_PROPERTY(bool hasTable READ hasTable)
        /*!
        \brief Whether the response has a single value or not
        \getter hasTable()
        */
        Q_PROPERTY(QVariant value READ value)
    private:
        Q_DECLARE_PRIVATE(QBbgReferenceDataResponse)
    public:
        //! Creates an empty response
    	QBbgReferenceDataResponse();
        //! Destructor
        virtual ~QBbgReferenceDataResponse();
        //! Creates a copy of another response
        QBbgReferenceDataResponse(const QBbgReferenceDataResponse& other);
        //! Copies another response
        virtual QBbgReferenceDataResponse& operator=(const QBbgReferenceDataResponse& other);
        /*!
        \brief Number of rows in the tabular result
        \details If hasTable() is false this will return 0
        */
        virtual qint32 rows() const;
        /*!
        \brief Number of columns in the tabular result
        \details If hasTable() is false this will return 0
        */
        virtual qint32 columns() const;
        /*!
        \brief Returns the result associated with a table cell
        \arg r The row index of the table
        \arg c The column index of the table
        \details If hasTable() is false or any index is out of range a null pointer will be returned
        */
        Q_INVOKABLE virtual const QBbgReferenceDataResponse* getTableValue(qint32 r, qint32 c) const;
        //! Checks if the response has tabular results
        virtual bool hasTable() const;
        //! Checks if the response has a single value
        virtual bool hasValue()const;
        //! Reimplemented from QBbgAbstractResponse::isEmpty()
        virtual bool isEmpty() const;
        /*!
        \brief Returns the single value of the result 
        \details If hasValue() is false this will return a null QVariant
        */
        virtual const QVariant& value() const;
    protected:
        QBbgReferenceDataResponse(QBbgReferenceDataResponsePrivate* dp);
        virtual void setValue(const QVariant& val, const QString& Header = QString());
        virtual void addValueRow(const QList<QVariant>& val, const QList<QString>& Headers = QList<QString>());
        virtual void clear();
        virtual void saveToStream(QDataStream& stream) const;
        virtual void loadFromStream(QDataStream& stream);

        friend class QBbgRequestResponseWorker;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgReferenceDataResponse);
#endif // QBbgReferenceDataResponse_h__