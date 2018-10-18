DECLARE FUNCTION tbase% (tx AS INTEGER, ty AS INTEGER)
DECLARE SUB showproperty ()
DECLARE SUB loadwall (wallchoice AS INTEGER)
DECLARE SUB movebackward ()
DECLARE SUB moveforward ()
DECLARE SUB automap ()
DECLARE SUB otherimages ()
DECLARE SUB clearviewport ()
DECLARE SUB skyground ()
DECLARE SUB showstats ()
DECLARE SUB takeinput ()
DECLARE SUB render3d ()
DECLARE SUB gettilesinfront ()
DECLARE SUB globalconsts ()
DECLARE SUB interface ()
DECLARE SUB loadmap (mapname$)
'ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
'บ                                                                 บ
'บ                  E.X.P.L.O.R                                    บ
'บ                                                                 บ
'บ                         A New World                             บ
'บ                                                                 บ
'บ                                      v. BETA 0.04, x.xx         บ
'บ                                                                 บ
'บ           Copyright (c) 2001, Beem software by Blaine Myers     บ
'บ                                                                 บ
'ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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

'Dang!!! It works perfectly.

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
'Also fixed a bug where facing north messed up on tfront%(10) and a bug
'where direction was displayed wrong.
'
'Explor is just about where it was before I redid the engine.  An automap
'as well as the menu's are still missing.  When I redo the credits I will
'probably drop most of the stuff and do a more reasonable list of
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
'I love this code it just works so well.
'
'Now supports Map version beta2: That is 0's instead of 1's for empty space
'
'Doors are now read by explor.  Made some major fixes for moveing forward
'and backward.  As well as automap display.
'
'Expected memory issues discovered when dimensioning the doors.  Its just too
'big.  So now for doors it simply places the preset version of the
'wall image.  There is no way we're going to leave that final.  We'll
'figure something out.  We don't know what yet maybe we should invent a
'bitmap loader.  BLOAD and BSAVE may also work !!! I'll look into
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
'I'm pretty satisfied that I learned how to use BLOAD and BSAVE
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


'TYPES
TYPE MAPFILEHEADER
   mapType AS INTEGER
   mapVersion AS INTEGER
   mapFileSize AS LONG
   mapReserved1 AS INTEGER
   mapReserved2 AS INTEGER
   mapWidth AS INTEGER
   mapHeight AS INTEGER
   mapDataSize AS LONG
   mapTileDataSize AS LONG
   mapPropertyDataSize AS LONG
   mapNumProperty AS INTEGER
END TYPE





'*** Other Image Dimensions ***
DIM SHARED autowall(50), facenorth(50), faceeast(50)
DIM SHARED autodoor(50), facesouth(50), facewest(50)

'*** Map Information ***
DIM SHARED tile%(225), tfront%(23)
DIM SHARED prop1%(225), prop2%(225)

'tile%() has info only on the tiles in the map
'tfront%() changes constantly depending on the location see
'   written notes for additional information

'*** Location Constants and Variables ***
DIM SHARED xloc AS INTEGER, yloc AS INTEGER, direction
DIM SHARED true, false
DIM SHARED N, E, S, W
DIM SHARED fileHeader AS MAPFILEHEADER

'Line should be remarked out for compile
' I        I            I              I
' V        V            V              V
CHDIR "c:\mydocu~1\programs\explor\redo\"

globalconsts 'The Variables that stay the same

SCREEN 13

'wallimages  'Loads the graphics into memory so they may be used
'wallimages is no longer used we found a more effective memory saving
'method to do the same thing

otherimages 'Same for this

'==========================================================
'===                                                    ===
'===    Initial variables:  Variables that determine    ===
'===     how you start in a map.  Will be decided by    ===
'===     explorSCRIPT in the playable releases.  Until  ===
'===     then they are written right here.              ===
'===  ExplorSCRIPT files will probably have .EXS        ===
'===  extenstion for (EX)plore(S)CRIPT                  ===
'===                                                    ===
'==========================================================

'readinitializers(MAPSCRIPT) 'Will be used to read the following
'information later:
xloc = 11
yloc = 1
direction = S

'gameloop
loadmap ("default.map")
interface
DO
  'tileaction '<----  Will read info about the current tile
                     'and preform and action accordingly
                     'such as display a text message or other
                     'special event
  clearviewport
  gettilesinfront
  render3d
  skyground
  showstats
  takeinput
  showproperty 'for debugging only
LOOP

SUB automap
'''''''''''''''''''''''''''''''''''''''''''''''
'''  Displays the automap                   '''
'''''''''''''''''''''''''''''''''''''''''''''''
DIM j AS INTEGER, k AS INTEGER
clearviewport
LINE (2, 2)-(149, 149), 7, BF
LINE (9, 9)-(143, 143), 0, BF
tilenum = 0
tsize = 9
FOR j = 0 TO 14
   FOR k = 0 TO 14
      SELECT CASE tile%(tilenum)
         CASE 10: PUT (k * tsize + tsize, j * tsize + tsize), autowall
         CASE 20: PUT (k * tsize + tsize, j * tsize + tsize), autodoor
      END SELECT
      tilenum = tilenum + 1
   NEXT
NEXT
SELECT CASE direction
   CASE N: PUT (xloc * tsize, yloc * tsize), facenorth
   CASE E: PUT (xloc * tsize, yloc * tsize), faceeast
   CASE S: PUT (xloc * tsize, yloc * tsize), facesouth
   CASE W: PUT (xloc * tsize, yloc * tsize), facewest
END SELECT
DO: LOOP UNTIL INKEY$ = CHR$(27)
END SUB

