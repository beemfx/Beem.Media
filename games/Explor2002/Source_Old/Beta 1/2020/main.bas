'$INCLUDE: 'main.bh'
'$INCLUDE: 'graphics.bh'
'$INCLUDE: 'consts.bh'
'$INCLUDE: 'walls.bh'

DIM SHARED direction, charac$, m$, x, y, oldx, oldy
DIM SHARED board$(482)
DIM SHARED xcord, ycord
DIM SHARED dda, ddb, ddc, ddd, dde, ddf, ddg, ddh, ddi, ddj, ddk, ddl
DIM SHARED ddp, ddq, ddm, ddn, ddo, wallchoice
DIM SHARED autom
DIM SHARED gbQuit AS INTEGER

CALL main

'ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
'บ                                                                 บ
'บ                  E.X.P.L.O.R (tm)                               บ
'บ                                                                 บ
'บ                         A New World                             บ        
'บ                                                                 บ
'บ                                      v. BETA 0.04               บ
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

SUB automap
	DO: LOOP UNTIL INKEY$ = CHR$(27)
END SUB

SUB calcbackward
		  IF direction = n THEN
					 CALL GraphicsDrawFaceN(x * con, y * con)
					 LET y = y + 1
					 IF y >= maxy THEN LET y = y - 1
					 IF POINT(x * con, y * con) THEN LET y = y - 1
		  ELSEIF direction = s THEN
					 CALL GraphicsDrawFaceS(x * con, y * con)
					 LET y = y - 1
					 IF y <= miny THEN LET y = y + 1
					 IF POINT(x * con, y * con) THEN LET y = y + 1
		  ELSEIF direction = e THEN
					 CALL GraphicsDrawFaceE(x * con, y * con)
					 LET x = x - 1
					 IF x <= minx THEN LET x = x + 1
					 IF POINT(x * con, y * con) THEN LET x = x + 1
		  ELSEIF direction = w THEN
					 CALL GraphicsDrawFaceW(x * con, y * con)
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
					 CALL GraphicsDrawFaceN(x * con, y * con)
					 LET y = y - 1
					 IF y <= miny THEN LET y = y + 1
					 IF POINT(x * con, y * con) THEN LET y = y + 1
		  ELSEIF direction = s THEN
					 CALL GraphicsDrawFaceS(x * con, y * con)
					 LET y = y + 1
					 IF y >= maxy THEN LET y = y - 1
					 IF POINT(x * con, y * con) THEN LET y = y - 1
		  ELSEIF direction = e THEN
					 CALL GraphicsDrawFaceE(x * con, y * con)
					 LET x = x + 1
					 IF x >= maxx THEN LET x = x - 1
					 IF POINT(x * con, y * con) THEN LET x = x - 1
		  ELSEIF direction = w THEN
					 CALL GraphicsDrawFaceW(x * con, y * con)
					 LET x = x - 1
					 IF x <= minx THEN LET x = x + 1
					 IF POINT(x * con, y * con) THEN LET x = x + 1
		  END IF


END SUB

