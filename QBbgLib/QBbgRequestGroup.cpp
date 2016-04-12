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

#include "QBbgRequestGroup.h"
#include "private/QBbgRequestGroup_p.h"
#include <QSet>
#include "QBbgReferenceDataRequest.h"
#include "QBbgPortfolioDataRequest.h"
#include "QBbgHistoricalDataRequest.h"
#include "QBbgIntradayTickRequest.h"
//#define DISABLE_BULK_REQUESTS // Disables bulk requests in Bloomberg until a bug is fixed

namespace QBbgLib {


    qint64 QBbgRequestGroupPrivate::MaxID = 1;
    QBbgRequestGroup::QBbgRequestGroup()
        :d_ptr(new QBbgRequestGroupPrivate(this))
    {}
    QBbgRequestGroup::QBbgRequestGroup(const QBbgRequestGroup& a)
        : d_ptr(new QBbgRequestGroupPrivate(this, *(a.d_ptr)))
    {}

    QBbgRequestGroup& QBbgRequestGroup::operator=(const QBbgRequestGroup& a)
    {
        Q_D(QBbgRequestGroup);
        d->operator=(*(a.d_func()));
        return *this;
    }

    QBbgRequestGroupPrivate::QBbgRequestGroupPrivate(QBbgRequestGroup* q)
        : q_ptr(q)
    {}
    QBbgAbstractRequest* QBbgRequestGroupPrivate::createRequest(const QBbgAbstractRequest& a) const
    {
        switch (a.requestType()) {
        case QBbgAbstractRequest::RequestType::ReferenceData:
            return new QBbgReferenceDataRequest(static_cast<const QBbgReferenceDataRequest&>(a));
        case QBbgAbstractRequest::RequestType::PortfolioData:
            return new QBbgPortfolioDataRequest(static_cast<const QBbgPortfolioDataRequest&>(a));
        case QBbgAbstractRequest::RequestType::HistoricalData:
            return new QBbgHistoricalDataRequest(static_cast<const QBbgHistoricalDataRequest&>(a));
        case QBbgAbstractRequest::RequestType::IntraDayTick:
            return new QBbgIntradayTickRequest(static_cast<const QBbgIntradayTickRequest&>(a));
            //TODO add other types
        default:
            Q_UNREACHABLE(); //Unhandled request type
            return nullptr;
        }
    }
    qint32 QBbgRequestGroup::size() const
    {
        Q_D(const QBbgRequestGroup);
        return d->RequestTable.size();
    }
    QBbgRequestGroupPrivate::~QBbgRequestGroupPrivate()
    {
        clear();
    }
    QBbgRequestGroup::~QBbgRequestGroup()
    {
        delete d_ptr;
    }