SUB clearviewport
''''''''''''''''''''''''''''''''''''''''''
''' Clears the displaywindow viewport  '''
''''''''''''''''''''''''''''''''''''''''''
LINE (1, 1)-(150, 150), 0, BF 'Clear View Window
END SUB

SUB gettilesinfront
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''   Gets info about the tiles in front of the player   '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'=== clear current tfront array ===
FOR cleart = 1 TO 22
   tfront%(cleart) = 1
NEXT
'=== The Array is thus Cleared ===

'================================================================
'===                                                          ===
'===         The North Calculations                           ===
'===                                                          ===
'================================================================

IF direction = N THEN
' Furthest Row
   IF yloc > 3 THEN
      IF xloc > 3 THEN
         'IF tile%(tbase(xloc, yloc)base(xloc, yloc) - 48) = 10 THEN tfront%(1) = 10
         tfront%(1) = tile%(tbase(xloc, yloc) - 48)
      ELSE tfront%(1) = 10
      END IF
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 47) = 10 THEN tfront%(2) = 10
         tfront%(2) = tile%(tbase(xloc, yloc) - 47)
      ELSE tfront%(2) = 10
      END IF
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 46) = 10 THEN tfront%(3) = 10
         tfront%(3) = (tbase(xloc, yloc) - 46)
      ELSE tfront%(3) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 45) = 10 THEN tfront%(4) = 10
         tfront%(4) = tile%(tbase(xloc, yloc) - 45)
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) - 44) = 10 THEN tfront%(5) = 10
         tfront%(5) = tile%(tbase(xloc, yloc) - 44)
      ELSE tfront%(5) = 10
      END IF
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) - 43) = 10 THEN tfront%(6) = 10
         tfront%(6) = tile%(tbase(xloc, yloc) - 43)
      ELSE tfront%(6) = 10
      END IF
      IF xloc < 13 THEN
        'IF tile%(tbase(xloc, yloc) - 42) = 10 THEN tfront%(7) = 10
        tfront%(7) = tile%(tbase(xloc, yloc) - 42)
      ELSE tfront%(7) = 10
      END IF
   ELSE
      tfront%(1) = 10
      tfront%(2) = 10
      tfront%(3) = 10
      tfront%(4) = 10
      tfront%(5) = 10
      tfront%(6) = 10
      tfront%(7) = 10
   END IF

' Second Furthest Row
   IF yloc > 2 THEN
      IF xloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) - 33) = 10 THEN tfront%(8) = 10
         tfront%(8) = tile%(tbase(xloc, yloc) - 33)
      tfront%(8) = 10
      END IF
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 32) = 10 THEN tfront%(9) = 10
         tfront%(9) = tile%(tbase(xloc, yloc) - 32)
      ELSE tfront%(9) = 10
      END IF
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 31) = 10 THEN tfront%(10) = 10
         tfront%(10) = tile%(tbase(xloc, yloc) - 31)
      ELSE tfront%(10) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 30) = 10 THEN tfront%(11) = 10
         tfront%(11) = tile%(tbase(xloc, yloc) - 30)
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) - 29) = 10 THEN tfront%(12) = 10
         tfront%(12) = tile%(tbase(xloc, yloc) - 29)
      ELSE tfront%(12) = 10
      END IF
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) - 28) = 10 THEN tfront%(13) = 10
         tfront%(13) = tile%(tbase(xloc, yloc) - 28)
      ELSE tfront%(13) = 10
      END IF
      IF xloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) - 27) = 10 THEN tfront%(14) = 10
         tfront%(14) = tile%(tbase(xloc, yloc) - 27)
      ELSE tfront%(14) = 10
      END IF
   ELSE
      tfront%(8) = 10
      tfront%(9) = 10
      tfront%(10) = 10
      tfront%(11) = 10
      tfront%(12) = 10
      tfront%(13) = 10
      tfront%(14) = 10
   END IF
' Row In Front
   IF yloc > 1 THEN
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 17) = 10 THEN tfront%(15) = 10
         tfront%(15) = tile%(tbase(xloc, yloc) - 17)
      ELSE tfront%(15) = 10
      END IF
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 16) = 10 THEN tfront%(16) = 10
         tfront%(16) = tile%(tbase(xloc, yloc) - 16)
      ELSE tfront%(16) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 15) = 10 THEN tfront%(17) = 10
         tfront%(17) = tile%(tbase(xloc, yloc) - 15)
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) - 14) = 10 THEN tfront%(18) = 10
         tfront%(18) = tile%(tbase(xloc, yloc) - 14)
      ELSE tfront%(18) = 10
      END IF
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) - 13) = 10 THEN tfront%(19) = 10
         tfront%(19) = tile%(tbase(xloc, yloc) - 13)
      ELSE tfront%(19) = 10
      END IF
   ELSE
      tfront%(15) = 10
      tfront%(16) = 10
      tfront%(17) = 10
      tfront%(18) = 10
      tfront%(19) = 10
   END IF
' Row On
   IF xloc > 1 THEN
      'IF tile%(tbase(xloc, yloc) - 1) = 10 THEN tfront%(20) = 10
      tfront%(20) = tile%(tbase(xloc, yloc) - 1)
   ELSE tfront%(20) = 10
   END IF
      'IF tile%(tbase(xloc, yloc)) = 10 THEN tfront%(21) = 10
      tfront%(21) = tile%(tbase(xloc, yloc))
   IF xloc < 15 THEN
      'IF tile%(tbase(xloc, yloc) + 1) = 10 THEN tfront%(22) = 10
      tfront%(22) = tile%(tbase(xloc, yloc) + 1)
   ELSE tfront%(22) = 10
   END IF