SUB calcmap
	'What this sub will do is caculate where walls and stuff need to be
	'put on the 3d image.  Then the data will be used in render3d to place
	'the images on the view screen.

	LET dda = false: LET ddb = false: LET ddc = false: LET ddd = false
	LET dde = false: LET ddf = false: LET ddg = false: LET ddh = false
	LET ddi = false: LET ddj = false: LET ddk = false: LET ddl = false
	LET ddm = false: LET ddn = false: LET ddo = false: LET ddp = false
	LET ddq = false

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
	IF POINT((x - 2) * con, (y - 3) * con) THEN LET dda = true
	IF POINT((x - 1) * con, (y - 3) * con) THEN LET ddb = true
	IF POINT(x * con, (y - 3) * con) THEN LET ddc = true
	IF POINT((x + 1) * con, (y - 3) * con) THEN LET ddd = true
	IF POINT((x + 2) * con, (y - 3) * con) THEN LET dde = true

	IF POINT((x - 2) * con, (y - 2) * con) THEN LET ddf = true
	IF POINT((x - 1) * con, (y - 2) * con) THEN LET ddg = true
	IF POINT(x * con, (y - 2) * con) THEN LET ddh = true
	IF POINT((x + 1) * con, (y - 2) * con) THEN LET ddi = true
	IF POINT((x + 2) * con, (y - 2) * con) THEN LET ddj = true

	IF POINT((x - 2) * con, (y - 1) * con) THEN LET ddk = true
	IF POINT((x - 1) * con, (y - 1) * con) THEN LET ddl = true
	IF POINT((x * con), (y - 1) * con) THEN LET ddm = true
	IF POINT((x + 1) * con, (y - 1) * con) THEN LET ddn = true
	IF POINT((x + 2) * con, (y - 1) * con) THEN LET ddo = true

	IF POINT((x - 1) * con, y * con) THEN LET ddp = true
	IF POINT((x + 1) * con, y * con) THEN LET ddq = true

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
END SUB

SUB game
	gbQuit = 0
	loadmap
	
	LET x = 5
	LET y = 6
	LET direction = w
	
	CALL GraphicsDrawFaceN(x * con, y * con)
	view1
	autom = true
	
	DO WHILE gbQuit = 0
		loadmap
		placechar
		calcmap
		render3d
		writecord
		moveinput
	LOOP
END SUB

SUB gameover
	CLS
	LOCATE 10, 15: PRINT "GAME OVER"
	COLOR 0
	SYSTEM
END SUB

SUB instructions
	CLS
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
END SUB

SUB loadauto
	LINE (1, 1)-(maxx * con, maxy * con), 0, BF
	OPEN "maps.dat" FOR INPUT AS #2

	FOR i = 1 TO 20
	  INPUT #2, board$(i)
	 NEXT i

	FOR j = 1 TO 20
	 FOR k = 1 TO 20
	  SELECT CASE MID$(board$(j), k, 1)
		CASE "X": CALL GraphicsDrawWallX(k * con, j * con)
		CASE " ": CALL GraphicsDrawBlankX(k * con, j * con)
	  END SELECT
	 NEXT
	NEXT
	CLOSE #2
END SUB

SUB loadmap
	LINE (1, 1)-(maxx * con, maxy * con), 0, BF
	OPEN "maps.dat" FOR INPUT AS #2

	FOR i = 1 TO 20
	  INPUT #2, board$(i)
	 NEXT i

	FOR j = 1 TO 20
	 FOR k = 1 TO 20
	  SELECT CASE MID$(board$(j), k, 1)
		CASE "X": CALL GraphicsDrawWall(k * con, j * con)
		CASE " ": CALL GraphicsDrawBlank(k * con, j * con)
	  END SELECT
	 NEXT
	NEXT
	CLOSE #2
END SUB

SUB main
	GraphicsInit
	WallsLoad
	software
	title
	mainmenu
END SUB

SUB mainmenu
	DO WHILE (1)
		CLS
		COLOR 40
		LOCATE 5, 15: PRINT "Main Menu"
		COLOR 45
		LOCATE 9, 10: PRINT "1. The Game"
		LOCATE 11, 10: PRINT "2. The Story"
		LOCATE 13, 10: PRINT "3. Instructions"
		LOCATE 15, 10: PRINT "4. Credits"
		LOCATE 17, 10: PRINT "5. Quit"
		COLOR 15: LOCATE 22, 30: PRINT "v 0.04b"
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
	LOOP
END SUB

SUB moveinput
	DO
	m$ = INKEY$
	LOOP UNTIL m$ = CHR$(0) + "M" OR m$ = CHR$(0) + "K" OR m$ = CHR$(27) OR m$ = CHR$(0) + "H" OR m$ = CHR$(0) + "P" OR m$ = "M" OR m$ = "m"
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
	ELSEIF m$ = "M" OR m$ = "m" THEN
			  IF autom = true THEN
				  loadauto
				  placechara
				  automap
			  ELSEIF autom = false THEN
			  END IF
	ELSEIF m$ = CHR$(27) THEN
			 gbQuit = 1
	END IF

