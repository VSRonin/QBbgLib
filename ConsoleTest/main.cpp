#include <QtCore/QCoreApplication>
#include "QBbgManager.h"
#include "QBbgSecurity.h"
#include "QbbgReferenceDataRequest.h"
#include "QBbgRequestGroup.h"
#include "QBbgReferenceDataResponse.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QBbgLib::QBbgSecurity secur("XS0181673798", QBbgLib::QBbgSecurity::isin);
    QBbgLib::QBbgReferenceDataRequest a_req;
    a_req.setSecurity(secur);
    a_req.setField("px  last\t");
    QBbgLib::QBbgRequestGroup req;
    req.addRequest(a_req);
    a_req.setField("name");
    req.addRequest(a_req);
    a_req.setField("des cash flow");
    req.addRequest(a_req);
    QBbgLib::QBbgManager mainManager;
    
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::recieved, [&mainManager](quint32 gr, qint64 id)
    {
        const QBbgLib::QBbgReferenceDataResponse* res = dynamic_cast<const QBbgLib::QBbgReferenceDataResponse* const >(mainManager.getResult(gr, id));
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
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::finished, []() { qDebug() << "Finished"; });
    mainManager.startRequest(req);
    qDebug() << "Started";
    return a.exec();
}
//////////////////////////////////////////////////////////////////////////
