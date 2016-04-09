DECLARE SUB place (choice!)
DECLARE SUB loadgif (AA$)
DECLARE SUB imageload ()

'ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
'บ                                                                 บ
'บ                  E.X.P.L.O.R (tm)                               บ
'บ                                                                 บ
'บ                         A New World                             บ   
'บ                                                                 บ
'บ                                      v. BETA 0.02               บ
'บ                                                                 บ
'บ           B.M. Software Copywrite(C) 2000                       บ
'บ                                                                 บ
'ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
'Here it is the BETA release of EXPLOR it's not much but a good
'start.  You probably won't want to play it for much more than a
'couple of minutes, probably less actually, but it's worth your
'time.

'The game is completely based off Might and Magic (though there are other
'games like it).  I had Might and Magic for nintendo but it just wouldn't
'save right so I decided to make my own game.  It's rendured 3D just like
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
DECLARE SUB calcw ()
DECLARE SUB calce ()
DECLARE SUB calcn ()
DECLARE SUB calcs ()
DECLARE SUB calcsouth ()
DECLARE SUB calcnorth ()
DECLARE SUB software ()
DECLARE SUB title ()
DECLARE SUB graphicsload ()
DECLARE SUB game ()
DECLARE SUB view1 ()
DECLARE SUB writecord ()
DECLARE SUB turnright ()
DECLARE SUB turnleft ()
DECLARE SUB story ()
DECLARE SUB render3d ()
DECLARE SUB placechar ()
DECLARE SUB calcbackward ()
DECLARE SUB calcforward ()
DECLARE SUB moveinput ()
DECLARE SUB credits ()
DECLARE SUB gameover ()
DECLARE SUB instructions ()
DECLARE SUB mainmenu ()
DECLARE SUB loadmap ()
DECLARE SUB calcmap ()
DECLARE SUB dataset ()

DIM SHARED direction, n, s, e, w, charac$, m$, x, y, oldx, oldy, maxx, maxy
DIM SHARED board$(1000), wall(190), blank(190), black(100), minx, miny
DIM SHARED faces(100), facen(100), facee(100), facew(100), graphic(100), con
DIM SHARED xcord, ycord, true, false
DIM SHARED dd1, dd2, dd3, dd4, dd5, dd6, dd7, dd8, dd9, dd10, dd11
DIM SHARED dd12, dd13, dd14, dd15, dd16, ddnull
DIM SHARED a$, AA$

DIM SHARED dir$
DIM SHARED wall1(5000), wall2(3000), wall3(2500), wall4(2500)
DIM SHARED wall5(3000), wall6(2500), null(2000)

DIM SHARED wall7(5000), wall8(3000), wall9(2500), wall10(2500)
DIM SHARED wall11(3000), wall12(2500), wall13(2000)

DIM SHARED wall14(5000), wall15(6000)
dir$ = "c:\mydocu~1\programs\explor\coolgr~1\"
imageload

graphicsload
dataset
software
title
mainmenu

SUB calcbackward
        IF direction = n THEN
                PUT (x * con, y * con), facen
                LET y = y + 1
                IF y >= maxy THEN LET y = y - 1
                IF POINT(x * con, y * con) THEN LET y = y - 1
        ELSEIF direction = s THEN
                PUT (x * con, y * con), faces
                LET y = y - 1
                IF y <= miny THEN LET y = y + 1
                IF POINT(x * con, y * con) THEN LET y = y + 1
        ELSEIF direction = e THEN
                PUT (x * con, y * con), facee
                LET x = x - 1
                IF x <= minx THEN LET x = x + 1
                IF POINT(x * con, y * con) THEN LET x = x + 1
        ELSEIF direction = w THEN
                PUT (x * con, y * con), facew
                LET x = x + 1
                IF x >= maxx THEN LET x = x - 1
                IF POINT(x * con, y * con) THEN LET x = x - 1
        END IF

END SUB

SUB calce
IF POINT((x + 3) * con, (y - 2) * con) THEN LET dda = true
IF POINT((x + 3) * con, (y - 1) * con) THEN LET ddb = true
IF POINT((x + 3) * con, y * con) THEN LET ddc = true
IF POINT((x + 3) * con, (y + 1) * con) THEN LET ddd = true
IF POINT((x + 3) * con, (y + 2) * con) THEN LET dde = true

IF POINT((x + 2) * con, (y - 2) * con) THEN LET ddf = true
IF POINT((x + 2) * con, (y - 1) * con) THEN LET ddg = true
IF POINT((x + 2) * con, y * con) THEN LET ddh = true
IF POINT((x + 2) * con, (y + 1) * con) THEN LET ddi = true
IF POINT((x + 2) * con, (y + 2) * con) THEN LET ddj = true

IF POINT((x + 1) * con, (y - 2) * con) THEN LET ddk = true
IF POINT((x + 1) * con, (y - 1) * con) THEN LET ddl = true
IF POINT((x + 1) * con, y * con) THEN LET ddm = true
IF POINT((x + 1) * con, (y + 1) * con) THEN LET ddn = true
IF POINT((x + 1) * con, (y + 2) * con) THEN LET ddo = true

IF POINT(x * con, (y - 1) * con) THEN LET ddp = true
IF POINT(x * con, (y + 1) * con) THEN LET ddq = true
END SUB