' Row Behind
   IF yloc < 15 THEN
        tfront%(23) = tile%(tbase(xloc, yloc) + 15)
   ELSE
        tfront%(23) = 10
   END IF
'================================================================
'===                                                          ===
'===         The South Calculations                           ===
'===                                                          ===
'================================================================

ELSEIF direction = S THEN
' Furthest Row
   IF yloc < 13 THEN
      IF xloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 48) = 10 THEN tfront%(1) = 10
         tfront%(1) = tile%(tbase(xloc, yloc) + 48)
      ELSE tfront%(1) = 10
      END IF
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 47) = 10 THEN tfront%(2) = 10
         tfront%(2) = tile%(tbase(xloc, yloc) + 47)
      ELSE tfront%(2) = 10
      END IF
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 46) = 10 THEN tfront%(3) = 10
         tfront%(3) = tile%(tbase(xloc, yloc) + 46)
      ELSE tfront%(3) = 10
      END IF
      'IF tile%(tbase(xloc, yloc) + 45) = 10 THEN tfront%(4) = 10
      tfront%(4) = tile%(tbase(xloc, yloc) + 45)
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) + 44) = 10 THEN tfront%(5) = 10
         tfront%(5) = tile%(tbase(xloc, yloc) + 44)
      ELSE tfront%(5) = 10
      END IF
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) + 43) = 10 THEN tfront%(6) = 10
         tfront%(6) = tile%(tbase(xloc, yloc) + 43)
      ELSE tfront%(6) = 10
      END IF
      IF xloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) + 42) = 10 THEN tfront%(7) = 10
         tfront%(7) = tile%(tbase(xloc, yloc) + 42)
      ELSE tfront%(7) = 10
      END IF
   ELSE
      tfront%(1) = 10
      tfront%(2) = 10
      tfront%(3) = 10
      tfront%(4) = 10
      tfront%(5) = 10
      tfront%(6) = 10
      tfront%(7) = 10
   END IF

' Second Furthest Row
   IF yloc < 14 THEN
      IF xloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 33) = 10 THEN tfront%(8) = 10
         tfront%(8) = tile%(tbase(xloc, yloc) + 33)
      ELSE tfront%(8) = 10
      END IF
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 32) = 10 THEN tfront%(9) = 10
         tfront%(9) = tile%(tbase(xloc, yloc) + 32)
      ELSE tfront%(9) = 10
      END IF
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 31) = 10 THEN tfront%(10) = 10
         tfront%(10) = tile%(tbase(xloc, yloc) + 31)
      ELSE tfront%(10) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) + 30) = 10 THEN tfront%(11) = 10
         tfront%(11) = tile%(tbase(xloc, yloc) + 30)
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) + 29) = 10 THEN tfront%(12) = 10
         tfront%(12) = tile%(tbase(xloc, yloc) + 29)
      ELSE tfront%(12) = 10
      END IF
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) + 28) = 10 THEN tfront%(13) = 10
         tfront%(13) = tile%(tbase(xloc, yloc) + 28)
      ELSE tfront%(13) = 10
      END IF
      IF xloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) + 27) = 10 THEN tfront%(14) = 10
         tfront%(14) = tile%(tbase(xloc, yloc) + 27)
      ELSE tfront%(14) = 10
      END IF
   ELSE
      tfront%(8) = 10
      tfront%(9) = 10
      tfront%(10) = 10
      tfront%(11) = 10
      tfront%(12) = 10
      tfront%(13) = 10
      tfront%(14) = 10
   END IF

'Row In front
   IF yloc < 15 THEN
      IF xloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 17) = 10 THEN tfront%(15) = 10
         tfront%(15) = tile%(tbase(xloc, yloc) + 17)
      ELSE tfront%(15) = 10
      END IF
      IF xloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 16) = 10 THEN tfront%(16) = 10
         tfront%(16) = tile%(tbase(xloc, yloc) + 16)
      ELSE tfront%(16) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) + 15) = 10 THEN tfront%(17) = 10
         tfront%(17) = tile%(tbase(xloc, yloc) + 15)
      IF xloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) + 14) = 10 THEN tfront%(18) = 10
         tfront%(18) = tile%(tbase(xloc, yloc) + 14)
      ELSE tfront%(18) = 10
      END IF
      IF xloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) + 13) = 10 THEN tfront%(19) = 10
         tfront%(19) = tile%(tbase(xloc, yloc) + 13)
      ELSE tfront%(19) = 10
      END IF
   ELSE
      tfront%(15) = 10
      tfront%(16) = 10
      tfront%(17) = 10
      tfront%(18) = 10
      tfront%(19) = 10

   END IF

' Row On
   IF xloc < 15 THEN
      'IF tile%(tbase(xloc, yloc) + 1) = 10 THEN tfront%(20) = 10
      tfront%(20) = tile%(tbase(xloc, yloc) + 1)
   ELSE tfront%(20) = 10
   END IF
      'IF tile%(tbase(xloc, yloc)) = 10 THEN tfront%(21) = 10
      tfront%(21) = tile%(tbase(xloc, yloc))
   IF xloc > 1 THEN
      'IF tile%(tbase(xloc, yloc) - 1) = 10 THEN tfront%(22) = 10
      tfront%(22) = tile%(tbase(xloc, yloc) - 1)
   ELSE tfront%(22) = 10
   END IF
