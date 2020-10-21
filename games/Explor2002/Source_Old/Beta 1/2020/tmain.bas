'$INCLUDE: 'main.bh'
'$INCLUDE: 'graphics.bh'
'$INCLUDE: 'consts.bh'
'$INCLUDE: 'walls.bh'

DIM SHARED direction, charac$, m$, x, y, oldx, oldy
DIM SHARED board$(256)
DIM SHARED xcord, ycord
DIM SHARED dda, ddb, ddc, ddd, dde, ddf, ddg, ddh, ddi, ddj, ddk, ddl
DIM SHARED ddp, ddq, ddm, ddn, ddo, wallchoice
DIM SHARED autom
DIM SHARED gbQuit AS INTEGER

CALL main

SUB main
	GraphicsInit
	WallsLoad
	dataset
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
						  'view1
						  'game
		ELSEIF move$ = "2" THEN
						 'story
		ELSEIF move$ = "3" THEN
						  'instructions
		ELSEIF move$ = "4" THEN
						 credits
		ELSEIF move$ = "5" THEN
						  gameover
		END IF
	LOOP
END SUB

SUB gameover
	CLS
	LOCATE 10, 15: PRINT "GAME OVER"
	COLOR 0
	SYSTEM
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

SUB dataset
	LET direction = w
END SUB

SUB software
	LOCATE 10, 9: PRINT "B.M. SOFTWARE PRESENTS"
	SLEEP 2
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