SUB calcforward
        IF direction = n THEN
                PUT (x * con, y * con), facen
                LET y = y - 1
                IF y <= miny THEN LET y = y + 1
                IF POINT(x * con, y * con) THEN LET y = y + 1
        ELSEIF direction = s THEN
                PUT (x * con, y * con), faces
                LET y = y + 1
                IF y >= maxy THEN LET y = y - 1
                IF POINT(x * con, y * con) THEN LET y = y - 1
        ELSEIF direction = e THEN
                PUT (x * con, y * con), facee
                LET x = x + 1
                IF x >= maxx THEN LET x = x - 1
                IF POINT(x * con, y * con) THEN LET x = x - 1
        ELSEIF direction = w THEN
                PUT (x * con, y * con), facew
                LET x = x - 1
                IF x <= minx THEN LET x = x + 1
                IF POINT(x * con, y * con) THEN LET x = x + 1
        END IF


END SUB

SUB calcmap
'What this sub will do is caculate where walls and stuff need to be
'put on the 3d image.  Then the data will be used in render3d to place
'the images on the view screen.

LET dd1 = false: LET dd2 = false: LET dd3 = false: LET dd4 = false
LET dd5 = false: LET dd6 = false: LET dd7 = false: LET dd8 = false
LET dd9 = false: LET dd10 = false: LET dd11 = false: LET dd12 = false
LET dd13 = false: LET dd14 = false: LET dd15 = false: LET dd16 = false
LET ddnul = false

IF direction = n THEN
        calcn
ELSEIF direction = s THEN
        calcs
ELSEIF direction = w THEN
        calcw
ELSEIF direction = e THEN
        calce
END IF

END SUB

SUB calcn

IF POINT((x - 1) * con, (y - 3) * con) THEN LET dd10 = true
IF POINT(x * con, (y - 3) * con) THEN LET dd11 = true
IF POINT((x + 1) * con, (y - 3) * con) THEN LET dd12 = true



IF POINT((x - 1) * con, (y - 2) * con) THEN LET dd7 = true
IF POINT(x * con, (y - 2) * con) THEN LET dd8 = true
IF POINT((x + 1) * con, (y - 2) * con) THEN LET dd9 = true



IF POINT((x - 1) * con, (y - 1) * con) THEN LET dd1 = true
IF POINT((x * con), (y - 1) * con) THEN LET dd2 = true
IF POINT((x + 1) * con, (y - 1) * con) THEN LET dd3 = true

IF POINT(x * con, y * con) THEN LET dd2 = true
IF POINT((x - 1) * con, y * con) THEN LET dd1 = true
IF POINT((x + 1) * con, y * con) THEN LET dd3 = true

END SUB

SUB calcs
IF POINT((x + 2) * con, (y + 3) * con) THEN LET dda = true
IF POINT((x + 1) * con, (y + 3) * con) THEN LET ddb = true
IF POINT(x * con, (y + 3) * con) THEN LET ddc = true
IF POINT((x - 1) * con, (y + 3) * con) THEN LET ddd = true
IF POINT((x - 2) * con, (y + 3) * con) THEN LET dde = true

IF POINT((x + 2) * con, (y + 2) * con) THEN LET ddf = true
IF POINT((x + 1) * con, (y + 2) * con) THEN LET ddg = true
IF POINT(x * con, (y + 2) * con) THEN LET ddh = true
IF POINT((x - 1) * con, (y + 2) * con) THEN LET ddi = true
IF POINT((x - 2) * con, (y + 2) * con) THEN LET ddj = true

IF POINT((x + 2) * con, (y + 1) * con) THEN LET ddk = true
IF POINT((x + 1) * con, (y + 1) * con) THEN LET ddl = true
IF POINT(x * con, (y + 1) * con) THEN LET ddm = true
IF POINT((x - 1) * con, (y + 1) * con) THEN LET ddn = true
IF POINT((x - 2) * con, (y + 1) * con) THEN LET ddo = true

IF POINT((x + 1) * con, y * con) THEN LET ddp = true
IF POINT((x - 1) * con, y * con) THEN LET ddq = true
END SUB

SUB calcw
IF POINT((x - 3) * con, (y + 2) * con) THEN LET dda = true
IF POINT((x - 3) * con, (y + 1) * con) THEN LET ddb = true
IF POINT((x - 3) * con, y * con) THEN LET ddc = true
IF POINT((x - 3) * con, (y - 1) * con) THEN LET ddd = true
IF POINT((x - 3) * con, (y - 2) * con) THEN LET dde = true

IF POINT((x - 2) * con, (y + 2) * con) THEN LET ddf = true
IF POINT((x - 2) * con, (y + 1) * con) THEN LET ddg = true
IF POINT((x - 2) * con, y * con) THEN LET ddh = true
IF POINT((x - 2) * con, (y - 1) * con) THEN LET ddi = true
IF POINT((x - 2) * con, (y - 2) * con) THEN LET ddj = true

IF POINT((x - 1) * con, (y + 2) * con) THEN LET ddk = true
IF POINT((x - 1) * con, (y + 1) * con) THEN LET ddl = true
IF POINT((x - 1) * con, y * con) THEN LET ddm = true
IF POINT((x - 1) * con, (y - 1) * con) THEN LET ddn = true
IF POINT((x - 1) * con, (y - 2) * con) THEN LET ddo = true

IF POINT(x * con, (y + 1) * con) THEN LET ddp = true
IF POINT(x * con, (y - 1) * con) THEN LET ddq = true