' Row Behind
   IF yloc > 1 THEN
        tfront%(23) = tile%(tbase(xloc, yloc) - 15)
   ELSE
        tfront%(23) = 10
   END IF

'================================================================
'===                                                          ===
'===         The East Calculations                            ===
'===                                                          ===
'================================================================

ELSEIF direction = E THEN
' Furthest Row
   IF xloc < 13 THEN
      IF yloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) - 42) = 10 THEN tfront%(1) = 10
         tfront%(1) = tile%(tbase(xloc, yloc) - 42)
      ELSE tfront%(1) = 10
      END IF
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 27) = 10 THEN tfront%(2) = 10
         tfront%(2) = tile%(tbase(xloc, yloc) - 27)
      ELSE tfront%(2) = 10
      END IF
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 12) = 10 THEN tfront%(3) = 10
         tfront%(3) = tile%(tbase(xloc, yloc) - 12)
      ELSE tfront%(3) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) + 3) = 10 THEN tfront%(4) = 10
         tfront%(4) = tile%(tbase(xloc, yloc) + 3)
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 18) = 10 THEN tfront%(5) = 10
         tfront%(5) = tile%(tbase(xloc, yloc) + 18)
      ELSE tfront%(5) = 10
      END IF
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 33) = 10 THEN tfront%(6) = 10
         tfront%(6) = tile%(tbase(xloc, yloc) + 33)
      ELSE tfront%(6) = 10
      END IF
      IF yloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 48) = 10 THEN tfront%(7) = 10
         tfront%(7) = tile%(tbase(xloc, yloc) + 48)
      ELSE tfront%(7) = 10
      END IF
   ELSE
      tfront%(1) = 10
      tfront%(2) = 10
      tfront%(3) = 10
      tfront%(4) = 10
      tfront%(5) = 10
      tfront%(6) = 10
      tfront%(6) = 10
   END IF

' Second Furthest Row
   IF xloc < 14 THEN
      IF yloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) - 43) = 10 THEN tfront%(8) = 10
         tfront%(8) = tile%(tbase(xloc, yloc) - 43)
      ELSE tfront%(8) = 10
      END IF
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 28) = 10 THEN tfront%(9) = 10
         tfront%(9) = tile%(tbase(xloc, yloc) - 28)
      ELSE tfront%(9) = 10
      END IF
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 13) = 10 THEN tfront%(10) = 10
         tfront%(10) = tile%(tbase(xloc, yloc) - 13)
      ELSE tfront%(10) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) + 2) = 10 THEN tfront%(11) = 10
         tfront%(11) = tile%(tbase(xloc, yloc) + 2)
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 17) = 10 THEN tfront%(12) = 10
         tfront%(12) = tile%(tbase(xloc, yloc) + 17)
      ELSE tfront%(12) = 10
      END IF
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 32) = 10 THEN tfront%(13) = 10
         tfront%(13) = tile%(tbase(xloc, yloc) + 32)
      ELSE tfront%(13) = 10
      END IF
      IF yloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 47) = 10 THEN tfront%(14) = 10
        tfront%(14) = tile%(tbase(xloc, yloc) + 47)
      ELSE tfront%(14) = 10
      END IF
   ELSE
      tfront%(8) = 10
      tfront%(9) = 10
      tfront%(10) = 10
      tfront%(11) = 10
      tfront%(12) = 10
      tfront%(13) = 10
      tfront%(14) = 10
   END IF

' Row In Front
   IF xloc < 15 THEN
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 29) = 10 THEN tfront%(15) = 10
         tfront%(15) = tile%(tbase(xloc, yloc) - 29)
      ELSE tfront%(15) = 10
      END IF
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 14) = 10 THEN tfront%(16) = 10
         tfront%(16) = tile%(tbase(xloc, yloc) - 14)
      ELSE tfront%(16) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) + 1) = 10 THEN tfront%(17) = 10
         tfront%(17) = tile%(tbase(xloc, yloc) + 1)
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 16) = 10 THEN tfront%(18) = 10
         tfront%(18) = tile%(tbase(xloc, yloc) + 16)
      ELSE tfront%(18) = 10
      END IF
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 31) = 10 THEN tfront%(19) = 10
         tfront%(19) = tile%(tbase(xloc, yloc) + 31)
      ELSE tfront%(19) = 10
      END IF
   ELSE
      tfront%(15) = 10
      tfront%(16) = 10
      tfront%(17) = 10
      tfront%(18) = 10
      tfront%(19) = 10
   END IF

' Row on
   IF yloc > 1 THEN
      'IF tile%(tbase(xloc, yloc) - 15) = 10 THEN tfront%(20) = 10
      tfront%(20) = tile%(tbase(xloc, yloc) - 15)
   ELSE tfront%(20) = 10
   END IF
      'IF tile%(tbase(xloc, yloc)) = 10 THEN tfront%(21) = 10
      tfront%(21) = tile%(tbase(xloc, yloc))
   IF yloc < 15 THEN
      'IF tile%(tbase(xloc, yloc) + 15) = 10 THEN tfront%(22) = 10
      tfront%(22) = tile%(tbase(xloc, yloc) + 15)
   ELSE tfront%(22) = 10
   END IF
' Row Behind
   IF xloc > 1 THEN
        tfront%(23) = tile%(tbase(xloc, yloc) - 1)
   ELSE
        tfront%(23) = 10
   END IF
'================================================================
'===                                                          ===
'===         The West Calculations                            ===
'===                                                          ===
'================================================================


