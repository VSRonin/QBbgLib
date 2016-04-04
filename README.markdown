# QBbgLib

This library is a [Qt](http://www.qt.io) wrapper for the [Bloomberg open API](http://www.bloomberglabs.com/api/)

A C++11 compatible compiler will be necessary.

The library supports all operating systems and both 32 and 64 bits configurations.

Licensing adheres to LGPL v3. Please see the included LICENSE file

## Building the library
To build open the Qt developer console, set the BLPPATH environmental variable to the path of the Bloomberg API.
For example, in Windows
<pre><code>
SET BLPPATH=C:\\blp\\API\\APIv3\\C++API\\v3.8.18.1
</code></pre>
Now run
<pre><code>
qmake "PREFIX=InstallDirectory"
nmake
</code></pre>
Replacing InstallDirectory with the destination where the library will be installed and nmake with your build tool name (mingw-32-make for MinGW, etc.).

## Documentation
Documentation in Qt Assistant format is packed with the repository, to build the documentation in other formats you'll need [Doxygen](http://www.doxygen.org). Just run it using the included doxyfile config.<br/>
The conceptual schema of how this library work is represented in the image<br/>
![Schema](http://i278.photobucket.com/albums/kk113/V-Ronin/Schema.png)

## Example Usage
Please refer to the example folder for code snippets that illustarte the library in action.
