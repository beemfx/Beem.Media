QInstall
========

Quick and Dirty Application Installer.

Quick and Dirty Application Installer Copyright (c) 2002, 2003 Blaine Myers

------
Usage:
------
   Basically this program just copies files from one location to another
future version may allow uninstall, and browse ability.

Ender User:
   Just active QInstall from the installation directory, everything
should take itself from there.

Developer:
   In order the create an installation process there must be a file
called QInstall.ini in the same directory as QInstall.  QInstall.ini must
contain four statements (each statement ends with a semicolin ';'.
Return carriages will be ingnored so you can put statements in separate
lines.

   All statments look like this:
      statmentidentifier="statementstring";
   
   Four statmentidentifiers must be defined:
      name /* The name of the app */
      installto /* Directory to install to*/
      installfrom /* directory to install from better not have trailing slash*/
      runonexit /* the app to run when the installation completes */

installto and installfrom can have parse strings.  A parse strings
will be replace by the operating system.  The following parse strings
are available:

%defaultdrive% /* Is replace with the same drive as windows is installed to */
%currentdir% /* The currently active directory */

Remeber all lines must end with a semicolin ';'.  This readme file
should not be included with distributed programs.

Example of usage:

name        = "QInstall Demo Application";
installto   = "%defaultdrive%\DemoApp\";
installfrom = "%currentdir%\DemoInstall\";
runonexit   = "QTestApp.exe";

Notice:
  Browse button does not do anything in this version.

------
About:
------
   This is basically a bang up job I made so I could have an installer
for old floppy-disk programs that I copied onto CD-ROM.  In the future
I plan on developing a more functional installer, which will be easier
to use and have more features.


----------------
Version History:
----------------

0.50 (March 06, 2003)
   Directory and sub directories copied.  Program is laid
   out better.

0.01 (December 31 2002)
   A banged up job, browse button doesn't do anything