ELSEIF direction = W THEN
' Furthest Row Away
   IF xloc > 3 THEN
      IF yloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 42) = 10 THEN tfront%(1) = 10
         tfront%(1) = tile%(tbase(xloc, yloc) + 42)
      ELSE tfront%(1) = 10
      END IF
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 27) = 10 THEN tfront%(2) = 10
         tfront%(2) = tile%(tbase(xloc, yloc) + 27)
      ELSE tfront%(2) = 10
      END IF
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 12) = 10 THEN tfront%(3) = 10
         tfront%(3) = tile%(tbase(xloc, yloc) + 12)
      ELSE tfront%(3) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 3) = 10 THEN tfront%(4) = 10
         tfront%(4) = tile%(tbase(xloc, yloc) - 3)
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 18) = 10 THEN tfront%(5) = 10
         tfront%(5) = tile%(tbase(xloc, yloc) - 18)
      ELSE tfront%(5) = 10
      END IF
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 33) = 10 THEN tfront%(6) = 10
         tfront%(6) = tile%(tbase(xloc, yloc) - 33)
      ELSE tfront%(6) = 10
      END IF
      IF yloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) - 48) = 10 THEN tfront%(7) = 10
         tfront%(7) = tile%(tbase(xloc, yloc) - 48)
      ELSE tfront%(7) = 10
      END IF
   ELSE
      tfront%(1) = 10
      tfront%(2) = 10
      tfront%(3) = 10
      tfront%(4) = 10
      tfront%(5) = 10
      tfront%(6) = 10
      tfront%(7) = 10
   END IF

' Second Furthest Row Away
   IF xloc > 2 THEN
      IF yloc < 13 THEN
         'IF tile%(tbase(xloc, yloc) + 43) = 10 THEN tfront%(8) = 10
         tfront%(8) = tile%(tbase(xloc, yloc) + 43)
      ELSE tfront%(8) = 10
      END IF
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 28) = 10 THEN tfront%(9) = 10
         tfront%(9) = tile%(tbase(xloc, yloc) + 28)
      ELSE tfront%(9) = 10
      END IF
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 13) = 10 THEN tfront%(10) = 10
         tfront%(10) = tile%(tbase(xloc, yloc) + 13)
      ELSE tfront%(10) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 2) = 10 THEN tfront%(11) = 10
         tfront%(11) = tile%(tbase(xloc, yloc) - 2)
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 17) = 10 THEN tfront%(12) = 10
         tfront%(12) = tile%(tbase(xloc, yloc) - 17)
      ELSE tfront%(12) = 10
      END IF
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 32) = 10 THEN tfront%(13) = 10
         tfront%(13) = tile%(tbase(xloc, yloc) - 32)
      ELSE tfront%(13) = 10
      END IF
      IF yloc > 3 THEN
         'IF tile%(tbase(xloc, yloc) - 47) = 10 THEN tfront%(14) = 10
         tfront%(14) = tile%(tbase(xloc, yloc) - 47)
      ELSE tfront%(14) = 10
      END IF
   ELSE
      tfront%(8) = 10
      tfront%(9) = 10
      tfront%(10) = 10
      tfront%(11) = 10
      tfront%(12) = 10
      tfront%(13) = 10
      tfront%(14) = 10
   END IF

' Row In Front
   IF xloc > 1 THEN
      IF yloc < 14 THEN
         'IF tile%(tbase(xloc, yloc) + 29) = 10 THEN tfront%(15) = 10
         tfront%(15) = tile%(tbase(xloc, yloc) + 29)
      ELSE tfront%(15) = 10
      END IF
      IF yloc < 15 THEN
         'IF tile%(tbase(xloc, yloc) + 14) = 10 THEN tfront%(16) = 10
         tfront%(16) = tile%(tbase(xloc, yloc) + 14)
      ELSE tfront%(16) = 10
      END IF
         'IF tile%(tbase(xloc, yloc) - 1) = 10 THEN tfront%(17) = 10
         tfront%(17) = tile%(tbase(xloc, yloc) - 1)
      IF yloc > 1 THEN
         'IF tile%(tbase(xloc, yloc) - 16) = 10 THEN tfront%(18) = 10
         tfront%(18) = tile%(tbase(xloc, yloc) - 16)
      ELSE tfront%(18) = 10
      END IF
      IF yloc > 2 THEN
         'IF tile%(tbase(xloc, yloc) - 31) = 10 THEN tfront%(19) = 10
         tfront%(19) = tile%(tbase(xloc, yloc) - 31)
      ELSE tfront%(19) = 10
      END IF
   ELSE
      tfront%(15) = 10
      tfront%(16) = 10
      tfront%(17) = 10
      tfront%(18) = 10
      tfront%(19) = 10
   END IF

' Row On
   IF yloc < 15 THEN
      'IF tile%(tbase(xloc, yloc) + 15) = 10 THEN tfront%(20) = 10
      tfront%(20) = tile%(tbase(xloc, yloc) + 15)
   ELSE tfront%(20) = 10
   END IF
      'IF tile%(tbase(xloc, yloc)) = 10 THEN tfront%(21) = 10
      tfront%(21) = tile%(tbase(xloc, yloc))
   IF yloc > 1 THEN
      'IF tile%(tbase(xloc, yloc) - 15) = 10 THEN tfront%(22) = 10
      tfront%(22) = tile%(tbase(xloc, yloc) - 15)
   ELSE tfront%(22) = 10
   END IF
' Row Behind
   IF xloc < 15 THEN
        tfront%(23) = tile%(tbase(xloc, yloc) + 1)
   ELSE
        tfront%(23) = 10
   END IF

END IF
END SUB

