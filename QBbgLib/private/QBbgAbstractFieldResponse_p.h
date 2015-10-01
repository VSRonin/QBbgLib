#include "QBbgAbstractFieldResponse.h"
#include "QBbgAbstractResponse_p.h"
#include <QString>
#include <QVariant>
namespace QBbgLib {
    class QBbgAbstractFieldResponsePrivate : public QBbgAbstractResponsePrivate
    {
    private:
        Q_DECLARE_PUBLIC(QBbgAbstractFieldResponse)
        QBbgAbstractFieldResponsePrivate(const QBbgAbstractFieldResponsePrivate& other);
    public:
        virtual ~QBbgAbstractFieldResponsePrivate();
        QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, QBbgAbstractResponse::ResponseType typ/*=QBbgAbstractResponse::Invalid*/);
        QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, const QBbgAbstractFieldResponsePrivate& other);
        virtual QBbgAbstractFieldResponsePrivate& operator=(const QBbgAbstractFieldResponsePrivate& other);
        QString m_Header;
    };

    

}