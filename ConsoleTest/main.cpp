#include <QtCore/QCoreApplication>
#include "QBbgRequestResponseWorker.h"
#include "QBbgSecurity.h"
#include "QbbgReferenceDataRequest.h"
#include "QBbgRequestGroup.h"
#include "QBbgReferenceDataResponse.h"
#include <QDebug>
#include <blpapi_session.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QBbgLib::QBbgSecurity secur("XS0181673798", QBbgLib::QBbgSecurity::Corp);
    QBbgLib::QBbgReferenceDataRequest a_req;
    a_req.setSecurity(secur);
    a_req.setField("px  last\t");
    BloombergLP::blpapi::SessionOptions sessionOptions;
    sessionOptions.setServerHost("localhost");
    sessionOptions.setServerPort(8194);
    sessionOptions.setMaxPendingRequests(INT_MAX - 2);
    QBbgLib::QBbgRequestGroup req;
    req.addRequest(a_req);
    QBbgLib::QBbgRequestResponseWorker mainworker(sessionOptions);
    QObject::connect(&mainworker, &QBbgLib::QBbgRequestResponseWorker::Recieved, [&mainworker](qint64 id)
    {
        const QBbgLib::QBbgReferenceDataResponse* res = dynamic_cast<const QBbgLib::QBbgReferenceDataResponse*>(mainworker.result(id));
        Q_ASSERT(res);
        if (res->hasValue())
            qDebug() << res->header() << res->value();
        if (res->hasTable()) {
            qDebug() << res->header();
            for (int i = 0; i < res->rows(); ++i) {
                for (int j = 0; j < res->columns(); ++j) {
                    qDebug() << res->getTableValue(i, j)->header() << res->getTableValue(i, j)->value();
                }
            }
        }
    });
    QObject::connect(&mainworker, &QBbgLib::QBbgRequestResponseWorker::Finished, []() { qDebug() << "Finished"; });
    mainworker.start(req);
    qDebug() << "Started";
    return a.exec();
}