    QBbgRequestGroupPrivate::QBbgRequestGroupPrivate(QBbgRequestGroup* q, const QBbgRequestGroupPrivate& a)
        : q_ptr(q)
    {
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = a.RequestTable.constBegin(); i != a.RequestTable.constEnd(); i++) {
            addRequest(*(i.value()), i.key());
        }
    }
    QBbgRequestGroupPrivate& QBbgRequestGroupPrivate::operator= (const QBbgRequestGroupPrivate& a)
    {
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = a.RequestTable.constBegin(); i != a.RequestTable.constEnd(); i++) {
            RequestTable.insert(i.key(), createRequest(*(i.value())));
            Q_ASSERT_X(RequestTable.value(i.key()), "QBbgRequestGroupPrivate::operator=", "NULL request added to table");
        }
        return *this;
    }
    void QBbgRequestGroup::clear()
    {
        Q_D(QBbgRequestGroup);
        d->clear();
    }
    qint64 QBbgRequestGroupPrivate::increaseMaxID()
    {
        qint64 result = MaxID++;
        if (MaxID == std::numeric_limits<qint64>::max())
            MaxID = 0;
        return result;
    }
    void QBbgRequestGroupPrivate::clear()
    {
        for (QHash<qint64, QBbgAbstractRequest*>::iterator i = RequestTable.begin(); i != RequestTable.end(); ++i) {
            delete i.value();
        }
        RequestTable.clear();
    }

    qint64 QBbgRequestGroup::addRequest(const QBbgAbstractRequest& a)
    {
        Q_D(QBbgRequestGroup);
        return d->addRequest(a);
    }
    qint64 QBbgRequestGroup::addRequest(QBbgAbstractRequest& a, qint64 preferredID)
    {
        Q_D(QBbgRequestGroup);
        return d->addRequest(a, preferredID);
    }
    qint64 QBbgRequestGroupPrivate::addRequest(const QBbgAbstractRequest& a)
    {
        
        QBbgAbstractRequest* newReq = createRequest(a);
        while (newReq->getID() < 0 || RequestTable.contains(newReq->getID())) {
            newReq->setID(increaseMaxID());
        }
        if (!newReq->isValidReq()) {
            delete newReq;
            return QBbgAbstractRequest::InvalidID;
        }
        return RequestTable.insert(newReq->getID(), newReq).key();
    }

    qint64 QBbgRequestGroupPrivate::addRequest(QBbgAbstractRequest& a, qint64 preferredID)
    {
        const qint64 oldID = a.getID();
        a.setID(preferredID);
        const qint64 result = addRequest(a);
        a.setID(oldID);
        return result;
    }

    const QBbgAbstractRequest* QBbgRequestGroupPrivate::request(qint64 ID) const
    {
        return RequestTable.value(ID, NULL);
    }
    const QBbgAbstractRequest* const QBbgRequestGroup::request(qint64 ID) const
    {
        Q_D(const QBbgRequestGroup);
        return d->request(ID);
    }
    QBbgAbstractRequest* QBbgRequestGroup::FindEditRequest(qint64 ID)
    {
        Q_D(QBbgRequestGroup);
        QHash<qint64, QBbgAbstractRequest*>::iterator iter = d->RequestTable.find(ID);
        if (iter == d->RequestTable.end())
            return NULL;
        return iter.value();
    }
    bool QBbgRequestGroup::isValidReq() const
    {
        Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = d->RequestTable.constBegin(); i != d->RequestTable.constEnd(); ++i) {
            if (!i.value()->isValidReq())
                return false;
        }
        return true;
    }
    QList<qint64> QBbgRequestGroup::findSecurity(const QBbgSecurity& Secur)const
    {
        Q_D(const QBbgRequestGroup);
        QList<qint64> Result;
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = d->RequestTable.constBegin(); i != d->RequestTable.constEnd(); ++i) {
            if (i.value()->security() == Secur) Result.append(i.key());
        }
        return Result;
    }
    QList<qint64> QBbgRequestGroup::IDList() const
    {
        Q_D(const QBbgRequestGroup);
        return d->RequestTable.keys();
    }
    void  QBbgRequestGroup::RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID)const
    {
        Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QList<qint64>* >::iterator i = Result.begin(); i != Result.end(); ++i)
            delete (i.value());
        Result.clear();
        {// Split by request type and security
            bool found;
            for (QHash<qint64, QBbgAbstractRequest*>::const_iterator MainIter = d->RequestTable.constBegin(); MainIter != d->RequestTable.constEnd(); ++MainIter) {
                found = false;
#ifndef DISABLE_BULK_REQUESTS
                for (QHash<qint64, QList<qint64>* >::iterator resIter = Result.begin(); !found && resIter != Result.end(); ++resIter) {
                    if (d->compatible(request(resIter.value()->first()), *MainIter)) {
                        resIter.value()->append(MainIter.key());
                        found = true;
                    }
                }
#endif // !DISABLE_BULK_REQUESTS
                if (!found) {
                    QHash<qint64, QList<qint64>* >::iterator iter=Result.insert(StartingID++, new QList<qint64>());
                    iter.value()->append(MainIter.key());
                }
            }
        }
#ifndef DISABLE_BULK_REQUESTS
        { 


            // Merge back groups with different securities but with all the other factors in common
            bool tempMerge;
            for (QHash<qint64, QList<qint64>* >::iterator MainIter = Result.begin(); MainIter != Result.end(); ++MainIter) {
                const QBbgAbstractRequest::RequestType mainType= request(MainIter.value()->first())->requestType();
                for (QHash<qint64, QList<qint64>* >::iterator SecondIter = MainIter + 1; SecondIter != Result.end();) {
                    tempMerge = mainType == request(SecondIter.value()->first())->requestType();
                    if (tempMerge)
                        // SameRequest is a slow method, call it only if necessary
                        tempMerge = d->SameRequest(*(MainIter.value()), *(SecondIter.value()));
                    if (tempMerge) {
                        MainIter.value()->append(*SecondIter.value());
                        delete SecondIter.value();
                        SecondIter = Result.erase(SecondIter);
                    }
                    else {
                        ++SecondIter;
                    }
                }
            }
            
        }
