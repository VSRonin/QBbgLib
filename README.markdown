# QBbgLib

This library is a [Qt](http://www.qt.io) wrapper for the [Bloomberg open API](http://www.bloomberglabs.com/api/).  
This layer removes the need for magic strings that are often poorly documented, takes care of handling services for you and give a unique correlation (using a pair of integers) between requests and responses.

The library supports all operating systems and both 32 and 64 bits configurations.

Licensing adheres to LGPL v3. Please see the included LICENSE file

## Building the library
A C++11 compatible compiler will be necessary.

To build open the Qt developer console, set the BLPPATH environmental variable to the path of the Bloomberg API.
For example, in Windows

    SET BLPPATH=C:\blp\API\APIv3\C++API\v3.8.18.1

Now run

    qmake "PREFIX=InstallDirectory"
    nmake

Replacing InstallDirectory with the destination where the library will be installed and nmake with your build tool name (mingw-32-make for MinGW, etc.).

## Documentation
Documentation in Qt Assistant format is packed with the repository, it is also available online at [lbeldi.bitbucket.org/QBbgLib](http://lbeldi.bitbucket.org/QBbgLib/).  
To build the documentation in other formats you'll need [Doxygen](http://www.doxygen.org). Just run it using the included doxyfile config.  
The conceptual schema of how this library work is represented in the image

![Schema](http://i278.photobucket.com/albums/kk113/V-Ronin/Schema.png)

## Example Usage
Please refer to the example folder for code snippets that illustarte the library in action.

## Current Development
This library is still under development. This is a list of what has been done, what needs to be done and what could be done.

* Implemented Functionalities
    * Reference Data ( BDP() and BDS() in excel ) ![100% ready](http://progressed.io/bar/100?title=done) 
    * Historical Data ( BDH() in excel ) ![100% ready](http://progressed.io/bar/100?title=done) 
    * Portfolio Data ( BDS() in excel using a Client security ) ![100% ready](http://progressed.io/bar/100?title=done) 
    * Intraday Tick Data ( BDH() in excel using IntrRw=true ) ![100% ready](http://progressed.io/bar/100?title=done) 
* Missing Functionalities
    * Intraday Bar Data ( BDH() in excel specifying BarType ) ![50% ready](http://progressed.io/bar/50) 
    * EQS ( BEQS() in excel ) ![10% ready](http://progressed.io/bar/10)
    * Field Info ( BFieldInfo() in excel ) ![0% ready](http://progressed.io/bar/0)
    * Field Search ( FLDS on the terminal ) ![0% ready](http://progressed.io/bar/0)
    * Categorized Field Search ![0% ready](http://progressed.io/bar/0)
    * Real Time Data ![0% ready](http://progressed.io/bar/0)
    * API Authorisation ![0% ready](http://progressed.io/bar/0)
* Missing and Undocumented Functionalities ( these are available on the API but there is no mention of them in the docs )
    * Download forward curves ![0% ready](http://progressed.io/bar/0)
* Whishlist
    * Use [CMake](https://cmake.org/) instead of qmake as build tool
    * Make the library depend only on STL and possibly [Boost](http://www.boost.org/) and make Qt only optional
    * Make library usable from [QML](http://doc.qt.io/qt-5/qtqml-index.html)
    * C++/CLI overlay of the API to make it available to .Net programming languages (C#, VB.Net, etc.)
    * Find a way to build reliable unit tests that do not break in time

## Reference
The documentation on the Bloomberg API running underneath this library can be found on the [Bloomberg Open API website](http://www.bloomberglabs.com/api/documentation/)