END SUB

SUB credits
CLS
COLOR 89: PRINT "PROGRAMMING"
COLOR 89: PRINT : PRINT "Lead Programmer"
COLOR 15: PRINT "Blaine Myers"
COLOR 89: PRINT "Assistant Programmers"
COLOR 15: PRINT "Hirobi Shicoby"
PRINT "Atasha Yensuki"
PRINT "Joe Gillis (Joface)"
PRINT "Hakeem Alajuan"
PRINT "The Grey Cat"
PRINT "U.C.L.A. Team Red"
COLOR 89: PRINT "Backup Team"
COLOR 15: PRINT "Bond, James Bond"
PRINT "Alec Guiness"
PRINT "John Cassidy Parker"
PRINT "and The Blue Baby"
COLOR 89: PRINT : PRINT "ARTWORK"
PRINT : PRINT "Lead Artist"
COLOR 15: PRINT "Blaine Myers"
COLOR 89: PRINT "3D Art Director"
COLOR 15: PRINT "Blaine Myers"
SLEEP 10
CLS
COLOR 89: PRINT "ACTORS"
COLOR 15: PRINT "Jean Luc Picard.....Star of the Game"
PRINT "James Bond..........The Planet"
PRINT "Luke Skywalker......The Holy One"
PRINT "Bill Clinton........Leader of the Pack"
PRINT "Queen Elizabeth.....Enslaved Woman"
PRINT "Tom Cruise..........Friendly Spy"
PRINT "Power Rangers.......Super Friends"
PRINT "The Beatles.........Concert Stars"
PRINT "Blaine Myers........The One"
PRINT "Leonardo DiCaprio...The Corps Lev. 2"
PRINT "John................Unknown"
COLOR 89: PRINT : PRINT "STUNT MEN"
COLOR 15: PRINT "Brandon (Shorty) Bellows"
PRINT "David Ninja"
PRINT "Crazy Lou"
PRINT "B the Bomb"
SLEEP 10
CLS
COLOR 89: PRINT : PRINT "SPECIAL THANKS TO"
COLOR 15: PRINT "Hacksoft"
PRINT "LaPeste"
PRINT "Star Trek"
PRINT "Star Fox"
PRINT "Star Wars"
PRINT "StarGate"
PRINT "Star 102.7"
PRINT "and Any other Stars"
PRINT "T.T.G. Tattle Tail Gargoyle"
PRINT "Travis the Green"
PRINT "(Blade) Michael Sharp"
PRINT "Jon Van Caneghem"
COLOR 89: PRINT : PRINT "NOT SO SPECIAL THANKS TO"
COLOR 15: PRINT "Adam Kay"
COLOR 89: PRINT : PRINT "SUPER SPECIAL THANKS TO"
COLOR 15: PRINT "Craig Decker"
PRINT "For Getting Me Started"
SLEEP 10
CLS
mainmenu

END SUB

SUB dataset
LET n = 1
LET e = 2
LET s = 3
LET w = 4
LET direction = w
LET maxy = 21
LET maxx = 21
LET minx = 0
LET miny = 0
LET con = 4.52
END SUB

SUB game
WINDOW SCREEN (0, 0)-(160, 100)
loadmap
dataset
LET x = 5
LET y = 6
true = 1
false = NOT true
PUT (x * con, y * con), facen
view1
DO
loadmap
placechar
calcmap
CLS
render3d
writecord
moveinput
LOOP

END SUB

SUB gameover
CLS
COLOR 255
LOCATE 10, 15: PRINT "GAME OVER"
COLOR 0
SYSTEM


END SUB

SUB graphicsload
LINE (1, 1)-(5 * 1.8, 5 * 1.8), 254, BF
GET (1, 1)-(5 * 1.8, 5 * 1.8), wall
LINE (1, 1)-(5 * 1.8, 5 * 1.8), 0, BF
GET (1, 1)-(5 * 1.8, 5 * 1.8), blank


COLOR 15
CLS

LINE (40.5, 42.5)-(44, 42.5), 253
LINE (40.5, 42.5)-(42, 41), 253
LINE (40.5, 42.5)-(42, 44), 253
GET (40, 40)-(44.52, 44.52), facew
CLS


LINE (40.5, 42.5)-(44, 42.5), 253
LINE (44, 42.5)-(42.5, 41), 253
LINE (44, 42.5)-(42.5, 44), 253
GET (40, 40)-(44.52, 44.52), facee
CLS


LINE (42.5, 40.5)-(42.5, 44), 253
LINE (42.5, 40.5)-(44, 42), 253
LINE (42.5, 40.5)-(40.5, 42), 253
GET (40, 40)-(44.52, 44.52), facen

CLS

LINE (42.5, 40.5)-(42.5, 44), 253
LINE (42.5, 44)-(44, 42), 253
LINE (42.5, 44)-(40.5, 42), 253
GET (40, 40)-(44.52, 44.52), faces
CLS
END SUB

SUB imageload
'Will load pallete's
'Pallet 1
loadgif ("image1")
GET (1, 1)-(47, 180), wall1
GET (47, 1)-(69, 180), wall2
GET (69, 1)-(81, 180), wall3
GET (81, 1)-(101, 180), null
GET (101, 1)-(112, 180), wall4
GET (112, 1)-(135, 180), wall5
GET (135, 1)-(181, 180), wall6
CLS
CLOSE #1
'Pallete 2
loadgif ("image2")
GET (1, 1)-(47, 180), wall7
GET (47, 1)-(69, 180), wall8
GET (69, 1)-(81, 180), wall9
GET (101, 1)-(112, 180), wall10
GET (112, 1)-(135, 180), wall11
GET (135, 1)-(181, 180), wall12
GET (81, 1)-(101, 180), wall13
CLS
CLOSE #1

