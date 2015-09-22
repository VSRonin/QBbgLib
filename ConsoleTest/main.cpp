#include <QtCore/QCoreApplication>
#include "QBbgManager.h"
#include "QBbgSecurity.h"
#include "QbbgReferenceDataRequest.h"
#include "QBbgRequestGroup.h"
#include "QBbgReferenceDataResponse.h"
#include "QBbgPortfolioDataRequest.h"
#include <QDebug>
#include "QBbgPortfolioDataResponse.h"
#include "QBbgHistoricalDataRequest.h"
#include "QBbgHistoricalDataResponse.h"
#include "QBbgOverride.h"
#include <QFile>
#include <QTextStream>
#include <QVariant>
void PrintToTempFile(const QString& TempFileName, const QString& Message, bool PrintTime)
{
    QFile TempFile("C:/Temp/" + TempFileName + ".log");
    if (!TempFile.open(QIODevice::Append | QIODevice::Text)) return;
    QTextStream TempWrite(&TempFile);
    TempWrite << (PrintTime ? QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm ") : QString()) + Message + '\n';
    TempFile.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //QBbgLib::QBbgSecurity secur("XS0243658670", QBbgLib::QBbgSecurity::Mtge);
    //QBbgLib::QBbgReferenceDataRequest a_req;
    QBbgLib::QBbgPortfolioDataRequest p_req;
    //QBbgLib::QBbgHistoricalDataRequest h_req;
    p_req.setSecurity("TS-PX1915-32", QBbgLib::QBbgSecurity::Client);
    //p_req.setSecurity("U10628870-2", QBbgLib::QBbgSecurity::Client);
    p_req.setReferenceDay(QDate(2015, 9, 3));
    //QBbgLib::QBbgOverride overrides;
   /* overrides.setOverride("Allow dynamic cashflow calcs", "Y");
    overrides.setOverride("mtg prepay typ", "CPR");
      overrides.setOverride("YLD flag", "1");
      overrides.setOverride("prepay speed vector", "5 12S 5 72R 16");
      overrides.setOverride("Default_Type", "CDR");
      overrides.setOverride("Default_Speed_Vector", "2");
      overrides.setOverride("Loss_Severity", "25");
     overrides.setOverride("Delinquency_Vector", "13 48S 20");
     overrides.setOverride("Trigger_State", "S");
     overrides.setOverride("apply FWD rate", "N");
    a_req.setOverrides(overrides);
    a_req.setSecurity(secur);
    a_req.setField("mtg cash flow");*/

   /* h_req.setSecurity(QBbgLib::QBbgSecurity("EUR003M", QBbgLib::QBbgSecurity::Index));
    h_req.setField("PX_LAST");
    h_req.startDate(QDate(2015, 3, 14));
    h_req.endDate(QDate(2015, 4, 14));
    h_req.nonTradingDayFill(QBbgLib::QBbgHistoricalDataRequest::ALL_CALENDAR_DAYS);*/

    QBbgLib::QBbgRequestGroup req;
    //req.addRequest(a_req);
   // a_req.setField("name");
    //req.addRequest(a_req);
    QBbgLib::QBbgManager mainManager;
    
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::recieved, [&mainManager](quint32 gr, qint64 id)
    {
        const QBbgLib::QBbgAbstractResponse* genres = mainManager.getResult(gr, id);
        if (genres->hasErrors()) {
            qDebug() << QString::number(genres->getID()) + " - " + genres->errorMessage();
            PrintToTempFile("BbgErrors", QString::number(genres->getID()) + " - " + genres->errorMessage(), false);
        }
        else {
            switch (genres->responseType()) {
            case QBbgLib::QBbgAbstractResponse::ResponseType::ReferenceDataResponse:{
                Q_ASSERT(dynamic_cast<const QBbgLib::QBbgReferenceDataResponse* const>(genres));
                const QBbgLib::QBbgReferenceDataResponse* const res = static_cast<const QBbgLib::QBbgReferenceDataResponse* const>(genres);
                QString tmpStr;
                if (res->hasValue()) {
                    qDebug() << res->header() << res->value();
                    tmpStr = res->header() + ": " + res->value().toString();
                }
                if (res->hasTable()) {
                    qDebug() << res->header();
                    tmpStr = res->header();
                    for (int i = 0; i < res->rows(); ++i) {
                        tmpStr += '\n';
                        if (i == 0) {
                            for (int j = 0; j < res->columns(); ++j) {
                                tmpStr += res->getTableValue(i, j)->header() + '\t';
                            }
                            tmpStr.chop(1);
                            tmpStr += '\n';
                        }
                        for (int j = 0; j < res->columns(); ++j) {
                            qDebug() << res->getTableValue(i, j)->header() << res->getTableValue(i, j)->value();
                            tmpStr += res->getTableValue(i, j)->value().toString() + '\t';
                        }
                        tmpStr.chop(1);
                    }
                }
                PrintToTempFile("RefData", tmpStr, false);
            }
            break;
            case QBbgLib::QBbgAbstractResponse::ResponseType::PortfolioDataResponse:{
                Q_ASSERT(dynamic_cast<const QBbgLib::QBbgPortfolioDataResponse* const>(genres));
                const QBbgLib::QBbgPortfolioDataResponse* const res = static_cast<const QBbgLib::QBbgPortfolioDataResponse* const>(genres);
                qDebug() << res->header();
                PrintToTempFile("PortfolioData", res->header(), false);
                for (int i = 0; i < res->size(); ++i) {
                    QString tmpStr=
                        res->security(i).fullName()
                        + (res->hasPosition() ? QString("\tPosition: %1").arg(res->position(i)) : QString())
                        + (res->hasMarketValue() ? QString("\tMarket Value: %1").arg(res->marketValue(i)) : QString())
                        + (res->hasCost() ? QString("\tCost: %1").arg(res->cost(i)) : QString())
                        + (res->hasCostDate() ? ("\tCost Date: " + res->costDate(i).toString("yyyy-MM-dd")) : QString())
                        + (res->hasCostFx() ? QString("\tCost Fx Rate: %1").arg(res->costFx(i)) : QString())
                        + (res->hasWeight() ? QString("\tWeight: %1").arg(res->weight(i)) : QString())
                        ;
                    qDebug() << tmpStr;
                    PrintToTempFile("PortfolioData", tmpStr, false);
                }
            }
            break;
            case QBbgLib::QBbgAbstractResponse::ResponseType::HistoricalDataResponse:{
                Q_ASSERT(dynamic_cast<const QBbgLib::QBbgHistoricalDataResponse* const>(genres));
                const QBbgLib::QBbgHistoricalDataResponse* const res = static_cast<const QBbgLib::QBbgHistoricalDataResponse* const>(genres);
                qDebug() << res->header();
                const auto allDates = res->dates();
                for (auto i = allDates.constBegin(); i !=allDates.constEnd(); ++i) {
                    QString tmpStr = i->toString("yyyy-MM-dd")
                        + (res->periodForDate(*i).isEmpty() ? QString() : ('\t' + res->periodForDate(*i)))
                        + '\t' + res->value(*i).toString()
                        ;
                    qDebug() << tmpStr;
                    PrintToTempFile("HistoricalData", tmpStr, false);
                }
            }
            break;
            default:
                Q_UNREACHABLE(); //Unhanded Response
            }
        }
    });
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::finished, []() { qDebug() << "Finished"; });
    p_req.setField(QBbgLib::QBbgPortfolioDataRequest::PORTFOLIO_DATA);
    req.addRequest(p_req);
    //a_req.setField("Gibberish");
    //req.addRequest(a_req);
    //a_req.setSecurity(QString("invalid Mtge"));
    //req.addRequest(a_req);
    //a_req.setField("PX_LAST");
    //req.addRequest(a_req);

    //req.addRequest(h_req);
    //h_req.setField("PX_ASK");
    //req.addRequest(h_req);
    //h_req.setField("Gibberish");
    //req.addRequest(h_req);

    mainManager.startRequest(req);
    qDebug() << "Started";
    return a.exec();
}
//////////////////////////////////////////////////////////////////////////
