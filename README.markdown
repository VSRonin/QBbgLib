# QBbgLib

This library is a [Qt](http://www.qt.io) wrapper for the [Bloomberg open API](http://www.bloomberglabs.com/api/)

A C++11 compatible compiler will be necessary

Licensing adheres to LGPL v3. Please see the included LICENSE file

## Building the library
### Windows, MSVC 2013 or newer
Run the following commands in the command prompt replacing:
    <ul>
    <li> &lt;PathToQt&gt; - Path to the Qt library, e.g. C:\Qt\5.5\msvc2013</li>
    <li> &lt;PathToVisualStudio&gt; - Path to the Visual Studio Binaries, e.g. C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC</li>
    <li> &lt;PathToBloombergAPI&gt; - Path to the Bloomberg API, e.g. C:\blp\API\APIv3\C++API\v3.8.18.1</li>
    <li> &lt;InstallDirectory&gt; - Directory where the library will be installed</li>
    </ul>
```
pushd C:\
CALL "<PathToQt>\bin\qtenv2.bat"
CALL "<PathToVisualStudio>\vcvarsall.bat"
popd
echo on
SET BLPPATH=<PathToBloombergAPI>
qmake "PREFIX=<InstallDirectory>"
nmake
nmake install
```
### Windows, MinGW
Run the following commands in the MinGW command prompt replacing:
    <ul>
    <li> &lt;PathToQt&gt; - Path to the Qt library, e.g. C:\Qt\5.5\msvc2013</li>
    <li> &lt;PathToBloombergAPI&gt; - Path to the Bloomberg API, e.g. C:\blp\API\APIv3\C++API\v3.8.18.1</li>
    <li> &lt;InstallDirectory&gt; - Directory where the library will be installed</li>
    </ul>
```
pushd C:\
CALL "<PathToQt>\bin\qtenv2.bat"
popd
echo on
SET BLPPATH=<PathToBloombergAPI>
qmake "PREFIX=<InstallDirectory>"
make
make install
```
### Linux, gcc
TODO, set BLPPATH environmental variable to the Bloomberg API directory and run qmake and make

### Mac OS, LLVM 
TODO, set BLPPATH environmental variable to the Bloomberg API directory and run qmake and make

## Example Usage
### Synchronous API
TODO

### Asynchronous API
TODO