'Pallete 3
loadgif ("image3")
GET (69, 1)-(114, 180), wall14
CLOSE #1
CLS

'Pallete 4
loadgif ("image4")
GET (47, 1)-(139, 180), wall15
CLOSE #1
CLS

'Pallete 5
'loadgif ("image5")
'GET (1, 1)-(180, 180), wall16
'CLS
'CLOSE #1

END SUB

SUB instructions
 CLS
SCREEN 13

WINDOW (1, 1)-(100, 100)
DIM uparrow(100), downarrow(100), leftarrow(100), rightarrow(100)
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (52.5, 50.5)-(52.5, 54.2), 0
LINE (52.5, 54.2)-(54.5, 52), 0
LINE (52.5, 54.2)-(50.5, 52), 0
GET (50, 50)-(55, 55), uparrow
 CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (52.5, 50.5)-(52.5, 54.2), 0
LINE (52.5, 50.5)-(50.5, 53), 0
LINE (52.5, 50.5)-(54.5, 53), 0
GET (50, 50)-(55, 55), downarrow
 CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (50.5, 52.5)-(54.5, 52.5), 0
LINE (54.5, 52.5)-(52, 50.5), 0
LINE (54.5, 52.5)-(52, 54.5), 0
GET (50, 50)-(55, 55), rightarrow
CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (50.5, 52.5)-(54.5, 52.5), 0
LINE (50.5, 52.5)-(53, 54.5), 0
LINE (50.5, 52.5)-(53, 50.5), 0
GET (50, 50)-(55, 55), leftarrow
CLS
COLOR 2: LOCATE 1, 14: PRINT "INSTRUCTIONS"
COLOR 5: LOCATE 3, 1: PRINT "To control your character use the UP"
PRINT "and DOWN arrows to move forward and"
PRINT "backward to turn left or right us the"
PRINT "LEFT and RIGHT arrows."
PUT (5, 60), uparrow
PUT (5, 52), downarrow
PUT (5, 44), rightarrow
PUT (5, 36), leftarrow
COLOR 11: LOCATE 10, 6: PRINT "MOVE FORWARD"
LOCATE 12, 6: PRINT "MOVE BACKWARD"
LOCATE 14, 6: PRINT "TURN RIGHT"
LOCATE 16, 6: PRINT "TURN LEFT"
LOCATE 18, 1
COLOR 15: PRINT "As you explor the 3D world you will find"
PRINT "many mysterious and wondrous things."
PRINT : PRINT "            (press space)"
DO: LOOP UNTIL INKEY$ = " "
mainmenu

END SUB

SUB loadgif (AA$)
'
'DEGIF6.BAS - No frills GIF decoder for the VGA's 320x200x256 mode.
'By Rich Geldreich 1993 (Public domain, use as you wish.)
'This version should properly decode all LZW encoded images in
'GIF image files. I've finally added GIF89a and local colormap
'support, so it more closely follows the GIF specification. It
'still doesn't support the entire GIF89a specification, but it'll
'show most GIF files fine.
'The GIF decoding speed of this program isn't great, but I'd say
'for an all QB/PDS decoder it's not bad!
'Note: This program does not stop decoding the GIF image after the
'rest of the scanlines become invisible! This happens with images
'larger than the 320x200 screen. So if the program seems to be
'just sitting there, accessing your hard disk, don't worry...
'It'll beep when it's done.

DEFINT A-Z
'Prefix() and Suffix() hold the LZW phrase dictionary.
'OutStack() is used as a decoding stack.
'ShiftOut() as a power of two table used to quickly retrieve the LZW
'multibit codes.
DIM Prefix(4095), Suffix(4095), OutStack(4095), ShiftOut(8)

'The following line is for the QB environment(slow).
DIM YBase AS LONG, Powersof2(11) AS LONG, WorkCode AS LONG
'For a little more speed, unremark the next line and remark the one
'above, before you compile... You'll get an overflow error if the
'following line is used in the QB environment, so change it back.
'DIM YBase AS INTEGER, Powersof2(11) AS INTEGER, WorkCode AS INTEGER

'Precalculate power of two tables for fast shifts.
FOR a = 0 TO 8: ShiftOut(8 - a) = 2 ^ a: NEXT
FOR a = 0 TO 11: Powersof2(a) = 2 ^ a: NEXT

'Get GIF filename.
a$ = COMMAND$: LET a$ = dir$ + AA$: IF a$ = "" THEN END
'Add GIF extension if the given filename doesn't have one.
FOR a = LEN(a$) TO 1 STEP -1
    SELECT CASE MID$(a$, a, 1)
    CASE "\", ":": EXIT FOR
    CASE ".": Extension = -1: EXIT FOR
    END SELECT
NEXT
IF Extension = 0 THEN a$ = a$ + ".GIF"

'Open file for input so QB stops with an error if it doesn't exist.
OPEN a$ FOR INPUT AS #1: CLOSE #1
OPEN a$ FOR BINARY AS #1

