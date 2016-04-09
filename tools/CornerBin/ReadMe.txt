CornerBin (c) 2011 Beem Media
Open Source
================================================================================

Officially CornernBin is as http://cornerbin.sourceforge.net. I'm including the
source code here only to have an archive with the rest of the Beem Media source
code.

Building
--------

The environment variable BEEMOUT should be set prior to building. This variable 
determines where the compiled data is built to. Go to advanced system settings
->environment variables and set BEEMOUT=D:\CornerBinOut (or similar).

The Release build will copy the executable back to the dist directory.

CornerBin uses MFC so you must install MFC alongside Visual Studio. This is
included with Visual Studio 2015 Community Edition, but is not installed by
default so make sure to run the Visual Studio setup utility with that option
checked. (You can modify existing Visual Studio 2015 installations to install
this.)
