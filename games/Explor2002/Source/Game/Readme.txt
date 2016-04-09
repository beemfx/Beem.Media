Explor Copyright (c) 2002, Blaine Myers by Beem Software

Author: Blaine Myers for Beem Software

Language: C++ Win32, DirectX API

Version x.xxW

Log:

March 12, 2002

Created the new CGameMap class which is a modified version of the
ExplorMap class used in ExplorED.  I've removed some of the unusable
functions, and added a new function: generateTFront(...) which
generates the tiles-in-front array.

There is no game yet.  As soon as I have the will I will get the 
wall art, and then try to rig up a game similar to the current DOS beta,
except with DirectDraw instead.

March 14, 2002

The 3D Rendering functions have been built, though are not complete.
They will take a tbase array, and load the appropriate tiles onto the
secondary surface.  I have not generated a game yet though.

I also changed the Tile manager so it only has three tile objects.  It
adjusts their size appropriately when the tile manager draw function is
called.

March 15, 2002

The engine is complete.  Though there is a problem with the ReleaseSurfaces()
function in main.cpp.  It seems that calling the Release for the TileSet Class
doesn't work correctly, so I'm not having them be released.  This will make it so
memory is still being occupied even when the program ends, I hope to fix this.  So
for now it just doesn't release the memory.

I'm not really satisfied with the engine, it didn't turn out how I hoped and a great
deal of the rendering is not correct.  I can redo the rendering functions to fix this,
but I don't really want to do the work, after all this program will probably never
really go anywhere.

April 03, 2002

The engine now releases properly, which eliminates that goddamned bug.

Old Log: (From the dos stages)

'Here it is the BETA release of EXPLOR it's not much but a good
'start.  You probably won't want to play it for much more than a
'couple of minutes, probably less actually, but it's worth your
'time.

'The game is completely based off Might and Magic though there are other
'games like it).  I had Might and Magic for nintendo but it just wouldn't
'save right so I decided to make my own game.  It's rendered 3D just like
'the first two might and magic games.  It's pretty cool and I'm proud of
'myself.  I actually only spent three days on it.  The first two I spent
'an average of 12 hours a day on it.  (Why? Well I was bored.)  Anyway here
'it is.

'Log

'I originally had plans for this program but now it is deemed as junk
'It has a story and credits but no game I doubt that it ever will have
'a game because Joe's Copter II is a lot better than any exploring game
'maybe when I get the internet I will be able to allow other people to
'use this piece of junk I don't want to throw it away because I spent
'so much time on it.

'That's old news I'm going to reincorporate EXPLOR and start the project
'it may end up junk anyways.

'Damn!!! It works perfectly.

'Well since the ASCII graphics interface didn't work right I changed
'To regular VGA graphics.  I also incorporated the loadmap from venture.bas
'I'm sure the loser author won't care. Too much! Anyways he'll never know.
'The load map works extremely well.  I figure if I want a different map
'loaded I can just use different subs for different levels.  Anyway I have
'to change the movement arrow to VGA graphics rather than ASCII then I will
'have to redefine the movement so it stops when approaching a wall.
'I don't want to do that today though. It will actually take a while.
'Turnleft and Turnright will not to be changed but calcforward and calcbackward
'will. Placechar will need to be changed also. What the hell I did it today
'The engine is working fine all I need to do is write the code that will
'make it not be able to pass through walls.  I'm actually proud of all I
'have accomplished today.
'I have changed the variable from 4.52 to con which equals the same thing.
'I have established borders for the character.
'I developed a method to stop the arrow from passing through walls now
'all thats left is to develop the 3D rendering.
'Well all done.  The 3D rendering works fine, it's extremely buggy though.
'I'm not going to do anymore with this program, I've done enough.
'It takes so much memory qbasic 4.5 can't convert it to an .exe I'm
'kind of disapointed.  No matter it will be fine.
'I made view1 look a lot better creating 0.02b.

'I've started working on the project again:

'Now supports new map format.  That is the map format formed by ExplorED.
'Currently only supports 10's and 1's.  I developed my own map loader will
'work better in the future.

'I've created the facing north rendering.  It seems to work so far
'but I haven't really tested it.  Will create east and south
'rendering later.  Rendering only works if within 4 edge of map
'need to fix that.
'
'Current north rendering was deleted.  I created a new method so it
'calculates an array by choosing the direction.  This array is tfront%
'
'I have created calculations for North, South, East, and West
'
'Made the 3D rendering sub.  It seems to work but actually probably has
'more than a dozen errors.  Well maybe not a dozen.  Any way need to
'make the movement subs.  Will probably port them over from.  V 0.04B
'May improve the render3D sub later so it only loads the images it has
'to.
'
'I brought over the moveinput sub and renamed it takeinput.  The 3D rendering
'seems to work perfectly.  It flashes a lot, I can fix this if I decide to
'redo the 3D rendering sub to only place the tiles that will show up in the
'end.
'
'Need to make it so one cannot pass through a wall.
'Made walls now not possible to pass through, unless you are inside one.
'Also fixed a bug where facing north fucked up on tfront%(10) and a bug
'where direction was displayed wrong.
'
'Explor is just about where it was before I redid the engine.  An automap
'as well as the menu's are still missing.  When I redo the credits I will
'probably drop most of the bullshit and do a more reasonable list of
'creators.  Namely me with a special thanks to Jon Van Caneghem and Craig
'Decker.
'
'Redid automap feature it works pretty well.  A little better than before
'but mostly the same.  Used some of the same code.
'
'It will be necessary to add door tiles if I really want to get anywhere
'decent.
'
'Updated some code deficiencies, to make future developments easier.
'What I need to do now is further the ExplorED Editor to do more things
'then come back to this code.
'Damn I love this code it just works so fucking well.
'
'Now supports Map version beta2: That is 0's instead of 1's for empty space
'
'Doors are now read by explor.  Made some major fixes for moveing forward
'and backward.  As well as automap display.
'
'Expected memory issues discovered when dimensioning the doors.  Its just too
'damn big.  So now for doors it simply places the preset version of the
'wall image.  There is no fucking way we're going to leave that final.  We'll
'figure something out.  We don't know what yet maybe we should invent a
'fucking bitmap loader.  BLOAD and BSAVE may also work !!! I'll look into
'what they are capable of doing.  Current skyground is really sloppy this can
'easily be fixed when we fix the door sprites.
'
'I've done the BLOAD thing for the wall sprites.  Now nothing is displayed
'for the doors.  I need to write up some graphics and do the same thing
'for them as I did for the walls.  To load a particular wall position you
'simply type loadwal(wallnumber) where wall number is the wall that is true
'check out render3D to see exactly how it is done.  I'm pretty satisfied
'with it.
'
'I'm pretty fucking satisfied that I learned how to use BLOAD and BSAVE
'the program wallgen generates the wallimages.
'
'Now use CHDIR to set the current directory istead of using dir$ + ""
'this is a little more effective as only one line needs to be remarked
'out for the compile and no longer need to use dir$

'I'm looking to port the code over to C++ so I can use some of the same
'features used in explorED.  I plan on converting this program to a
'DirectX API.  Double Buffering is something I want to do for the display.
'That would reduce flashing significantly.  I don't know how to access video
'memory directly in a QB environment, so I plan on converting to C++

'Created a new function called tbase% it takes x and y values as perameters
'and returns the value of tbase this replaced using t = ....... in the
'different functions.  With this new function it should be easier to
'make any map size acceptable.

'Updated program so now the actuall first element of the tile arrays is
'storred in 0 instead of 1.