'Check to see if GIF file. Ignore GIF version number.
a$ = "      ": GET #1, , a$
IF LEFT$(a$, 3) <> "GIF" THEN PRINT "Not a GIF file.": END

'Get logical screen's X and Y resolution.
GET #1, , TotalX: GET #1, , TotalY: GOSUB GetByte
'Calculate number of colors and find out if a global palette exists.
NumColors = 2 ^ ((a AND 7) + 1): NoPalette = (a AND 128) = 0
'Retrieve background color.
GOSUB GetByte: Background = a

'Get aspect ratio and ignore it.
GOSUB GetByte

'Retrieve global palette if it exists.
IF NoPalette = 0 THEN P$ = SPACE$(NumColors * 3): GET #1, , P$

DO 'Image decode loop

'Skip by any GIF extensions.
'(With a few modifications this code could also fetch comments.)
DO
    'Skip by any zeros at end of image (why must I do this? the
    'GIF spec never mentioned it)
    DO
        IF EOF(1) THEN GOTO AllDone 'if at end of file, exit
        GOSUB GetByte
    LOOP WHILE a = 0           'loop while byte fetched is zero

    SELECT CASE a
    CASE 44  'We've found an image descriptor!
        EXIT DO
    CASE 59  'GIF trailer, stop decoding.
        GOTO AllDone
    CASE IS <> 33
        PRINT "Unknown GIF extension type.": END
    END SELECT
    'Skip by blocked extension data.
    GOSUB GetByte
    DO: GOSUB GetByte: a$ = SPACE$(a): GET #1, , a$: LOOP UNTIL a = 0
LOOP
'Get image's start coordinates and size.
GET #1, , XStart: GET #1, , YStart: GET #1, , XLength: GET #1, , YLength
XEnd = XStart + XLength: YEnd = YStart + YLength

'Check for local colormap, and fetch it if it exists.
GOSUB GetByte
IF (a AND 128) THEN
    NoPalette = 0
    NumColors = 2 ^ ((a AND 7) + 1)
    P$ = SPACE$(NumColors * 3): GET #1, , P$
END IF

'Check for interlaced image.
Interlaced = (a AND 64) > 0: PassNumber = 0: PassStep = 8

'Get LZW starting code size.
GOSUB GetByte

'Calculate clear code, end of stream code, and first free LZW code.
ClearCode = 2 ^ a
EOSCode = ClearCode + 1
FirstCode = ClearCode + 2: NextCode = FirstCode
StartCodeSize = a + 1: CodeSize = StartCodeSize

'Find maximum code for the current code size.
StartMaxCode = 2 ^ (a + 1) - 1: MaxCode = StartMaxCode

BitsIn = 0: BlockSize = 0: BlockPointer = 1

x = XStart: y = YStart: YBase = y * 320&

'Set screen 13 in not set yet.
IF FirstTime = 0 THEN
    'Go to VGA mode 13 (320x200x256).
    SCREEN 13: DEF SEG = &HA000
END IF

'Set palette, if there was one.
IF NoPalette = 0 THEN
    'Use OUTs for speed.
    OUT &H3C8, 0
    FOR a = 1 TO NumColors * 3: OUT &H3C9, ASC(MID$(P$, a, 1)) \ 4: NEXT
    'Save palette of image to disk.
    'OPEN "pal." FOR BINARY AS #2: PUT #2, , P$: CLOSE #2
END IF

IF FirstTime = 0 THEN
  'Clear entire screen to background color. This isn't
  'done until the image's palette is set, to avoid flicker
  'on some GIFs.
    LINE (0, 0)-(319, 199), Background, BF
    FirstTime = -1
END IF

'Decode LZW data stream to screen.
DO
    'Retrieve one LZW code.
    GOSUB GetCode
    'Is it an end of stream code?
    IF Code <> EOSCode THEN
        'Is it a clear code? (The clear code resets the sliding
        'dictionary - it *should* be the first LZW code present in
        'the data stream.)
        IF Code = ClearCode THEN
            NextCode = FirstCode
            CodeSize = StartCodeSize
            MaxCode = StartMaxCode
            DO: GOSUB GetCode: LOOP WHILE Code = ClearCode
            IF Code = EOSCode THEN GOTO ImageDone
            LastCode = Code: LastPixel = Code
            IF x < 320 AND y < 200 THEN POKE x + YBase, LastPixel
            x = x + 1: IF x = XEnd THEN GOSUB NextScanLine
        ELSE
            CurCode = Code: StackPointer = 0

            'Have we entered this code into the dictionary yet?
            IF Code >= NextCode THEN
                IF Code > NextCode THEN GOTO AllDone 'Bad GIF if this happens.
               'mimick last code if we haven't entered the requested
               'code into the dictionary yet
                CurCode = LastCode
                OutStack(StackPointer) = LastPixel
                StackPointer = StackPointer + 1
            END IF

            'Recursively get each character of the string.
            'Since we get the characters in reverse, "push" them
            'onto a stack so we can "pop" them off later.
            'Hint: There is another, much faster way to accomplish
            'this that doesn't involve a decoding stack at all...
            DO WHILE CurCode >= FirstCode
                OutStack(StackPointer) = Suffix(CurCode)
                StackPointer = StackPointer + 1
                CurCode = Prefix(CurCode)
            LOOP

            LastPixel = CurCode
            IF x < 320 AND y < 200 THEN POKE x + YBase, LastPixel
            x = x + 1: IF x = XEnd THEN GOSUB NextScanLine

            '"Pop" each character onto the display.
            FOR a = StackPointer - 1 TO 0 STEP -1
                IF x < 320 AND y < 200 THEN POKE x + YBase, OutStack(a)
                x = x + 1: IF x = XEnd THEN GOSUB NextScanLine
            NEXT

            'Can we put this new string into our dictionary? (Some GIF
            'encoders will wait a bit when the dictionary is full
            'before sending a clear code- this increases compression
            'because the dictionary's contents are thrown away less
            'often.)
            IF NextCode < 4096 THEN
                'Store new string in the dictionary for later use.
                Prefix(NextCode) = LastCode
                Suffix(NextCode) = LastPixel
                NextCode = NextCode + 1
                'Time to increase the LZW code size?
                IF (NextCode > MaxCode) AND (CodeSize < 12) THEN
                    CodeSize = CodeSize + 1
                    MaxCode = MaxCode * 2 + 1
                END IF
            END IF
            LastCode = Code
        END IF
    END IF
