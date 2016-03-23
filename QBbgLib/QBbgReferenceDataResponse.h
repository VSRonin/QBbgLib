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

#ifndef QBbgReferenceDataResponse_h__
#define QBbgReferenceDataResponse_h__
#include "QBbgAbstractFieldResponse.h"
#include "QBbgProjectGlobals.h"
#include <QList>
class QVariant;
namespace QBbgLib {
    class QBbgRequestResponseWorker;
    class QBbgReferenceDataResponsePrivate;
    class QBBG_EXPORT QBbgReferenceDataResponse : public QBbgAbstractFieldResponse
    {
    private:
        Q_DECLARE_PRIVATE(QBbgReferenceDataResponse)
    public:
    	QBbgReferenceDataResponse();
        virtual ~QBbgReferenceDataResponse();
        QBbgReferenceDataResponse(const QBbgReferenceDataResponse& other);
        virtual QBbgReferenceDataResponse& operator=(const QBbgReferenceDataResponse& other);
        virtual qint32 rows() const;
        virtual qint32 columns() const;
        virtual const QBbgReferenceDataResponse* getTableValue(qint32 r, qint32 c) const;
        virtual bool hasTable() const;
        virtual bool hasValue()const;
        virtual bool isEmpty() const;
        virtual const QVariant& value() const;
    protected:
        QBbgReferenceDataResponse(QBbgReferenceDataResponsePrivate* dp);
        virtual void setValue(const QVariant& val, const QString& Header = QString());
        virtual void addValueRow(const QList<QVariant>& val, const QList<QString>& Headers = QList<QString>());
        virtual void clear();

        friend class QBbgRequestResponseWorker;
    };
}
Q_DECLARE_METATYPE(QBbgLib::QBbgReferenceDataResponse);
#endif // QBbgReferenceDataResponse_h__