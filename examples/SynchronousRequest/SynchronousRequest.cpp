#include <QCoreApplication>
#include <Includes/QBbgReferenceData>
#include <Includes/QBbgHistoricalData>
#include <Includes/QBbgPortfolioData>
#include <Includes/QBbgRequestGroup>
#include <Includes/QBbgManager>
#include <QVariant>

#include <QDebug> // Used to print to console

void singleReferenceDataRequest(QBbgLib::QBbgManager& bbgManager);
void singleHistoricalDataRequest(QBbgLib::QBbgManager& bbgManager);
void singlePortfolioDataRequest(QBbgLib::QBbgManager& bbgManager);
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
        qDebug() << QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString());
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
            qDebug() << headerString;

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
                qDebug() << valueString;
            }

        }
        else {
            // Print single value
            qDebug() << QStringLiteral("%1 for %2 is %3").arg(resp->header()).arg(req.security().fullName()).arg(resp->value().toString());
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
        qDebug() << QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString());
    }
    else {
        // Print all the values in the series
        qDebug() << "Date\t" << resp->header();
        for (int i = 0; i < resp->size(); ++i) {
            qDebug() << resp->date(i).toString(Qt::DefaultLocaleShortDate) << '\t' << resp->value(i).toString();
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
        qDebug() << QStringLiteral("Error %1 - %2").arg(resp->errorMessage()).arg(resp->errorString());
    }
    else {
        // Print all the values in the series
        qDebug() << "Security\tNominal";
        for (int i = 0; i < resp->size(); ++i) {
            qDebug() << resp->security(i).fullName() << '\t' << resp->position(i);
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
            referenceDictionary.insert(
                QPair<size_t, size_t>(i, j)
                , allRequests.addRequest(refData_req)
            );
        }
    }

    // You can add historical and portfolio requests to the same group too if you want

    // Send the request and wait for the response
    const quint32 resultGroupID = bbgManager.processRequestID(allRequests);
   
    // Print The result
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
                qDebug() << referenceSecurities[i] << " - " << referenceFields[j] << ": " << QStringLiteral("Error %1 - %2").arg(currentResult->errorMessage()).arg(currentResult->errorString());
            }
            else {
                // Check if the result is a table or a single value
                if (currentResult->hasValue()) {
                    // Print out the value
                    qDebug() << referenceSecurities[i] << " - " << referenceFields[j] << ": " << currentResult->value();
                }
                else if (currentResult->hasTable()) {
                    qDebug() << referenceSecurities[i] << " - " << referenceFields[j];
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
                    qDebug() << headerString;

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
                        qDebug() << valueString;
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
