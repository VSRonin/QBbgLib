
#include <QCoreApplication>
#include <Includes/QBbgReferenceData>
#include <Includes/QBbgManager>
#include <iostream>
#include <QVariant>

void singleRequest(QBbgLib::QBbgManager& bbgManager)
{
    // Create a reference data request
    QBbgLib::QBbgReferenceDataRequest req;

    // Set the security to download
    req.setSecurity(QBbgLib::QBbgSecurity("US92857WBD11",QBbgLib::QBbgSecurity::Corp)); // VOD 4 3/8 02/19/43 Corp

    // Set the field to download
    req.setField("SECURITY_NAME"); // Single Value
    // req.setField("DES_CASH_FLOW"); // Table, uncomment to demonstrate
    
    // Send the request and wait for the response
    const QBbgLib::QBbgReferenceDataResponse * const resp = bbgManager.processRequest(req);

    // Check if we recieved an error
    if (resp->hasErrors()) {
        std::cout << (QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString())).toStdString();
    }
    else {
        // Check if the value requested was a table
        if (resp->hasTable()){
            std::cout << (QStringLiteral("%1 for %2").arg(resp->header()).arg(req.security().fullName())).toStdString() << std::endl;
            // Print the table headers
            // Iterate over the columns
            for (int i = 0; i < resp->columns(); ++i){
                // Get the first row element
                const QBbgLib::QBbgReferenceDataResponse * const tableValue = resp->getTableValue(0, i);
                if (tableValue->hasErrors())
                    std::cout << "N/A";
                else
                    // Print the header for the current value
                    std::cout << tableValue->header().toStdString();
                std::cout << '\t';
            }
            std::cout << std::endl;

            // Print the actual values
            // Iterate over the rows
            for (int j = 0; j < resp->rows(); ++j) {
                // Iterate over the columns
                for (int i = 0; i < resp->columns(); ++i) {
                    // Get the relevant result
                    const QBbgLib::QBbgReferenceDataResponse * const tableValue = resp->getTableValue(j, i);
                    if (tableValue->hasErrors())
                        std::cout << "N/A";
                    else
                        // Print the value
                        std::cout << tableValue->value().toString().toStdString();
                    std::cout << '\t';
                }
                std::cout << std::endl;
            }

        }
        else {
            // Print single value
            std::cout << (QStringLiteral("%1 for %2 is %3").arg(resp->header()).arg(req.security().fullName()).arg(resp->value().toString())).toStdString();
        }
    }
}

int main(int argc, char *argv[])
{
    // Always create a QCoreApplication or QApplication before sending any request
    QCoreApplication a(argc, argv);
    // Create the main manager
    QBbgLib::QBbgManager bbgManager;
   
    singleRequest(bbgManager);
    return 0;
}