SUB globalconsts
''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  Constants used globaly                      '''
'''   throughout entire program                  '''
''''''''''''''''''''''''''''''''''''''''''''''''''''
N = 1
S = 2
E = 3
W = 4

true = 1
false = 0
END SUB

SUB interface
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  This is the viewport we look upon                           '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
LINE (0, 0)-(319, 199), 15, B
LINE (0, 0)-(151, 151), 15, B
LINE (190, 5)-(290, 105), 15, B
LINE (3, 153)-(317, 197), 15, B
LINE (153, 107)-(317, 151), 15, B
COLOR 14
LOCATE 2, 25: PRINT "E.X.P.L.O.R."
LOCATE 4, 27: PRINT "A New"
LOCATE 5, 30: PRINT "World"
COLOR 7
LOCATE 7, 25: PRINT "Copyright(c)"
LOCATE 8, 26: PRINT "2001,"
LOCATE 10, 26: PRINT "Beem"
LOCATE 11, 27: PRINT "Software"
COLOR 15
pat$ = CHR$(&H40) + CHR$(&H70)
PAINT (155, 105), pat$, 15
END SUB

SUB loadmap (mapname$)
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  Procedure that loads a map described by mapname$ into     '''
'''                                                 RAM        '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
DIM binloc AS INTEGER, tilenum AS INTEGER
OPEN mapname$ FOR BINARY AS #2
GET #2, , fileHeader
IF fileHeader.mapVersion <> 3 THEN
        PRINT "Error 567: Not supported map type"
        END
END IF

FOR i = 0 TO fileHeader.mapTileDataSize / 2 - 1 STEP 1
   GET #2, , tile%(i)
NEXT
FOR i = 0 TO fileHeader.mapTileDataSize / 2 - 1 STEP 1
   GET #2, , prop1%(i)
NEXT
FOR i = 0 TO fileHeader.mapTileDataSize / 2 - 1 STEP 1
   GET #2, , prop2%(i)
NEXT
CLOSE #2
END SUB

SUB loadwall (wallchoice AS INTEGER)
DIM wall2(1 TO 950), wall3(1 TO 950), wall1(1 TO 2600)
DIM wall4(1 TO 950), wall5(1 TO 650), wall6(1 TO 650), wall7(1 TO 650)
DIM wall8(1 TO 160), wall9(1 TO 325), wall10(1 TO 160)
DIM wall11(1 TO 300), wall12(1 TO 150)

SELECT CASE wallchoice
   CASE 1:
      DEF SEG = VARSEG(wall12(1))
      BLOAD "images\" + "wall12.img", VARPTR(wall12(1))
      DEF SEG
      PUT (1, 62), wall12, PSET
   CASE 2:
      DEF SEG = VARSEG(wall11(1))
      BLOAD "images\" + "wall11.img", VARPTR(wall11(1))
      DEF SEG
      PUT (13, 62), wall11, PSET
   CASE 3:
      DEF SEG = VARSEG(wall11(1))
      BLOAD "images\" + "wall11.img", VARPTR(wall11(1))
      DEF SEG
      PUT (38, 62), wall11, PSET
   CASE 4:
      DEF SEG = VARSEG(wall11(1))
      BLOAD "images\" + "wall11.img", VARPTR(wall11(1))
      DEF SEG
      PUT (63, 62), wall11, PSET
   CASE 5:
      DEF SEG = VARSEG(wall11(1))
      BLOAD "images\" + "wall11.img", VARPTR(wall11(1))
      DEF SEG
      PUT (88, 62), wall11, PSET
   CASE 6:
      DEF SEG = VARSEG(wall11(1))
      BLOAD "images\" + "wall11.img", VARPTR(wall11(1))
      DEF SEG
      PUT (114, 62), wall11, PSET
      LINE (113, 62)-(113, 86)
   CASE 7:
      DEF SEG = VARSEG(wall12(1))
      BLOAD "images\" + "wall12.img", VARPTR(wall12(1))
      DEF SEG
      PUT (139, 62), wall12, PSET

   CASE 8:
   CASE 9:
   CASE 10:
      DEF SEG = VARSEG(wall8(1))
      BLOAD "images\" + "wall8.img", VARPTR(wall8(1))
      DEF SEG
      DEF SEG = VARSEG(wall7(1))
      BLOAD "images\" + "wall7.img", VARPTR(wall7(1))
      DEF SEG
      PUT (51, 50), wall8, PSET
      PUT (1, 50), wall7, PSET
   CASE 11:
      DEF SEG = VARSEG(wall7(1))
      BLOAD "images\" + "wall7.img", VARPTR(wall7(1))
      DEF SEG
      PUT (51, 50), wall7, PSET
   CASE 12:
      DEF SEG = VARSEG(wall10(1))
      BLOAD "images\" + "wall10.img", VARPTR(wall10(1))
      DEF SEG
      DEF SEG = VARSEG(wall7(1))
      BLOAD "images\" + "wall7.img", VARPTR(wall7(1))
      DEF SEG
      PUT (89, 50), wall10, PSET
      PUT (101, 50), wall7, PSET
   CASE 13:
   CASE 14:
   CASE 15:
   CASE 16:
      DEF SEG = VARSEG(wall4(1))
      BLOAD "images\" + "wall4.img", VARPTR(wall4(1))
      DEF SEG
      DEF SEG = VARSEG(wall5(1))
      BLOAD "images\" + "wall5.img", VARPTR(wall5(1))
      DEF SEG
      PUT (1, 25), wall4, PSET
      PUT (26, 25), wall5, PSET
   CASE 17:
      DEF SEG = VARSEG(wall1(1))
      BLOAD "images\" + "wall1.img", VARPTR(wall1(1))
      DEF SEG
      PUT (26, 25), wall1, PSET
   CASE 18:
      DEF SEG = VARSEG(wall4(1))
      BLOAD "images\" + "wall4.img", VARPTR(wall4(1))
      DEF SEG
      DEF SEG = VARSEG(wall6(1))
      BLOAD "images\" + "wall6.img", VARPTR(wall6(1))
      DEF SEG
      PUT (126, 25), wall4, PSET
      PUT (101, 25), wall6, PSET
   CASE 19:
   CASE 20:
      DEF SEG = VARSEG(wall2(1))
      BLOAD "images\" + "wall2.img", VARPTR(wall2(1))
      DEF SEG
      PUT (1, 1), wall2, PSET
   CASE 21:
      DEF SEG = VARSEG(wall2(1))
      BLOAD "images\" + "wall2.img", VARPTR(wall2(1))
      DEF SEG
      DEF SEG = VARSEG(wall1(1))
      BLOAD "images\" + "wall1.img", VARPTR(wall1(1))
      DEF SEG
      DEF SEG = VARSEG(wall3(1))
      BLOAD "images\" + "wall3.img", VARPTR(wall3(1))
      DEF SEG
      PUT (1, 1), wall2, PRESET
      PUT (26, 25), wall1, PRESET
      PUT (126, 1), wall3, PRESET
   CASE 22:
      DEF SEG = VARSEG(wall3(1))
      BLOAD "images\" + "wall3.img", VARPTR(wall3(1))
      DEF SEG
      PUT (126, 1), wall3, PSET
   CASE 23:
   CASE ELSE:
     PRINT "Error 203: Not proper tile selection"
