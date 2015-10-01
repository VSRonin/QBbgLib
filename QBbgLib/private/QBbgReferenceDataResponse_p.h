#ifndef QBbgReferenceDataResponse_p_h__
#define QBbgReferenceDataResponse_p_h__
#include "QBbgReferenceDataResponse.h"
#include "QBbgAbstractFieldResponse_p.h"
#include <QList>
namespace QBbgLib {
    class QBbgReferenceDataResponsePrivate : public QBbgAbstractFieldResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgReferenceDataResponse)
        QBbgReferenceDataResponsePrivate(const QBbgReferenceDataResponsePrivate& other);
    public:
        virtual ~QBbgReferenceDataResponsePrivate();
        QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q, const QBbgReferenceDataResponsePrivate& other);
        QBbgReferenceDataResponsePrivate(QBbgReferenceDataResponse* q);
        virtual QBbgReferenceDataResponsePrivate& operator=(const QBbgReferenceDataResponsePrivate& other);
        QVariant m_Value;
        QList<QBbgReferenceDataResponse*> m_TableResultRows;
        qint32 m_TableCols;
    	
    };

    

   

    

}
#endif // QBbgReferenceDataResponse_p_h__