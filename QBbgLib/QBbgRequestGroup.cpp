#include "QBbgRequestGroup.h"
#include "QBbgRequestGroup_p.h"
#include <QSet>
#include "QbbgReferenceDataRequest.h"
#include "QBbgPortfolioDataRequest.h"
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
        case QBbgAbstractRequest::ReferenceData:
            return new QBbgReferenceDataRequest(dynamic_cast<const QBbgReferenceDataRequest&>(a));
        case QBbgAbstractRequest::PortfolioData:
            return new QBbgPortfolioDataRequest(dynamic_cast<const QBbgPortfolioDataRequest&>(a));
            //TODO add other types
        default:
            Q_ASSERT_X(false, "QBbgRequestGroupPrivate::createRequest", "Unhandled request type");
            return NULL;
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
            RequestTable.insert(i.key(), new QBbgAbstractRequest(*(i.value())));
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
        QBbgAbstractRequest* newReq = d->createRequest(a);

        while (newReq->getID() < 0 || d->RequestTable.contains(newReq->getID())) {
            newReq->setID(d->increaseMaxID());
        }
        if (!newReq->isValidReq()) {
            delete newReq;
            return QBbgAbstractRequest::InvalidID;
        }
        QHash<qint64, QBbgAbstractRequest*>::iterator iter = d->RequestTable.find(newReq->getID());
        if (iter == d->RequestTable.end()) {
            iter=d->RequestTable.insert(newReq->getID(), newReq);
        }
        else {
            delete iter.value();
            iter.value() = newReq;
        }
        return iter.key();
    }
    const QBbgAbstractRequest* QBbgRequestGroupPrivate::request(qint64 ID) const
    {
        return RequestTable.value(ID, NULL);
    }
    const QBbgAbstractRequest* QBbgRequestGroup::request(qint64 ID) const
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

        /*Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QList<qint64>* >::iterator i = Result.begin(); i != Result.end(); ++i)
            delete (i.value());
        Result.clear();
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator MainIter = d->RequestTable.constBegin(); MainIter != d->RequestTable.constEnd(); ++MainIter) {
            QList<qint64>* tmp = new QList<qint64>();
            tmp->append(MainIter.key());
            Result.insert(MainIter.key(), tmp);
        }
        return;*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QList<qint64>* >::iterator i = Result.begin(); i != Result.end(); ++i)
            delete (i.value());
        Result.clear();
        {// Split by request type and security
            bool found;
            for (QHash<qint64, QBbgAbstractRequest*>::const_iterator MainIter = d->RequestTable.constBegin(); MainIter != d->RequestTable.constEnd(); ++MainIter) {
                found = false;
                for (QHash<qint64, QList<qint64>* >::iterator resIter = Result.begin(); !found && resIter != Result.end(); ++resIter) {
                    if (d->compatible(request(resIter.value()->first()), *MainIter)) {
                        resIter.value()->append(MainIter.key());
                        found = true;
                    }
                }
                if (!found) {
                    QHash<qint64, QList<qint64>* >::iterator iter=Result.insert(StartingID++, new QList<qint64>());
                    iter.value()->append(MainIter.key());
                }
            }
        }
        { /*
            // Merge back groups with different securities but with all the other factors in common
            bool tempMerge;
            for (QHash<qint64, QList<qint64>* >::iterator MainIter = Result.begin(); MainIter != Result.end(); ++MainIter) {
                for (QHash<qint64, QList<qint64>* >::iterator SecondIter = MainIter+1; SecondIter != Result.end();) {
                    tempMerge = request(MainIter.value()->first())->requestType() == request(SecondIter.value()->first())->requestType();
                    if (tempMerge)
                        // SameRequest is a slow method, call it only if necessary
                        tempMerge = d->SameRequest(*(MainIter.value()), *(SecondIter.value()));
                    if (tempMerge) {
                        MainIter.value()->append(*(SecondIter.value()));
                        delete SecondIter.value();
                        SecondIter = Result.erase(SecondIter);
                    }
                    else {
                        ++SecondIter;
                    }
                }
            }
            */
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Q_D(const QBbgRequestGroup);
        for (QHash<qint64, QList<qint64>* >::iterator i = Result.begin(); i != Result.end(); i++)
            delete (i.value());
        Result.clear();
        QList<qint64> UsedIDs;
        QList<QString> UsedFields;
        for (QHash<qint64, QBbgAbstractRequest*>::const_iterator MainIter = d->RequestTable.constBegin(); MainIter != d->RequestTable.constEnd(); ++MainIter) {
            if (UsedIDs.contains(MainIter.key()))continue;
            UsedIDs.append(MainIter.key());
            UsedFields.clear();
            UsedFields.push_back(MainIter.value()->GetField());
            QList<qint64>* CurrentGroup = new QList<qint64>();
            CurrentGroup->push_back(MainIter.key());
            for (QHash<qint64, QBbgAbstractRequest*>::const_iterator SecondIter = MainIter + 1; SecondIter != d->RequestTable.constEnd(); ++SecondIter) {
                if (MainIter.value()->security() == SecondIter.value()->security()) {
                    if (MainIter.value()->SameOverrides(*SecondIter.value())) {
                        UsedIDs.append(SecondIter.key());
                        CurrentGroup->append(SecondIter.key());
                        UsedFields.append(SecondIter.value()->field());
                    }
                }
            }
            Result.insert(StartingID, CurrentGroup);
            StartingID++;
        }
        for (QHash<qint64, QList<qint64>* >::iterator MainIter = Result.begin(); MainIter != Result.end();) {
            if (MainIter.value()->empty()) {
                MainIter = Result.erase(MainIter);
                continue;
            }
            for (QHash<qint64, QList<qint64>* >::iterator SecondIter = MainIter + 1; SecondIter != Result.end();) {
                if (d->SameRequest(*(MainIter.value()), *(SecondIter.value()))) {
                    MainIter.value()->append(*(SecondIter.value()));
                    delete SecondIter.value();
                    SecondIter = Result.erase(SecondIter);
                    continue;
                }
                SecondIter++;
            }
            MainIter++;
        }*/
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
        if (request(*a.begin())->requestType() & QBbgAbstractRequest::FirstFielded) {
            QSet<QString> FiledsA;
            QSet<QString> FiledsB;
            if (a.empty()) return false;
            if (b.empty()) return false;
            if (
                !dynamic_cast<const QBbgAbstractFieldRequest*>(request(a.first()))->sameOverrides(
                *dynamic_cast<const QBbgAbstractFieldRequest*>(request(b.first())))
            ) return false;
            for (QList<qint64>::const_iterator i = a.constBegin(); i != a.constEnd(); ++i) {
                FiledsA.insert(dynamic_cast<const QBbgAbstractFieldRequest*>(request(*i))->field());
            }
            for (QList<qint64>::const_iterator i = b.constBegin(); i != b.constEnd(); ++i) {
                FiledsB.insert(dynamic_cast<const QBbgAbstractFieldRequest*>(request(*i))->field());
            }
            return FiledsA == FiledsB;
        }
        //TODO do realtime
        Q_ASSERT_X(false, "QBbgRequestGroupPrivate::SameRequest", "Unhandled request type");
        return false;
        
    }
    bool QBbgRequestGroupPrivate::compatible(const QBbgAbstractRequest* a, const QBbgAbstractRequest* b) const
    {
        if (!a || !b) return false;
        if (a->requestType() != b->requestType()) return false;
        if (a->security() != b->security()) return false;
        switch (a->requestType()) {
        case QBbgAbstractRequest::ReferenceData:
        case QBbgAbstractRequest::PortfolioData:
            if (!dynamic_cast<const QBbgAbstractFieldRequest*>(a)->sameOverrides(*dynamic_cast<const QBbgAbstractFieldRequest*>(b))) return false;
            break;
        }
        return true;
    }
}