END SELECT

END SUB

SUB movebackward
   IF direction = N THEN
        SELECT CASE tfront%(23)
           CASE 0: yloc = yloc + 1
           CASE 20: yloc = yloc + 2
        END SELECT
   ELSEIF direction = E THEN
        SELECT CASE tfront%(23)
           CASE 0: xloc = xloc - 1
           CASE 20: xloc = xloc - 2
        END SELECT
   ELSEIF direction = S THEN
        SELECT CASE tfront%(23)
           CASE 0: yloc = yloc - 1
           CASE 20: yloc = yloc - 2
        END SELECT
   ELSEIF direction = W THEN
        SELECT CASE tfront%(23)
          CASE 0: xloc = xloc + 1
          CASE 20: xloc = xloc + 2
        END SELECT
   END IF

END SUB

SUB moveforward
   IF direction = N THEN
      SELECT CASE tfront%(17)
         CASE 0: yloc = yloc - 1
         CASE 20: yloc = yloc - 2
      END SELECT
   ELSEIF direction = E THEN
      SELECT CASE tfront%(17)
         CASE 0: xloc = xloc + 1
         CASE 20: xloc = xloc + 2
      END SELECT
   ELSEIF direction = S THEN
      SELECT CASE tfront%(17)
         CASE 0: yloc = yloc + 1
         CASE 20: yloc = yloc + 2
      END SELECT
   ELSEIF direction = W THEN
      SELECT CASE tfront%(17)
         CASE 0: xloc = xloc - 1
         CASE 20: xloc = xloc - 2
      END SELECT
   END IF

END SUB

SUB otherimages
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  Loads images that are not wall tiles               '''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Automap Images
arcolor = 14
CLS
LINE (0, 0)-(8, 8), 7, BF
GET (0, 0)-(8, 8), autowall
CLS
LINE (0, 0)-(8, 8), 138, BF
GET (0, 0)-(8, 8), autodoor
CLS
LINE (3, 0)-(3, 6), arcolor
LINE (0, 2)-(3, 0), arcolor
LINE (6, 2)-(3, 0), arcolor
GET (0, 0)-(6, 6), facenorth
CLS
LINE (3, 0)-(3, 6), arcolor
LINE (0, 4)-(3, 6), arcolor
LINE (6, 4)-(3, 6), arcolor
GET (0, 0)-(6, 6), facesouth
CLS
LINE (0, 3)-(6, 3), arcolor
LINE (4, 0)-(6, 3), arcolor
LINE (4, 6)-(6, 3), arcolor
GET (0, 0)-(6, 6), faceeast
CLS
LINE (0, 3)-(6, 3), arcolor
LINE (2, 0)-(0, 3), arcolor
LINE (2, 6)-(0, 3), arcolor
GET (0, 0)-(6, 6), facewest
CLS
END SUB

SUB render3d
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''' Loads all images to be displayed in the 3D view    '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Currently only checks if a wall is there.  In the future will check
'any type of tile.  Particularly doors, trees, mountains, etc.  The
'possibilities are endless. Except may be limited by the amount of memory
'images can store.

' Furthest Row Back

SELECT CASE tfront%(1)
   CASE 10: loadwall (1)
   'CASE 20: PUT (1, 62), wall12, PRESET
END SELECT

SELECT CASE tfront%(2)
   CASE 10: loadwall (2)
   'CASE 20: PUT (13, 62), wall11, PRESET
END SELECT

SELECT CASE tfront%(3)
   CASE 10: loadwall (3)
   'CASE 20: PUT (38, 62), wall11, PRESET
END SELECT

SELECT CASE tfront%(4)
  CASE 10: loadwall (4)
  'CASE 20: PUT (63, 62), wall11, PRESET
END SELECT

SELECT CASE tfront%(5)
   CASE 10:
      loadwall (5)
      LINE (113, 62)-(113, 86)
   'CASE 20:
      'PUT (88, 62), wall11, PRESET
      'LINE (113, 62)-(113, 86)