END SUB

SUB placechar
	LET xcord = (x * con) / con
	LET ycord = (maxy - (y * con) / con)
	IF direction = n THEN
		CALL GraphicsDrawFaceN(x * con, y * con)
	ELSEIF direction = e THEN
		CALL GraphicsDrawFaceE(x * con, y * con)
	ELSEIF direction = s THEN
		CALL GraphicsDrawFaceS(x * con, y * con)
	ELSEIF direction = w THEN
		CALL GraphicsDrawFaceW(x * con, y * con)
	END IF

END SUB

SUB placechara
	LET xcord = (x * con) / con
	LET ycord = (maxy - (y * con) / con)
	IF direction = n THEN
		CALL GraphicsDrawFaceNA(x * con, y * con)
	ELSEIF direction = e THEN  
		CALL GraphicsDrawFaceEA(x * con, y * con)
	ELSEIF direction = s THEN
		CALL GraphicsDrawFaceSA(x * con, y * con)
	ELSEIF direction = w THEN 
		CALL GraphicsDrawFaceWA(x * con, y * con)
	END IF

END SUB

SUB render3d
	'This sub will clear the map and then puts the 3D rendering on the
	'view screen.
	LINE (1, 1)-(maxx * con, maxy * con), 0, BF

	IF dda = true THEN WallsDrawWall (20)
	IF ddb = true THEN WallsDrawWall (14)
	IF ddc = true THEN WallsDrawWall (13)
	IF ddd = true THEN WallsDrawWall (15)
	IF dde = true THEN WallsDrawWall (21)

	IF ddf = true THEN
	WallsDrawWall (18)
	WallsDrawWall (16)
	END IF
	IF ddg = true THEN
	WallsDrawWall (11)
	WallsDrawWall (8)
	END IF
	IF ddj = true THEN
	WallsDrawWall (19)
	WallsDrawWall (17)
	END IF
	IF ddi = true THEN
	WallsDrawWall (12)
	WallsDrawWall (9)
	END IF

	IF ddh = true THEN WallsDrawWall (10)
	IF ddk = true THEN WallsDrawWall (22)
	IF ddo = true THEN WallsDrawWall (23)
	IF ddl = true THEN
	WallsDrawWall (4)
	WallsDrawWall (6)
	END IF
	IF ddn = true THEN
	WallsDrawWall (7)
	WallsDrawWall (5)
	END IF
	IF ddm = true THEN WallsDrawWall (3)
	IF ddp = true THEN WallsDrawWall (1)
	IF ddq = true THEN WallsDrawWall (2)
END SUB

SUB software
	LOCATE 10, 9: PRINT "B.M. SOFTWARE PRESENTS"
	SLEEP 2

END SUB

SUB story
	WINDOW (0, 0)-(100, 100)
	CLS
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
	
	GraphicsSetDefaultViewport
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
	GraphicsSetDefaultViewport
END SUB

SUB turnleft
		  IF direction = n THEN
					  CALL GraphicsDrawFaceN(x * con, y * con)
		  ELSEIF direction = s THEN
					  CALL GraphicsDrawFaceS(x * con, y * con)
		  ELSEIF direction = e THEN
					  CALL GraphicsDrawFaceE(x * con, y * con)
		  ELSEIF direction = w THEN
					  CALL GraphicsDrawFaceW(x * con, y * con)
		  END IF

		  LET direction = direction - 1
		  IF direction = 0 THEN LET direction = 4

END SUB

SUB turnright
		  IF direction = n THEN
					  CALL GraphicsDrawFaceN(x * con, y * con)
		  ELSEIF direction = s THEN
					  CALL GraphicsDrawFaceS(x * con, y * con)
		  ELSEIF direction = e THEN
					  CALL GraphicsDrawFaceE(x * con, y * con)
		  ELSEIF direction = w THEN
					  CALL GraphicsDrawFaceW(x * con, y * con)
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

