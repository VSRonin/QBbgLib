
#include <QCoreApplication>
#include <Includes/QBbgReferenceData>
#include <Includes/QBbgManager>
#include <iostream>
#include <QVariant>
int main(int argc, char *argv[])
{
    // Always create a QCoreApplication or QApplication before sending any request
    QCoreApplication a(argc, argv);
    QBbgLib::QBbgManager bbgManager;
    QBbgLib::QBbgReferenceDataRequest req;
    req.setSecurity(QBbgLib::QBbgSecurity("IBM US Equity"));
    req.setField("ID_ISIN");
    const QBbgLib::QBbgReferenceDataResponse * const resp = bbgManager.processRequest(req);
    if (resp->hasErrors()){
        std::cout << (QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString())).toStdString();
    }
    else{
        std::cout << (QStringLiteral("ISIN for %1 is %2").arg(req.security().fullName()).arg(resp->value().toString())).toStdString();
    }
    return 0;
}
