#include <QCoreApplication>
#include <Includes/QBbgReferenceData>
#include <Includes/QBbgHistoricalData>
#include <Includes/QBbgPortfolioData>
#include <Includes/QBbgRequestGroup>
#include <Includes/QBbgIntradayTick>
#include <Includes/QBbgManager>
#include <QVariant>

#include <iostream>

void singleReferenceDataRequest(QBbgLib::QBbgManager& bbgManager);
void singleHistoricalDataRequest(QBbgLib::QBbgManager& bbgManager);
void singlePortfolioDataRequest(QBbgLib::QBbgManager& bbgManager);
void singleIntradayTickRequest(QBbgLib::QBbgManager& bbgManager);
void multipleRequests(QBbgLib::QBbgManager& bbgManager);


int main(int argc, char *argv[])
{
    // Always create a QCoreApplication or QApplication before sending any request
    QCoreApplication a(argc, argv);
    // Create the main manager
    QBbgLib::QBbgManager bbgManager;
   
    singleReferenceDataRequest(bbgManager);
    singleHistoricalDataRequest(bbgManager);
    singlePortfolioDataRequest(bbgManager);
    singleIntradayTickRequest(bbgManager);
    multipleRequests(bbgManager);

    return 0;
}


void singleReferenceDataRequest(QBbgLib::QBbgManager& bbgManager)
{
    // Create a reference data request
    QBbgLib::QBbgReferenceDataRequest req;

    // Set the security to download
    req.setSecurity(QBbgLib::QBbgSecurity("US92857WBD11", QBbgLib::QBbgSecurity::Corp)); // VOD 4 3/8 02/19/43 Corp

    // Set the field to download
    req.setField("SECURITY_NAME"); // Single Value
    // req.setField("DES_CASH_FLOW"); // Table, uncomment to demonstrate

    // Send the request and wait for the response
    const QBbgLib::QBbgReferenceDataResponse * const resp = bbgManager.processRequest(req);

    // Check if we recieved an error
    if (resp->hasErrors()) {
        std::cout << std::endl <<  qPrintable(QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString()));
    }
    else {
        // Check if the value requested was a table
        if (resp->hasTable()) {
            QString headerString;
            for (int i = 0; i < resp->columns(); ++i) {
                // Get the first row element
                const QBbgLib::QBbgReferenceDataResponse * const tableValue = resp->getTableValue(0, i);
                if (tableValue->hasErrors())
                    headerString += "N/A";
                else
                    // Print the header for the current value
                    headerString += tableValue->header();
                headerString += '\t';
            }
            std::cout << std::endl << qPrintable(headerString);

            // Print the actual values
            // Iterate over the rows
            for (int j = 0; j < resp->rows(); ++j) {
                // Iterate over the columns
                QString valueString;
                for (int i = 0; i < resp->columns(); ++i) {
                    // Get the relevant result
                    const QBbgLib::QBbgReferenceDataResponse * const tableValue = resp->getTableValue(j, i);
                    if (tableValue->hasErrors())
                        valueString += "N/A";
                    else
                        // Print the value
                        valueString += tableValue->value().toString();
                    valueString += '\t';
                }
                std::cout << std::endl << qPrintable(valueString);
            }

        }
        else {
            // Print single value
            std::cout << std::endl << qPrintable(QStringLiteral("%1 for %2 is %3").arg(resp->header()).arg(req.security().fullName()).arg(resp->value().toString()));
        }
    }
}

void singleHistoricalDataRequest(QBbgLib::QBbgManager& bbgManager)
{
    // Create an historical data request
    QBbgLib::QBbgHistoricalDataRequest req;

    // Set the security to download
    req.setSecurity(QBbgLib::QBbgSecurity("BBG000BLNNH6", QBbgLib::QBbgSecurity::Equity)); // IBM US Equity

    // Set the field to download
    req.setField("PX_LAST");

    // Set the start of the series (3 years ago)
    req.setStartDate(QDate::currentDate().addYears(-3));

    // Set the end of the series (today)
    req.setEndDate(QDate::currentDate());

    // Send the request and wait for the response
    const QBbgLib::QBbgHistoricalDataResponse * const resp = bbgManager.processRequest(req);

    // Check if we recieved an error
    if (resp->hasErrors()) {
        std::cout << std::endl << qPrintable(QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString()));
    }
    else {
        // Print all the values in the series
        std::cout << std::endl << "Date\t" << qPrintable(resp->header());
        for (int i = 0; i < resp->size(); ++i) {
            std::cout << std::endl << qPrintable(resp->date(i).toString(Qt::DefaultLocaleShortDate)) << '\t' << qPrintable(resp->value(i).toString());
        }
    }
}

