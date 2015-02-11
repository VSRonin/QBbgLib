#ifndef QSingleBbgResult_p_h__
#define QSingleBbgResult_p_h__
#include "QSingleBbgResult.h"
#include <QList>
#include <QString>
#include <QDate>
namespace QBbgLib {
    class QSingleBbgResultPrivate
    {
    private:
        Q_DECLARE_PUBLIC(QSingleBbgResult)
        QSingleBbgResult* q_ptr;
        QSingleBbgResultPrivate(const QSingleBbgResultPrivate& a);
    public:
        bool HasTable() const;
        void SetValue(const QString& val, const QString& Header = QString());
        void AddValueRow(const QList<QString>& val, const QList<QString>& Headers = QList<QString>());
        void Clear();
        BbgErrorCodes m_ErrorCode;
        QString m_Header;
        QString* m_StringValue;
        QDate* m_DateValue;
        double* m_DoubleValue;
        QList<QSingleBbgResult*> m_TableResultRows;
        quint32 TableResultCols;
        virtual ~QSingleBbgResultPrivate();
        QSingleBbgResultPrivate(QSingleBbgResult* q);
        QSingleBbgResultPrivate(QSingleBbgResult* q,const QSingleBbgResultPrivate& a);
        QSingleBbgResultPrivate& operator=(const QSingleBbgResultPrivate& a);
    };
}
#endif // QSingleBbgResult_p_h__