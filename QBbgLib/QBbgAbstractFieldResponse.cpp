#include "QBbgAbstractFieldResponse.h"
#include "private/QBbgAbstractFieldResponse_p.h"
namespace QBbgLib {
    QBbgAbstractFieldResponsePrivate::QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, QBbgAbstractResponse::ResponseType typ)
        :QBbgAbstractResponsePrivate(q,typ)
    {}

    QBbgAbstractFieldResponsePrivate::QBbgAbstractFieldResponsePrivate(QBbgAbstractFieldResponse* q, const QBbgAbstractFieldResponsePrivate& other)
        : QBbgAbstractResponsePrivate(q, other)
        , m_Header(other.m_Header)
    {}
    QBbgAbstractFieldResponsePrivate& QBbgAbstractFieldResponsePrivate::operator=(const QBbgAbstractFieldResponsePrivate& other)
    {
        QBbgAbstractResponsePrivate::operator=(other);
        m_Header = other.m_Header;
        return *this;
    }
    QBbgAbstractFieldResponse::QBbgAbstractFieldResponse(ResponseType typ)
        :QBbgAbstractResponse(new QBbgAbstractResponsePrivate(this,typ))
    {}

    QBbgAbstractFieldResponse::QBbgAbstractFieldResponse(const QBbgAbstractFieldResponse& a)
        : QBbgAbstractResponse(new QBbgAbstractResponsePrivate(this,*(a.d_func())))
    {}

    QBbgAbstractFieldResponse::QBbgAbstractFieldResponse(QBbgAbstractFieldResponsePrivate* d)
        : QBbgAbstractResponse(d)
    {}
    QBbgAbstractFieldResponse& QBbgAbstractFieldResponse::operator=(const QBbgAbstractFieldResponse& a)
    {
        Q_D(QBbgAbstractFieldResponse);
        d->operator=(*(a.d_func()));
        return *this;
    }
    const QString& QBbgAbstractFieldResponse::header() const
    {
        Q_D(const QBbgAbstractFieldResponse);
        return d->m_Header;
    }
    void QBbgAbstractFieldResponse::setHeader(const QString& Header)
    {
        Q_D(QBbgAbstractFieldResponse);
        d->m_Header=Header;
    }
}