void singlePortfolioDataRequest(QBbgLib::QBbgManager& bbgManager)
{
    // Create an historical data request
    QBbgLib::QBbgPortfolioDataRequest req;

    // Set the security to download
    req.setSecurity(QBbgLib::QBbgSecurity("UXXXXXXX-X", QBbgLib::QBbgSecurity::Client)); // Change this to a portfolio ID you set up in PRTU

    // Set the field to download
    req.setField(QBbgLib::QBbgPortfolioDataRequest::PortfolioFields::PORTFOLIO_MPOSITION);

    // Send the request and wait for the response
    const QBbgLib::QBbgPortfolioDataResponse * const resp = bbgManager.processRequest(req);

    // Check if we recieved an error
    if (resp->hasErrors()) {
        std::cout << std::endl << qPrintable(QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString()));
    }
    else {
        // Print all the values in the series
        std::cout << std::endl << "Security\tNominal";
        for (int i = 0; i < resp->size(); ++i) {
            std::cout << std::endl << qPrintable(resp->security(i).fullName()) << '\t' << resp->position(i);
        }
    }
}

void singleIntradayTickRequest(QBbgLib::QBbgManager& bbgManager)
{
    // Create a tick-by-tick data request
    QBbgLib::QBbgIntradayTickRequest req;

    // Set the security to download
    req.setSecurity(QBbgLib::QBbgSecurity("BBG000BLNNH6", QBbgLib::QBbgSecurity::Equity)); // IBM US Equity

    // Set the events to download
    req.setEventType(QBbgLib::QBbgIntradayTickRequest::EventType::BID);

    // Set the start of the series (3 days ago)
    req.setStartDateTime(QDateTime::currentDateTime().addDays(-3));

    // Set the end of the series (2 days ago)
    req.setEndDateTime(QDateTime::currentDateTime().addDays(-2));

    // Send the request and wait for the response
    const QBbgLib::QBbgIntradayTickResponse * const resp = bbgManager.processRequest(req);

    // Check if we recieved an error
    if (resp->hasErrors()) {
        std::cout << std::endl << qPrintable(QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString()));
    }
    else {
        // Print all the values in the series
        std::cout << std::endl << "Date\tValue\tSize";
        for (int i = 0; i < resp->size(); ++i) {
            std::cout << std::endl << qPrintable(resp->dateTime(i).toString(Qt::DefaultLocaleShortDate)) << '\t' << resp->value(i) << '\t' << resp->tickSize(i);
        }
    }
}