LOOP UNTIL Code = EOSCode
ImageDone:

LOOP

AllDone:
GOTO 20

'Slowly reads one byte from the GIF file...
GetByte: a$ = " ": GET #1, , a$: a = ASC(a$): RETURN

'Moves down one scanline. If the GIF is interlaced, then the number
'of scanlines skipped is based on the current pass.
NextScanLine:
    IF Interlaced THEN
        y = y + PassStep
        IF y >= YEnd THEN
            PassNumber = PassNumber + 1
            SELECT CASE PassNumber
            CASE 1: y = 4: PassStep = 8
            CASE 2: y = 2: PassStep = 4
            CASE 3: y = 1: PassStep = 2
            END SELECT
        END IF
    ELSE
        y = y + 1
    END IF
    x = XStart: YBase = y * 320&
RETURN

'Reads a multibit code from the data stream.
GetCode:
    WorkCode = LastChar \ ShiftOut(BitsIn)
   'Loop while more bits are needed.
    DO WHILE CodeSize > BitsIn
'Reads a byte from the LZW data stream. Since the data stream is
'blocked, a check is performed for the end of the current block
'before each byte is fetched.
        IF BlockPointer > BlockSize THEN
          'Retrieve block's length
            GOSUB GetByte: BlockSize = a
            a$ = SPACE$(BlockSize): GET #1, , a$
            BlockPointer = 1
        END IF
      'Yuck, ASC() and MID$() aren't that fast.
        LastChar = ASC(MID$(a$, BlockPointer, 1))
        BlockPointer = BlockPointer + 1
      'Append 8 more bits to the input buffer
        WorkCode = WorkCode OR LastChar * Powersof2(BitsIn)
        BitsIn = BitsIn + 8
    LOOP
  'Take away x number of bits.
    BitsIn = BitsIn - CodeSize
  'Return code to caller.
    Code = WorkCode AND MaxCode
RETURN
20


END SUB

DEFSNG A-Z
SUB loadmap
LINE (1, 1)-(maxx * con, maxy * con), 0, BF
OPEN dir$ + "maps.dat" FOR INPUT AS #2

FOR i = 1 TO 20
  INPUT #2, board$(i)
 NEXT i

FOR j = 1 TO 20
 FOR k = 1 TO 20
  SELECT CASE MID$(board$(j), k, 1)
   CASE "X": PUT (k * con, j * con), wall
   CASE " ": PUT (k * con, j * con), blank
  END SELECT
 NEXT
NEXT
CLOSE #2

END SUB

SUB mainmenu
CLS
COLOR 253
LOCATE 5, 15: PRINT "Main Menu"
COLOR 252
LOCATE 9, 10: PRINT "1. The Game"
LOCATE 11, 10: PRINT "2. The Story"
LOCATE 13, 10: PRINT "3. Instructions"
LOCATE 15, 10: PRINT "4. Credits"
LOCATE 17, 10: PRINT "5. Quit"
COLOR 15: LOCATE 22, 30: PRINT "v 0.02b"
DO
 move$ = INKEY$
LOOP UNTIL move$ = "1" OR move$ = "2" OR move$ = "3" OR move$ = "4" OR move$ = "5"
IF move$ = "1" THEN
              view1
              game
ELSEIF move$ = "2" THEN
             story
ELSEIF move$ = "3" THEN
              instructions
ELSEIF move$ = "4" THEN
             credits

ELSEIF move$ = "5" THEN
              gameover
 
END IF

END SUB

SUB moveinput
DO
m$ = INKEY$
LOOP UNTIL m$ = CHR$(0) + "M" OR m$ = CHR$(0) + "K" OR m$ = CHR$(27) OR m$ = CHR$(0) + "H" OR m$ = CHR$(0) + "P"
LET oldx = x: LET oldy = y

IF m$ = CHR$(0) + "M" THEN  'Right
        loadmap
        turnright
ELSEIF m$ = CHR$(0) + "K" THEN  'Left
        loadmap
        turnleft
     
ELSEIF m$ = CHR$(0) + "H" THEN  'forward
        loadmap
        calcforward

ELSEIF m$ = CHR$(0) + "P" THEN  'backward
        loadmap
        calcbackward

     
ELSEIF m$ = CHR$(27) THEN
       mainmenu
END IF

END SUB

SUB place (choice)
IF choice = 1 THEN
        PUT (1, 1), wall1