#endif // !DISABLE_BULK_REQUESTS
    }
    QList<QBbgAbstractRequest::RequestType> QBbgRequestGroup::differentTypes() const
    {
        QSet<QBbgAbstractRequest::RequestType> result;
        Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = d->RequestTable.constBegin(); i != d->RequestTable.constEnd(); ++i)
            result.insert(i.value()->requestType());
        return result.toList();
    }

    QList<QString> QBbgRequestGroup::differentServices() const
    {
        QSet<QString> result;
        Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator i = d->RequestTable.constBegin(); i != d->RequestTable.constEnd(); ++i)
            result.insert(QBbgAbstractRequest::serviceStringForRequest(i.value()->requestType()));
        return result.toList();
    }

    bool QBbgRequestGroupPrivate::SameRequest(const QList<qint64>& a, const QList<qint64>& b) const
    {
        if (static_cast<qint32>(request(a.first())->requestType()) & QBbgAbstractRequest::FirstFielded) {
            if (request(a.first())->requestType() == QBbgAbstractRequest::RequestType::HistoricalData) {
                return false; // Can't send multiple securities with hist data
            }
            QSet<QString> FiledsA;
            QSet<QString> FiledsB;
            if (a.empty()) return false;
            if (b.empty()) return false;
            Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(request(a.first())));
            Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(request(b.first())));
            if (
                !static_cast<const QBbgAbstractFieldRequest*>(request(a.first()))->sameOverrides(
                *static_cast<const QBbgAbstractFieldRequest*>(request(b.first())))
            ) return false;
            for (QList<qint64>::const_iterator i = a.constBegin(); i != a.constEnd(); ++i) {
                Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(request(*i)));
                FiledsA.insert(static_cast<const QBbgAbstractFieldRequest*>(request(*i))->field());
            }
            for (QList<qint64>::const_iterator i = b.constBegin(); i != b.constEnd(); ++i) {
                Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(request(*i)));
                FiledsB.insert(static_cast<const QBbgAbstractFieldRequest*>(request(*i))->field());
            }
            if (FiledsA != FiledsB)
                return false;
            return true;
        }
        else if (static_cast<qint32>(request(a.first())->requestType()) & QBbgAbstractRequest::FirstIntraday) {
            QSet<QBbgAbstractIntradayRequest::EventType> EventsA;
            QSet<QBbgAbstractIntradayRequest::EventType> EventsB;
            if (a.empty()) return false;
            if (b.empty()) return false;
            Q_ASSERT(dynamic_cast<const QBbgAbstractIntradayRequest*>(request(a.first())));
            Q_ASSERT(dynamic_cast<const QBbgAbstractIntradayRequest*>(request(b.first())));
            if (request(a.first())->requestType() == QBbgAbstractRequest::RequestType::IntraDayTick){
                Q_ASSERT(dynamic_cast<const QBbgIntradayTickRequest*>(request(a.first())));
                Q_ASSERT(dynamic_cast<const QBbgIntradayTickRequest*>(request(b.first())));
                if(!
                    static_cast<const QBbgIntradayTickRequest*>(request(a.first()))->sameOptions(
                        *static_cast<const QBbgIntradayTickRequest*>(request(b.first()))
                    )
                )
                return false; 
            }
            else{
                Q_UNREACHABLE(); // only IntraDayTick is available
            }
            for (QList<qint64>::const_iterator i = a.constBegin(); i != a.constEnd(); ++i) {
                Q_ASSERT(dynamic_cast<const QBbgAbstractIntradayRequest*>(request(*i)));
                EventsA.insert(static_cast<const QBbgAbstractIntradayRequest*>(request(*i))->eventType());
            }
            for (QList<qint64>::const_iterator i = b.constBegin(); i != b.constEnd(); ++i) {
                Q_ASSERT(dynamic_cast<const QBbgAbstractIntradayRequest*>(request(*i)));
                EventsB.insert(static_cast<const QBbgAbstractIntradayRequest*>(request(*i))->eventType());
            }
            if (EventsA != EventsB)
                return false;
            return true;
        }
        Q_UNREACHABLE(); //Unhandled request type
        return false;
        
    }
    bool QBbgRequestGroupPrivate::compatible(const QBbgAbstractRequest* a, const QBbgAbstractRequest* b) const
    {
        if (!a || !b) return false;
        if (a->requestType() != b->requestType()) 
            return false;
        if (a->security() != b->security()) 
            return false;
        switch (a->requestType()) {
        case QBbgAbstractRequest::RequestType::ReferenceData:
        case QBbgAbstractRequest::RequestType::PortfolioData:
            Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(a));
            Q_ASSERT(dynamic_cast<const QBbgAbstractFieldRequest*>(b));
            if (!static_cast<const QBbgAbstractFieldRequest*>(a)->sameOverrides(*static_cast<const QBbgAbstractFieldRequest*>(b))) 
                return false;
            break;
        case QBbgAbstractRequest::RequestType::HistoricalData:
            Q_ASSERT(dynamic_cast<const QBbgHistoricalDataRequest*>(a));
            Q_ASSERT(dynamic_cast<const QBbgHistoricalDataRequest*>(b));
            if (!static_cast<const QBbgAbstractFieldRequest*>(a)->sameOverrides(*static_cast<const QBbgAbstractFieldRequest*>(b))) 
                return false;
            if (!static_cast<const QBbgHistoricalDataRequest*>(a)->equalHistoricalFields(*static_cast<const QBbgHistoricalDataRequest*>(b))) 
                return false;
            break;
        case QBbgAbstractRequest::RequestType::IntraDayTick:
            Q_ASSERT(dynamic_cast<const QBbgIntradayTickRequest*>(a));
            Q_ASSERT(dynamic_cast<const QBbgIntradayTickRequest*>(b));
            if (!static_cast<const QBbgIntradayTickRequest*>(a)->sameOptions(*static_cast<const QBbgIntradayTickRequest*>(b)))
                return false;
            break;
        default:
            Q_UNREACHABLE(); //Unhandled request type
        }
        return true;
    }
}


