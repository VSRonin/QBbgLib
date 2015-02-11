#include "QBbgRequest.h"
#include "QBbgRequest_p.h"
#include "QSingleBbgRequest.h"
#include <QDataStream>
namespace QBbgLib {
    QBbgRequest::QBbgRequest()
        :d_ptr(new QBbgRequestPrivate(this))
    {}
    QBbgRequest::QBbgRequest(const QBbgRequest& a)
        : d_ptr(new QBbgRequestPrivate(this, *(a.d_ptr)))
    {}

    QBbgRequest& QBbgRequest::operator=(const QBbgRequest& a)
    {
        Q_D(QBbgRequest);
        d->operator=(*(a.d_ptr));
        return *this;
    }

    QBbgRequestPrivate::QBbgRequestPrivate(QBbgRequest* q)
        : q_ptr(q)
        , MaxID(std::numeric_limits<qint64>::min())
    {}
    qint32 QBbgRequest::NumRequests() const
    {
        Q_D(const QBbgRequest);
        return d->ResultTable.size();
    }
    QBbgRequestPrivate::~QBbgRequestPrivate()
    {
        ClearRequests();
    }
    QBbgRequest::~QBbgRequest()
    {
        delete d_ptr;
    }

    QBbgRequestPrivate::QBbgRequestPrivate(QBbgRequest* q, const QBbgRequestPrivate& a)
        : q_ptr(q)
        , MaxID(a.MaxID)
    {
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = a.ResultTable.constBegin(); i != a.ResultTable.constEnd(); i++) {
            ResultTable.insert(i.key(), new QSingleBbgRequest(*(i.value())));
        }
    }
    QBbgRequestPrivate& QBbgRequestPrivate::operator= (const QBbgRequestPrivate& a)
    {
        MaxID = a.MaxID;
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = a.ResultTable.constBegin(); i != a.ResultTable.constEnd(); i++) {
            ResultTable.insert(i.key(), new QSingleBbgRequest(*(i.value())));
        }
        return *this;
    }
    void QBbgRequest::ClearRequests()
    {
        Q_D(QBbgRequest);
        d->ClearRequests();
    }
    void QBbgRequestPrivate::ClearRequests()
    {
        for (QHash<qint64, QSingleBbgRequest*>::iterator i = ResultTable.begin(); i != ResultTable.end(); ++i) {
            delete i.value();
        }
        ResultTable.clear();
    }

    void QBbgRequest::AddRequest(const QSingleBbgRequest& a)
    {
        Q_D(QBbgRequest);
        if (d->ResultTable.contains(a.GetResultID())) return;
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
            if (i.value()->operator==(a)) return;
        }
        QSingleBbgRequest* TempRes = new QSingleBbgRequest(a);
        if (TempRes->GetResultID() < 1i64) {
            ++(d->MaxID);
            TempRes->SetResultID((d->MaxID<1i64) ? 1i64 : d->MaxID);
        }
        if (TempRes->GetResultID() > d->MaxID)
            d->MaxID = TempRes->GetResultID();
        d->ResultTable.insert(TempRes->GetResultID(), TempRes);
    }
    const QSingleBbgRequest* QBbgRequest::FindRequest(qint64 ID) const
    {
        Q_D(const QBbgRequest);
        return d->FindRequest(ID);
    }
    const QSingleBbgRequest* QBbgRequestPrivate::FindRequest(qint64 ID) const
    {
        return ResultTable.value(ID, NULL);
    }
    const QSingleBbgRequest* QBbgRequest::GetRequest(quint32 Index) const
    {
        Q_D(const QBbgRequest);
        if (Index > d->ResultTable.size()) return NULL;
        return (d->ResultTable.begin() + Index).value();
    }
    QSingleBbgRequest* QBbgRequest::GetEditRequest(quint32 Index)
    {
        Q_D(QBbgRequest);
        if (Index > d->ResultTable.size()) return NULL;
        return (d->ResultTable.begin() + Index).value();
    }
    QSingleBbgRequest* QBbgRequest::FindEditRequest(qint64 ID)
    {
        Q_D(QBbgRequest);
        if (d->ResultTable.contains(ID))
            return d->ResultTable[ID];
        return NULL;
    }
    bool QBbgRequest::IsValidReq() const
    {
        Q_D(const QBbgRequest);
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
            if (!i.value()->IsValidReq())
                return false;
        }
        return true;
    }
    QList<qint64> QBbgRequest::FindSecurity(QString Secur)const
    {
        Q_D(const QBbgRequest);
        QList<qint64> Result;
        Secur = Secur.trimmed().toUpper();
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
            if (i.value()->GetSecurity() == Secur || i.value()->GetFullSecurity().toUpper() == Secur) Result.append(i.key());
        }
        return Result;
    }
    QList<qint64> QBbgRequest::FindField(QString Field)const
    {
        Q_D(const QBbgRequest);
        QList<qint64> Result;
        Field = Field.simplified().toUpper();
        Field.replace(QChar(' '), QChar('_'));
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
            if (i.value()->GetField() == Field) Result.append(i.key());
        }
        return Result;
    }
    QList<qint64> QBbgRequest::FindSecurityField(QString Secur, QString Field)const
    {
        Q_D(const QBbgRequest);
        QList<qint64> Result;
        Secur = Secur.simplified().toUpper();
        Field = Field.simplified().toUpper();
        Field.replace(QChar(' '), QChar('_'));
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
            if (
                i.value()->GetField() == Field &&
                (i.value()->GetSecurity() == Secur || i.value()->GetFullSecurity().toUpper() == Secur)
                ) Result.append(i.key());
        }
        return Result;
    }
    QList<qint64> QBbgRequest::IdList() const
    {
        Q_D(const QBbgRequest);
        return d->ResultTable.keys();
        /*QList<qint64> Result;
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator i = d->ResultTable.constBegin(); i != d->ResultTable.constEnd(); ++i) {
        Result.append(i.key());
        }
        return Result;*/
    }
    void QBbgRequest::AddRequest(qint64 ID, const QString& Secur, const QString& Field, YellowKeys YellowKey)
    {
        QSingleBbgRequest Temp;
        Temp.SetField(Field);
        Temp.SetSecurity(Secur);
        Temp.SetResultID(ID);
        Temp.SetExtension(YellowKey);
        AddRequest(Temp);
    }
    void QBbgRequest::AddRequest(const QString& Secur, const QString& Field, YellowKeys YellowKey)
    {
        Q_D(QBbgRequest);
        AddRequest(1i64 + d->MaxID, Secur, Field, YellowKey);
    }
    void QBbgRequest::AddRequest(qint64 ID, const QString& Secur, const QString& Field, const Overrides& Overr, YellowKeys YellowKey)
    {
        QSingleBbgRequest Temp;
        Temp.SetField(Field);
        Temp.SetSecurity(Secur);
        Temp.SetResultID(ID);
        Temp.SetOverrides(Overr);
        Temp.SetExtension(YellowKey);
        AddRequest(Temp);
    }
    void QBbgRequest::AddRequest(const QString& Secur, const QString& Field, const Overrides& Overr, YellowKeys YellowKey)
    {
        Q_D(QBbgRequest);
        AddRequest(1i64 + d->MaxID, Secur, Field, Overr, YellowKey);
    }
    void  QBbgRequest::RequestGroups(QHash<qint64, QList<qint64>* >& Result, qint64 StartingID)const
    {
        Q_D(const QBbgRequest);
        for (QHash<qint64, QList<qint64>* >::iterator i = Result.begin(); i != Result.end(); i++)
            delete (i.value());
        Result.clear();
        QList<qint64> UsedIDs;
        QList<QString> UsedFields;
        for (QHash<qint64, QSingleBbgRequest*>::const_iterator MainIter = d->ResultTable.constBegin(); MainIter != d->ResultTable.constEnd(); ++MainIter) {
            if (UsedIDs.contains(MainIter.key()))continue;
            UsedIDs.append(MainIter.key());
            UsedFields.clear();
            UsedFields.push_back(MainIter.value()->GetField());
            QList<qint64>* CurrentGroup = new QList<qint64>();
            CurrentGroup->push_back(MainIter.key());
            for (QHash<qint64, QSingleBbgRequest*>::const_iterator SecondIter = MainIter + 1; SecondIter != d->ResultTable.constEnd(); ++SecondIter) {
                if (MainIter.value()->GetFullSecurity() == SecondIter.value()->GetFullSecurity()) {
                    if (MainIter.value()->SameOverrides(*SecondIter.value())) {
                        UsedIDs.append(SecondIter.key());
                        CurrentGroup->append(SecondIter.key());
                        UsedFields.append(SecondIter.value()->GetField());
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
        }
    }


    qint32 QBbgRequest::GetErrorCode() const
    {
        Q_D(const QBbgRequest);
        return d->m_ErrorCode;
    }
    bool QBbgRequest::HasErrors() const
    {
        Q_D(const QBbgRequest);
        return d->m_ErrorCode != NoErrors;
    }
    void QBbgRequest::SetErrorCode(BbgErrorCodes val)
    {
        Q_D(QBbgRequest);
        if (val == NoErrors) d->m_ErrorCode = NoErrors;
        else d->m_ErrorCode |= val;
    }
    bool QBbgRequestPrivate::SameRequest(const QList<qint64>& a, const QList<qint64>& b) const
    {
        QList<QString> FiledsA;
        QList<QString> FiledsB;
        if (a.empty()) return false;
        if (b.empty()) return false;
        if (!FindRequest(*a.begin())->SameOverrides(*FindRequest(*b.begin()))) return false;
        for (QList<qint64>::const_iterator i = a.constBegin(); i != a.constEnd(); i++) {
            FiledsA.append(FindRequest(*i)->GetField());
        }
        for (QList<qint64>::const_iterator i = b.constBegin(); i != b.constEnd(); i++) {
            FiledsB.append(FindRequest(*i)->GetField());
        }
        if (FiledsA.size() != FiledsB.size()) return false;
        for (QList<QString>::const_iterator i = FiledsA.constBegin(); i != FiledsA.constEnd(); i++) {
            if (!FiledsB.contains(*i)) return false;
        }
        return true;
    }
}


