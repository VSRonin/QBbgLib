#include <QtCore/QCoreApplication>
#include "QBbgManager.h"
#include "QBbgSecurity.h"
#include "QbbgReferenceDataRequest.h"
#include "QBbgRequestGroup.h"
#include "QBbgReferenceDataResponse.h"
#include "QBbgPortfolioDataRequest.h"
#include <QDebug>
#include "QBbgPortfolioDataResponse.h"
#include "QBbgOverride.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QBbgLib::QBbgSecurity secur("FRIAR 2014-1 A", QBbgLib::QBbgSecurity::Mtge);
    QBbgLib::QBbgReferenceDataRequest a_req;
    QBbgLib::QBbgPortfolioDataRequest p_req;
    p_req.setSecurity("TS-PX1915-15", QBbgLib::QBbgSecurity::Client);
    //p_req.setSecurity("U10628870-2", QBbgLib::QBbgSecurity::Client);
    //p_req.setReferenceDay(QDate(2015, 01, 30));
    QBbgLib::QBbgOverride overrides;
    overrides.setOverride("Allow dynamic cashflow calcs", true);
    overrides.setOverride("mtg prepay speed", 100);
    overrides.setOverride("mtg prepay typ", "CPR");
    overrides.setOverride("YLD flag", 2);
    overrides.setOverride("prepay speed vector", "15 6S 20 24S 15");
    overrides.setOverride("apply FWD rate", false);
    overrides.setOverride("recovery lag", 0);
    a_req.setOverrides(overrides);
    a_req.setSecurity(secur);
    a_req.setField("mtg cash flow");

    QBbgLib::QBbgRequestGroup req;
    req.addRequest(a_req);
    a_req.setField("name");
    //req.addRequest(a_req);
    QBbgLib::QBbgManager mainManager;
    
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::recieved, [&mainManager](quint32 gr, qint64 id)
    {
        const QBbgLib::QBbgAbstractResponse* genres = mainManager.getResult(gr, id);
        if (genres->hasErrors()) {
            qDebug() << QString::number(genres->getID()) + " - " + genres->errorMessage();
        }
        else {
            switch (genres->responseType()) {
            case QBbgLib::QBbgAbstractResponse::ReferenceDataResponse:{
                const QBbgLib::QBbgReferenceDataResponse* const res = dynamic_cast<const QBbgLib::QBbgReferenceDataResponse* const>(genres);
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

            }
            break;
            case QBbgLib::QBbgAbstractResponse::PortfolioDataResponse:{
                const QBbgLib::QBbgPortfolioDataResponse* const res = dynamic_cast<const QBbgLib::QBbgPortfolioDataResponse* const>(genres);
                Q_ASSERT(res);
                qDebug() << res->header();
                for (int i = 0; i < res->size(); ++i) {
                    qDebug() << res->security(i).fullName()
                        + (res->hasPosition() ? QString(" Position: %1").arg(res->position(i)) : QString())
                        + (res->hasMarketValue() ? QString(" Market Value: %1").arg(res->marketValue(i)) : QString())
                        + (res->hasCost() ? QString(" Cost: %1").arg(res->cost(i)) : QString())
                        + (res->hasCostDate() ? (" Cost Date: " + res->costDate(i).toString("yyyy-MM-dd")) : QString())
                        + (res->hasCostFx() ? QString(" Cost Fx Rate: %1").arg(res->costFx(i)) : QString())
                        + (res->hasWeight() ? QString(" Weight: %1").arg(res->weight(i)) : QString())
                        ;
                }
            }
            break;
            default:
                Q_ASSERT_X(false, "main", "Unhandled Response");
            }
        }
    });
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::finished, []() { qDebug() << "Finished"; });
    p_req.setField("PORTFOLIO_DATA");
    //req.addRequest(p_req);
    a_req.setField("Gibberish");
    //req.addRequest(a_req);
    a_req.setSecurity(QString("invalid Mtge"));
    //req.addRequest(a_req);
    a_req.setField("PX_LAST");
    //req.addRequest(a_req);
    mainManager.startRequest(req);
    qDebug() << "Started";
    return a.exec();
}
//////////////////////////////////////////////////////////////////////////