END SELECT

SELECT CASE tfront%(6)
   CASE 10: loadwall (6)
   'CASE 20: PUT (114, 62), wall11, PRESET
END SELECT

SELECT CASE tfront%(7)
   CASE 10: loadwall (7)
   'CASE 20: PUT (138, 62), wall12, PRESET
END SELECT

'Second Row Back
SELECT CASE tfront%(10)
   CASE 10: loadwall (10)
   'CASE 20:
     'PUT (51, 50), wall8, PRESET
     'PUT (1, 50), wall7, PRESET
END SELECT

SELECT CASE tfront%(12)
   CASE 10: loadwall (12)
   'CASE 20:
      'PUT (89, 50), wall10, PRESET
      'PUT (101, 50), wall7, PRESET
END SELECT

SELECT CASE tfront%(11)
   CASE 10: loadwall (11)
   'CASE 20: PUT (51, 50), wall7, PRESET
END SELECT

'Row In Front
SELECT CASE tfront%(16)
   CASE 10: loadwall (16)
   'CASE 20:
      'PUT (1, 25), wall4, PRESET
      'PUT (26, 25), wall5, PRESET
END SELECT

SELECT CASE tfront%(18)
   CASE 10: loadwall (18)
   'CASE 20:
      'PUT (126, 25), wall4, PRESET
      'PUT (101, 25), wall6, PRESET
END SELECT

SELECT CASE tfront%(17)
   CASE 10: loadwall (17)
   'CASE 20: PUT (26, 25), wall1, PRESET
END SELECT

'Row On
SELECT CASE tfront%(20)
   CASE 10: loadwall (20)
   'CASE 20: PUT (1, 1), wall2, PRESET
END SELECT

SELECT CASE tfront%(22)
  CASE 10: loadwall (22)
  'CASE 20: PUT (126, 1), wall3, PRESET
END SELECT

SELECT CASE tfront%(21)            'Inside of a wall tile
   CASE 10: loadwall (21)
END SELECT
END SUB

SUB showproperty
LOCATE 21, 2: PRINT "Property 1:"; prop1%(tbase(xloc, yloc))
LOCATE 22, 2: PRINT "Property 2:"; prop2%(tbase(xloc, yloc))
END SUB

SUB showstats
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  Shows current statistics                           '''
'''   probably will display current weapon amount of    '''
'''   money.  Or thos may be displayed on a different   '''
'''   menu.                                             '''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
LOCATE 17, 25: PRINT "x:"; xloc
LOCATE 17, 31: PRINT "y:"; yloc
LOCATE 15, 21: PRINT "Direction:"
LOCATE 15, 32

SELECT CASE direction
   CASE N: PRINT "North"
   CASE E: PRINT "East "
   CASE W: PRINT "West "
   CASE S: PRINT "South"
END SELECT
END SUB

SUB skyground
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''  Paints the sky and ground decided colors        '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Good Colors for day sky: 1, 11, 52, 53
skycolor = 53
'Good Colors for ground: 6, 186, 138,
groundcolor = 186


'FOR paintx = 1 TO 150
'  FOR painty = 1 TO 75
'    IF POINT(paintx, painty) THEN
'    ELSE
'       PSET (paintx, painty), skycolor
'    END IF
'  NEXT
'NEXT
'FOR paintx = 1 TO 150
'   FOR painty = 76 TO 150
'      IF POINT(paintx, painty) THEN
'      ELSE
'        PSET (paintx, painty), groundcolor
'      END IF
'   NEXT
'NEXT
FOR sky = 1 TO 150
       IF POINT(sky, 75) THEN
       ELSE
        PSET (sky, 75), skycolor
        PSET (sky, 76), groundcolor
       END IF
NEXT
IF tfront%(21) = 10 THEN
ELSE
        PAINT (75, 2), skycolor, 15
        PAINT (75, 149), groundcolor, 15
END IF
END SUB

SUB takeinput
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''' Waits to recieve input from the keyboard then acts         '''
''' accordingly.                                               '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
DO
m$ = INKEY$
LOOP UNTIL m$ = CHR$(0) + "M" OR m$ = CHR$(0) + "K" OR m$ = CHR$(27) OR m$ = CHR$(0) + "H" OR m$ = CHR$(0) + "P" OR m$ = "M" OR m$ = "m"
LET oldx = xloc: LET oldy = yloc
t = xloc + 15 * (yloc - 1)
SELECT CASE m$
CASE CHR$(0) + "M":  'Right
   IF direction = N THEN
      LET direction = E
   ELSEIF direction = E THEN
      LET direction = S
   ELSEIF direction = S THEN
      LET direction = W
   ELSEIF direction = W THEN
      LET direction = N
   END IF
CASE CHR$(0) + "K":  'Left
   IF direction = N THEN
      LET direction = W
   ELSEIF direction = E THEN
      LET direction = N
   ELSEIF direction = W THEN
      LET direction = S
   ELSEIF direction = S THEN
      LET direction = E
   END IF
CASE CHR$(0) + "H":  'forward
   moveforward
CASE CHR$(0) + "P":  'backward
   movebackward
CASE CHR$(27):
       END
CASE "M", "m":
        automap
CASE ELSE:
        '
END SELECT
END SUB

FUNCTION tbase% (tx AS INTEGER, ty AS INTEGER)
't = xloc + 15 * (yloc - 1)
tbase = fileHeader.mapWidth * (ty - 1) + tx - 1
'tbase = tx + 15 * (ty - 1)
END FUNCTION