ELSEIF choice = 2 THEN
        PUT (48, 1), wall2
ELSEIF choice = 3 THEN
        PUT (71, 1), wall3
ELSEIF choice = null THEN
        PUT (84, 1), null
ELSEIF choice = 4 THEN
        PUT (105, 1), wall4
ELSEIF choice = 5 THEN
        PUT (117, 1), wall5
ELSEIF choice = 6 THEN
        PUT (141, 1), wall6
ELSEIF choice = 7 THEN
        PUT (1, 1), wall7
ELSEIF choice = 8 THEN
        PUT (48, 1), wall8
ELSEIF choice = 9 THEN
        PUT (71, 1), wall9
ELSEIF choice = 13 THEN
        PUT (84, 1), wall13
ELSEIF choice = 10 THEN
        PUT (105, 1), wall10
ELSEIF choice = 11 THEN
        PUT (117, 1), wall11
ELSEIF choice = 12 THEN
        PUT (141, 1), wall12
ELSEIF choice = 14 THEN
        PUT (71, 1), wall14
ELSEIF choice = 16 THEN
        loadgif ("image5")
        CLOSE #1
ELSEIF choice = 15 THEN
        PUT (48, 1), wall15
END IF

END SUB

SUB placechar
LET xcord = (x * con) / con
LET ycord = (maxy - (y * con) / con)
IF direction = n THEN
       PUT (x * con, y * con), facen
ELSEIF direction = e THEN
      
        PUT (x * con, y * con), facee
ELSEIF direction = s THEN
     
        PUT (x * con, y * con), faces
ELSEIF direction = w THEN
     
         PUT (x * con, y * con), facew
END IF

END SUB

SUB render3d
'This sub will clear the map and then puts the 3D rendering on the
'view screen.
LINE (1, 1)-(maxx * con, maxy * con), 0, BF

IF dd1 = true AND dd2 = false THEN
        place (1)
END IF
IF dd2 = true THEN
        place (2)
END IF
IF dd3 = true AND dd2 = false THEN
        place (6)
END IF
IF dd4 = true AND dd2 = false AND dd5 = fale THEN
        place (2)
END IF
IF dd4 = true AND dd1 AND dd2 = false THEN
        place (7)
END IF
IF dd6 = true AND dd3 = false AND dd2 = false THEN
        place (12)
END IF
IF dd6 = true AND dd2 = false AND dd5 = false THEN
        place (5)
END IF
IF dd5 = true AND dd2 = false THEN
        place (15)
END IF
IF dd7 = true AND dd4 = false AND dd1 = false THEN
        place (8)
END IF
IF dd7 = true AND dd8 = false AND dd5 = false AND dd2 = false THEN
        place (3)
END IF
IF dd9 = true AND dd6 = false AND dd3 = false THEN
        place (11)
END IF
IF dd9 = true AND dd8 = false AND dd5 = false AND dd2 = false THEN
        place (4)
END IF
IF dd8 = true AND dd5 = false AND dd2 = false THEN
        place (14)
END IF
IF dd10 = true AND dd7 = false AND dd4 = false AND dd1 = false THEN
        place (9)
END IF
IF dd11 = true AND dd8 = false AND dd5 = false AND dd2 = false THEN
        place (13)
END IF
IF dd12 = true AND dd9 = false AND dd6 = false AND dd3 = false THEN
        place (10)
END IF
IF dd11 = false AND dd8 = false AND dd5 = false AND dd2 = false THEN
        place (null)
END IF

END SUB

SUB software
LOCATE 10, 9: PRINT "B.M. SOFTWARE PRESENTS"
SLEEP 2


END SUB

SUB story
CLS
SCREEN 13
WINDOW (0, 0)-(100, 100)
LINE (0, 30)-(100, 30)
LINE (40, 60)-(50, 40), 1, BF
LINE (45, 40)-(45, 55), 0
LINE (40, 40)-(38, 38), 220
LINE (38, 38)-(52, 38), 220
LINE (52, 38)-(50, 40), 220
LINE (50, 40)-(40, 40), 220
PAINT (50, 39), 220
LINE (45, 38)-(45, 40), 0
LINE (50, 60)-(40, 75), 4, BF
LINE (40, 75)-(35, 70), 4, BF
LINE (50, 75)-(55, 70), 4, BF
CIRCLE (45, 80), 4, 6
PAINT (45, 80), 6
LINE (35, 70)-(33, 60), 6
LINE (33, 60)-(30, 60), 6
LINE (30, 60)-(35, 75), 6
LINE (35, 75)-(35, 70), 6
PAINT (31, 61), 6
LINE (55, 70)-(58, 60), 6
LINE (58, 60)-(60, 60), 6
LINE (60, 60)-(55, 75), 6
LINE (55, 70)-(55, 75), 6
PAINT (56, 71), 6
LINE (44, 78)-(46, 78), 0
LINE (43, 81)-(43, 82), 0
LINE (47, 81)-(47, 82), 0
LINE (45, 80)-(45, 81), 0
LINE (41, 86)-(49, 84), 230, BF
LINE (41, 86)-(42, 81), 230, BF
LINE (48.5, 86)-(49.5, 81), 230, BF
LOCATE 19, 1: PRINT "You work for the E.X.P.L.O.R. an elite "
LOCATE 20, 1: PRINT "group of explorers sent out to find"
LOCATE 21, 1: PRINT "strange new planets and civilizations."
LOCATE 22, 1: PRINT "You are now on board the Starship "
LOCATE 23, 1: PRINT "Enterprize, where you are in command."
DO: LOOP UNTIL INKEY$ = " "


