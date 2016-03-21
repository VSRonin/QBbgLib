# QBbgLib

This library is a [Qt](http://www.qt.io) wrapper for the [Bloomberg open API](http://www.bloomberglabs.com/api/)

A C++11 compatible compiler will be necessary.

The library supports all operating systems and both 32 and 64 bits configurations.

Licensing adheres to LGPL v3. Please see the included LICENSE file

## Building the library
To build open the Qt developer console, set the BLPPATH environmental variable to the path of the Bloomberg API.
For example, in Windows
<pre><code>
SET BLPPATH=C:\blp\API\APIv3\C++API\v3.8.18.1
</code></pre>
Now run
<pre><code>
qmake "PREFIX=&lt;InstallDirectory&gt;"
make
</code></pre>
Replacing &lt;InstallDirectory&gt; with the destination where the library will be installed and make with your build tool name (nmake for MSVC, etc.).

## Example Usage
Please refer to the example folder for code snippets that illustarte the library in action.
