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

#ifndef QbbgReferenceDataRequest_h__
#define QbbgReferenceDataRequest_h__
#include "QBbgProjectGlobals.h"
#include "QBbgAbstractFieldRequest.h"
#include <QObject>
namespace QBbgLib {
    class QBbgReferenceDataRequestPrivate;
    /*!
    \brief A reference data request
    \details This class can be used to query current data from Bloomberg.<br/>
    Both single values and tables can be retrieved using this request.<br/>
    This is equivalent to BDP() and BDS() bloomberg functions in excel.
    \note For request with securities having the QBbgSecurity::Client extension, use QBbgPortfolioDataRequest instead
    */
    class QBBG_EXPORT QBbgReferenceDataRequest : public QBbgAbstractFieldRequest
    {
        Q_GADGET
        /*!
        \brief The security associated with the request
        \getter security()
        \setter setSecurity()
        */
        Q_PROPERTY(QBbgSecurity security READ security WRITE setSecurity)
        /*!
        \brief Whether all dates and time results for this request should be in UTC format
        \getter useUTCtime()
        \setter setUseUTCtime()
        */
        Q_PROPERTY(bool useUTCtime READ useUTCtime WRITE setUseUTCtime)
        Q_DECLARE_PRIVATE(QBbgReferenceDataRequest)
    public:
        //! Destructor
        virtual ~QBbgReferenceDataRequest();
        //! Creates an empty reference request
    	QBbgReferenceDataRequest();
        //! Creates a copy of a reference request
        QBbgReferenceDataRequest(const QBbgReferenceDataRequest& a);
        //! Copies another request
        virtual QBbgReferenceDataRequest& operator=(const QBbgReferenceDataRequest& a);
        //! Checks if two requests are identical
        virtual bool operator==(const QBbgReferenceDataRequest& a) const;
        //! If true all dates and times will be returned in UTC format
        bool useUTCtime() const;
        //! Set whether all date and times should be referenced as UTC (Greenwich Time)
        void setUseUTCtime(bool a);
        //! Reimplemented from QBbgAbstractRequest
        virtual void setSecurity(const QBbgSecurity& val);
    protected:
        QBbgReferenceDataRequest(QBbgReferenceDataRequestPrivate* d);
    };
}
#endif // QbbgReferenceDataRequest_h__