LOCATE 19, 1: PRINT "You lived your life as Captain of the "
LOCATE 20, 1: PRINT "Starship Enterprize when suddenly you"
LOCATE 21, 1: PRINT "were beamed off the Ship and ended     "
LOCATE 22, 1: PRINT "up on a strange Planet Where no one"
LOCATE 23, 1: PRINT "is in sight. To bad for you.          "

FOR li = 30 TO 70
LINE (li + 1, 31)-(li + 2, 90), 14, BF
LINE (li, 90)-(li + 1, 31), 0, BF
FOR time.delay = 1 TO 10000: NEXT time.delay
NEXT li
LINE (71, 31)-(72, 90), 0, BF
DO: LOOP UNTIL INKEY$ = " "
LINE (71, 90)-(72, 31), 0, BF
CIRCLE (50, 70), 10, 1
PAINT (50, 70), 1
LINE (35, 70)-(42, 65), 14
LINE (42, 65)-(44, 60), 14
LINE (44, 60)-(65, 75), 14
LINE (65, 75)-(35, 70), 14
PAINT (50, 70), 14
LINE (0, 30)-(100, 0), 0, BF

LOCATE 20, 1: PRINT "   E.X.P.L.O.R.: TRANSMISSION COMPLETE"
LOCATE 22, 15: PRINT "(Press Space)"
DO: LOOP UNTIL INKEY$ = " "
mainmenu

END SUB

SUB title
WINDOW (0, 0)-(300, 300)
CLS
LINE (50, 225)-(250, 75), 1, BF
LINE (50, 225)-(250, 75), 2, B
LINE (60, 215)-(240, 85), 15, BF
LINE (60, 215)-(240, 85), 7, B
LINE (70, 190)-(75, 130), 38, BF
LINE (75, 190)-(90, 185), 38, BF
LINE (75, 160)-(90, 165), 38, BF
LINE (75, 130)-(90, 135), 38, BF
LINE (95, 190)-(120, 130), 38
LINE (120, 130)-(125, 130), 38
LINE (125, 130)-(100, 190), 38
LINE (100, 190)-(95, 190), 38
PAINT (98, 188), 38
LINE (95, 130)-(120, 190), 38
LINE (120, 190)-(125, 190), 38
LINE (125, 190)-(100, 130), 38
LINE (100, 130)-(95, 130), 38
PAINT (98, 132), 38
PAINT (124, 188), 38
LINE (130, 190)-(135, 130), 38, BF
CIRCLE (135, 176), 10, 38, 4.5, 2
PAINT (140, 176), 38
LINE (150, 190)-(155, 130), 38, BF
LINE (155, 135)-(170, 130), 38, BF
CIRCLE (190, 160), 20, 38
CIRCLE (190, 160), 15, 38
PAINT (171, 160), 38
LINE (215, 190)-(220, 130), 38, BF
CIRCLE (220, 175), 12, 38, 4.5, 2
PAINT (221, 175), 38
LINE (220, 160)-(235, 130), 38
LINE (235, 130)-(230, 130), 38
LINE (230, 130)-(215, 160), 38
PAINT (232, 131), 38
LOCATE 17, 15: COLOR 40: PRINT "A New World"
DO: LOOP UNTIL INKEY$ = " "

END SUB

SUB turnleft
        IF direction = n THEN
                 PUT (x * con, y * con), facen
        ELSEIF direction = s THEN
                 PUT (x * con, y * con), faces
        ELSEIF direction = e THEN
                 PUT (x * con, y * con), facee
        ELSEIF direction = w THEN
                 PUT (x * con, y * con), facew
        END IF

        LET direction = direction - 1
        IF direction = 0 THEN LET direction = 4

END SUB

SUB turnright
        IF direction = n THEN
                 PUT (x * con, y * con), facen
        ELSEIF direction = s THEN
                 PUT (x * con, y * con), faces
        ELSEIF direction = e THEN
                 PUT (x * con, y * con), facee
        ELSEIF direction = w THEN
                 PUT (x * con, y * con), facew
        END IF
        LET direction = direction + 1
        IF direction = 5 THEN LET direction = 1

END SUB

SUB view1
CLS
LINE (0, 0)-(22 * con, 22 * con), 15, B
LINE (23 * con, 1)-(160, 100), 15, B
LINE ((23 * con) + 1, 2)-(159, 35), 15, B
COLOR 14: LOCATE 2, 28: PRINT "E.X.P.L.O.R."
END SUB

SUB writecord
COLOR 15
LOCATE 11, 27: PRINT "Your Location"
COLOR 2: LOCATE 13, 34: PRINT xcord - 1
LOCATE 13, 30: PRINT "x"
COLOR 9: LOCATE 14, 34: PRINT ycord - 1
LOCATE 14, 30: PRINT "y"
LOCATE 4, 31
IF direction = n THEN
COLOR 1
PRINT "North"
ELSEIF direction = e THEN
COLOR 2
PRINT "East "
ELSEIF direction = s THEN
COLOR 3
PRINT "South"
ELSEIF direction = w THEN
COLOR 4
PRINT "West "
END IF
COLOR 15
END SUB

