img_lib
=======

Texture Viewer 3 with img_lib, this was originally on Sourceforge, but Github 
seems to be the place to be now. Previous versions including the COM version are
still on Sourceforge.

================================================================================
TexView3 with img_lib

(C) 2007-2012 Beem Software
Open Source
================================================================================

Building
--------

Because the TexView3 executable uses MFC you will need a Professional version of
Visual Studio (MFC is not included with Visual Studio Express Editions).

Also, the game uses the environment variable BEEMOUT to determine where
the build output is set, so this should be set (go to advanced system settings
->environment variables). Something to the effect of 
set BEEMOUT=D:\TexView3Out

The Release build will copy the executable back to the dist directory.

Notes
-----

img_lib is almost ANSI C, except I know I'm explicitely declaring functions as
__cdecl which may be MS specific. TexView3 is MFC and will required a pro
edition of Visual Studio to build (not the express version).