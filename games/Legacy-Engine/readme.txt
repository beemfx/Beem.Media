Legacy 3D Engine
================
Engineered by Blaine Myers

(c) 2008 Beem Media

The Legacy Engine was my first 3D engine. It's not very good and is not meant
to be representative of my skills as an engineer. The engine was scrapped in 
2008. It was developed before I knew anything about software engineering and so
it has some really bad code. There are some good ideas in it, and it had some 
interesting tools (albeit unecessary), namely the LMEdit tool and various 
plugins.

It also featured a math library written in assembly (but it was basically a
less featured copy of d3dx9 math).

The code never really came along far enough to even make a basic game demo in
it. It supported various physics engines, the primary was meant to be PhysX
though that is no longer supported by this source (since I'm not even sure what
version of PhysX it was originally built with.) The provided code works with
the Newton Game Dynamics physics engine and the in-house physics engine (though
being that there is no gameplay, everything seems to be pretty chaotic in the
demo).

I'm  keeping the code for novelty purposes, but it has been surpassed by the
Emergence Engine (which is not open source at this time).

The executables in the base directory work and were built with Visual Studio
2015 (except for LPaKager) so they'll require a recent version of the Visual
C++ runtimes installed. The executable for LPaKager doesn't have source code
any more, and it is the only version of the software that will open the game
data in baseuncmp (besides the game client itself).

The Scrapped directory has old version or obsolete code (or stuff I didn't want
to build for this distribution). I didn't know about source control when I wrote
this engine so I originally dumped old files into that directory.
