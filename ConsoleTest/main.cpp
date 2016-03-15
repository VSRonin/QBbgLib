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
#include <QSaveFile>
#include <QTextStream>
#include <QVariant>
void PrintToTempFile(const QString& TempFileName, const QString& Message, bool PrintTime)
{
    QSaveFile TempFile("C:/Temp/" + TempFileName + ".log");
    if (!TempFile.open(QIODevice::Append | QIODevice::Text)) 
        return;
    QTextStream TempWrite(&TempFile);
    TempWrite << (PrintTime ? QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm ") : QString()) + Message + '\n';
    TempFile.commit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QBbgLib::QBbgRequestGroup req;
    const QString fieldsRe[] = { "RTG_FITCH", "RTG_SP", "RTG_MOODY", "MTG_CASH_FLOW"};
    QList<QBbgLib::QBbgSecurity> securList;
    securList 
        << QBbgLib::QBbgSecurity("XS0743625674", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0744029843", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0551623365", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0736399055", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0739240819", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0784928300", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0785328153", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0692718801", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0693869389", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0692718637", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0693863937", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US042707AF68", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0267357340", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0208096635", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("BE0002362342", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US34988WAF14", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0238072895", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0629516211", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US82846GAD25", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0302981799", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0692717589", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0314150006", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US042706AF85", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0256207472", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0237370605", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US71419GAQ38", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US81752WAB54", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0618260920", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38405JAD19", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US042707AH25", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0267359635", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0183019032", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0488420893", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0428965866", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38406CAB90", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0236976378", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38405JCE73", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0302998926", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0314148018", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38406CAT09", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US71419QAD07", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0701039744", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0004231236", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0221342131", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US58403GAB14", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0276517710", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0182690668", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38405JCC18", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0302996557", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0271028838", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0003844948", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0266744761", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US04271AAA97", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0304467557", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("AU300MEDF010", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US43641NBH61", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US58403AAG31", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0273259472", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0563147684", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0679914860", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0273256882", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0377991007", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0377992005", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US042706AG68", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38405JAA79", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0240602929", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0240670686", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0256208363", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0004087174", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US041239BR47", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0506554152", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0003473748", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0243911756", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38405JCD90", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0302998413", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0382042002", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38741YBZ16", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US45254NPD39", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0312885017", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0291663820", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0003933998", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US38741YCD94", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US71419GAB68", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0248346974", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0270510653", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0277500285", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0004222532", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0004144892", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0309364000", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0312888011", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US71419QAH11", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0273840305", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0292898912", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0219048641", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("ES0312886015", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("IT0004658289", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0256130401", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("US74588WAA27", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0284071908", QBbgLib::QBbgSecurity::Mtge)
        << QBbgLib::QBbgSecurity("XS0454741272", QBbgLib::QBbgSecurity::Mtge)
        ;

    QBbgLib::QBbgReferenceDataRequest a_req;
    QBbgLib::QBbgPortfolioDataRequest p_req;
    //QBbgLib::QBbgHistoricalDataRequest h_req;
    p_req.setSecurity("TS-PX1915-32", QBbgLib::QBbgSecurity::Client);
    //p_req.setSecurity("U10628870-2", QBbgLib::QBbgSecurity::Client);
    //p_req.setReferenceDay(QDate(2015, 9, 3));
    QBbgLib::QBbgOverride overrides;
    overrides.setOverride("Allow dynamic cashflow calcs", "Y");
    overrides.setOverride("mtg prepay typ", "CPR");
    overrides.setOverride("YLD flag", "1");
    overrides.setOverride("prepay speed vector", "5 12S 5 72R 16");
    overrides.setOverride("Default_Type", "CDR");
    overrides.setOverride("Default_Speed_Vector", "2");
    overrides.setOverride("Loss_Severity", "25");
    overrides.setOverride("Delinquency_Vector", "13 48S 20");
    overrides.setOverride("Trigger_State", "S");
    overrides.setOverride("apply FWD rate", "N");

    for(const QBbgLib::QBbgSecurity& sec : securList){
        a_req.setSecurity(sec);
        for (auto&& fld : fieldsRe){
            a_req.setField(fld);
            req.addRequest(a_req);
        }
    }


   /* h_req.setSecurity(QBbgLib::QBbgSecurity("EUR003M", QBbgLib::QBbgSecurity::Index));
    h_req.setField("PX_LAST");
    h_req.startDate(QDate(2015, 3, 14));
    h_req.endDate(QDate(2015, 4, 14));
    h_req.nonTradingDayFill(QBbgLib::QBbgHistoricalDataRequest::ALL_CALENDAR_DAYS);*/

    
   
    //a_req.clearOverrides();
    QBbgLib::QBbgManager mainManager;
    
    QObject::connect(&mainManager, &QBbgLib::QBbgManager::recieved, [&mainManager, &req](quint32 gr, qint64 id)
    {
        const QBbgLib::QBbgAbstractResponse* genres = mainManager.getResult(gr, id);
        if (genres->hasErrors()) {
            QString tempString;
            switch (genres->responseType()) {
            case QBbgLib::QBbgAbstractResponse::ResponseType::ReferenceDataResponse:{
                auto reqForRes = req.getRequest<QBbgLib::QBbgReferenceDataRequest>(id);
                Q_ASSERT(reqForRes);
                tempString = reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + genres->errorMessage();
                break;
            }
            case QBbgLib::QBbgAbstractResponse::ResponseType::PortfolioDataResponse:{
                auto reqForRes = req.getRequest<QBbgLib::QBbgPortfolioDataRequest>(id);
                Q_ASSERT(reqForRes);
                tempString = reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + genres->errorMessage();
                break;
            }
            case QBbgLib::QBbgAbstractResponse::ResponseType::HistoricalDataResponse:{
                auto reqForRes = req.getRequest<QBbgLib::QBbgHistoricalDataRequest>(id);
                Q_ASSERT(reqForRes);
                tempString = reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + genres->errorMessage();
                break;
            }
            default:
                Q_UNREACHABLE(); //Unhandled response type
            }
            qDebug() << tempString;
            PrintToTempFile("BbgErrors", tempString, false);
        }
        else {
            switch (genres->responseType()) {
            case QBbgLib::QBbgAbstractResponse::ResponseType::ReferenceDataResponse:{
                Q_ASSERT(dynamic_cast<const QBbgLib::QBbgReferenceDataResponse* const>(genres));
                const QBbgLib::QBbgReferenceDataResponse* const res = static_cast<const QBbgLib::QBbgReferenceDataResponse* const>(genres);
                QString tmpStr;
                auto reqForRes = req.getRequest<QBbgLib::QBbgReferenceDataRequest>(id);
                Q_ASSERT(reqForRes);
                tmpStr = reqForRes->security().fullName() + " - " + reqForRes->field() + '\t';
                if (res->hasValue()) {
                    qDebug() << reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + res->header() << res->value();
                    tmpStr += res->header() + ": " + res->value().toString();
                }
                if (res->hasTable()) {
                    qDebug() << reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + res->header();
                    tmpStr += res->header();
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
                auto reqForRes = req.getRequest<QBbgLib::QBbgPortfolioDataRequest>(id);
                Q_ASSERT(reqForRes);
                qDebug() << reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + res->header();
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
                auto reqForRes = req.getRequest<QBbgLib::QBbgHistoricalDataRequest>(id);
                Q_ASSERT(reqForRes);
                qDebug() << reqForRes->security().fullName() + " - " + reqForRes->field() + '\t' + res->header();
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
    p_req.setSecurity("TS-PX1915-14", QBbgLib::QBbgSecurity::Client);
    //req.addRequest(p_req);
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