void multipleRequests(QBbgLib::QBbgManager& bbgManager)
{
    using namespace QBbgLib;
    // This will collect all requests
    QBbgRequestGroup allRequests;


    QBbgReferenceDataRequest refData_req;

    const QString referenceSecurities[] = { "US92857WBD11", "US88579YAH45", "XS0911388832" };
    const QString referenceFields[] = { "RTG_FITCH", "RTG_SP", "RTG_MOODY", "DES_CASH_FLOW" };

    QBbgSecurity tempSecurity;
    // All securities will have a Corp extension
    tempSecurity.setExtension(QBbgSecurity::Corp);

    /*
    We will store the ID of the request using the indexes of security and field in the array as key
    */
    QHash<QPair<size_t, size_t>, qint64> referenceDictionary;

    for (size_t i = 0; i < std::extent<decltype(referenceSecurities)>::value; ++i) {
        //Iterate over the securities
        for (size_t j = 0; j < std::extent<decltype(referenceFields)>::value; ++j) {
            // Iterate over the fields

            // Set the security name
            tempSecurity.setName(referenceSecurities[i]);

            //Assign the security to the request
            refData_req.setSecurity(tempSecurity);
            refData_req.setField(referenceFields[j]);

            // Add the request to the container and store its ID
            const QPair<size_t, size_t> dictionaryKey(i, j);
            referenceDictionary.insert(
                dictionaryKey
                , allRequests.addRequest(refData_req)
            );
            // Assert if the added request was invalid
            Q_ASSERT(referenceDictionary.value(dictionaryKey) != QBbgAbstractRequest::InvalidID);
        }
    }

    // You can add historical and portfolio requests to the same group too if you want
    //In this case we'll get the 3m EURIBOR rate as of 05/05/2015
    QBbgHistoricalDataRequest histRq;
    histRq.setSecurity(QBbgSecurity("EUR003M", QBbgSecurity::Index));
    histRq.setField("PX_LAST");
    histRq.setStartDate(QDate(2015, 5, 5));
    histRq.setEndDate(QDate(2015, 5, 5));
    const qint64 euriborID = allRequests.addRequest(histRq);
    // Assert if the added request was invalid
    Q_ASSERT(euriborID != QBbgAbstractRequest::InvalidID);


    // Send the request and wait for the response
    const quint32 resultGroupID = bbgManager.processRequestID(allRequests);
   
    // Print The result

    // Historical Result
    const QBbgHistoricalDataResponse* const euriborResult = bbgManager.getResult<QBbgHistoricalDataResponse>(resultGroupID, euriborID);
    if (euriborResult->hasErrors())
        std::cout << std::endl << qPrintable(QStringLiteral("Unable to download historical 3m EURIBOR. Error %1: %2").arg(euriborResult->errorString()).arg(euriborResult->errorMessage()));
    else
        std::cout << std::endl << qPrintable(QStringLiteral("3m EURIBOR as of %1 = %2").arg(euriborResult->date(0).toString(Qt::DefaultLocaleShortDate)).arg(euriborResult->value(0).toDouble()));

    // Reference data results
    for (size_t i = 0; i < std::extent<decltype(referenceSecurities)>::value; ++i) {
        for (size_t j = 0; j < std::extent<decltype(referenceFields)>::value; ++j) {
            // The key in the ID dictionary
            const QPair<size_t, size_t> resultKey(i, j);
            // We retrieve the result with ID referenceDictionary.value(resultKey) in the group resultGroupID as a QBbgReferenceDataResponse
            const QBbgReferenceDataResponse* const currentResult =
                bbgManager.getResult<QBbgReferenceDataResponse>(
                    resultGroupID
                    , referenceDictionary.value(resultKey, QBbgAbstractRequest::InvalidID)
                );
            Q_ASSERT(currentResult); // Should always pass
            if (currentResult->hasErrors()){
                // Check for errors
                std::cout << std::endl << qPrintable(referenceSecurities[i]) << " - " << qPrintable(referenceFields[j]) << ": " << qPrintable(QStringLiteral("Error %1 - %2").arg(currentResult->errorMessage()).arg(currentResult->errorString()));
            }
            else {
                // Check if the result is a table or a single value
                if (currentResult->hasValue()) {
                    // Print out the value
                    std::cout << std::endl << qPrintable(referenceSecurities[i]) << " - " << qPrintable(referenceFields[j]) << ": " << qPrintable(currentResult->value().toString());
                }
                else if (currentResult->hasTable()) {
                    std::cout << std::endl << qPrintable(referenceSecurities[i]) << " - " << qPrintable(referenceFields[j]);
                    // Print the table headers
                    // Iterate over the columns
                    QString headerString;
                    for (int i = 0; i < currentResult->columns(); ++i) {
                        // Get the first row element
                        const QBbgLib::QBbgReferenceDataResponse * const tableValue = currentResult->getTableValue(0, i);
                        if (tableValue->hasErrors())
                            headerString += "N/A";
                        else
                            // Print the header for the current value
                            headerString += tableValue->header();
                        headerString+= '\t';
                    }
                    std::cout << std::endl << qPrintable(headerString);

                    // Print the actual values
                    // Iterate over the rows
                    for (int j = 0; j < currentResult->rows(); ++j) {
                        // Iterate over the columns
                        QString valueString;
                        for (int i = 0; i < currentResult->columns(); ++i) {
                            // Get the relevant result
                            const QBbgLib::QBbgReferenceDataResponse * const tableValue = currentResult->getTableValue(j, i);
                            if (tableValue->hasErrors())
                                valueString += "N/A";
                            else
                                // Print the value
                                valueString += tableValue->value().toString();
                            valueString += '\t';
                        }
                        std::cout << std::endl << qPrintable(valueString);
                    }
                }
                else {
                    Q_UNREACHABLE();
                    //If currentResult->hasErrors() is false, either currentResult->hasValue() or currentResult->hasTable() will be true
                }
            }
        }
    }
}
