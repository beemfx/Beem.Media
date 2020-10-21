'$INCLUDE: 'walls.bh'
'$INCLUDE: 'consts.bh'

' DIM SHARED wall1(100), wall2(100), wall3(100), wall5(100)
' DIM SHARED wall6(100), wall7(100), wall8(100), wall9(100), wall10(100)
' DIM SHARED wall11(100), wall12(100), wall13(100), wall14(100), wall15(100)

SUB WallsDrawWall (wallchoice)
	IF wallchoice = 1 THEN
		LINE (1, 1)-(21 * con, 21 * con), 15, B
		LINE (2, 2)-(2, (21 * con) - 1)
		LINE (2, 2)-(15, 15)
		LINE (2, (21 * con) - 1)-(15, (21 * con) - 15)
		LINE (15, (21 * con) - 15)-(15, 15)
		PAINT (5, 10), 8, 15
	ELSEIF wallchoice = 10 THEN
		LINE ((21 * con) - 30, 30)-(30, 30)
		LINE ((21 * con) - 30, (21 * con) - 30)-(30, (21 * con) - 30)
		PAINT (38, 38), 8, 15
	ELSEIF wallchoice = 11 THEN
		LINE (1, 1)-(21 * con, 21 * con), 15, B
		LINE (15, 30)-(15, (21 * con) - 30)
		LINE (15, 30)-(30, 30)
		LINE (15, (21 * con) - 30)-(30, (21 * con) - 30)
		LINE (30, (21 * con) - 30)-(30, 30)
		PAINT (18, 33), 8, 15

		LINE ((21 * con) - 15, 30)-((21 * con) - 15, (21 * con) - 30)
		LINE ((21 * con) - 15, 30)-((21 * con) - 30, 30)
		LINE ((21 * con) - 15, (21 * con) - 30)-((21 * con) - 30, (21 * con) - 30)
		LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 30, 30)
		PAINT ((21 * con) - 18, 33), 8, 15

		LINE (30, 30)-(40, 40)
		LINE (30, (21 * con) - 30)-(40, (21 * con) - 40)
		LINE (40, 40)-(40, (21 * con) - 40)
		PAINT (38, 45), 8, 15
	ELSEIF wallchoice = 12 THEN
		LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 40, (21 * con) - 40)
		LINE ((21 * con) - 30, 30)-((21 * con) - 40, 40)
		LINE ((21 * con) - 40, 40)-((21 * con) - 40, (21 * con) - 40)
		PAINT ((21 * con) - 33, 45), 8, 15
	ELSEIF wallchoice = 13 THEN
		LINE (40, 40)-((21 * con) - 40, 40)
		LINE (40, (21 * con) - 40)-((21 * con) - 40, (21 * con) - 40)
		PAINT (45, 45), 8, 15
	ELSEIF wallchoice = 14 THEN
		LINE (1, 1)-(21 * con, 21 * con), 15, B
		LINE (15, 30)-(15, (21 * con) - 30)
		LINE (15, 30)-(30, 30)
		LINE (15, (21 * con) - 30)-(30, (21 * con) - 30)
		LINE (30, (21 * con) - 30)-(30, 30)
		PAINT (18, 33), 8, 15

		LINE ((21 * con) - 15, 30)-((21 * con) - 15, (21 * con) - 30)
		LINE ((21 * con) - 15, 30)-((21 * con) - 30, 30)
		LINE ((21 * con) - 15, (21 * con) - 30)-((21 * con) - 30, (21 * con) - 30)
		LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 30, 30)
		PAINT ((21 * con) - 18, 33), 8, 15

		LINE (30, 40)-(40, 40)
		LINE (30, (21 * con) - 40)-(40, (21 * con) - 40)
		LINE (40, 40)-(40, (21 * con) - 40)
		PAINT (38, 45), 8, 15
	ELSEIF wallchoice = 15 THEN
		LINE ((21 * con) - 30, (21 * con) - 40)-((21 * con) - 40, (21 * con) - 40)
		LINE ((21 * con) - 30, 40)-((21 * con) - 40, 40)
		LINE ((21 * con) - 40, 40)-((21 * con) - 40, (21 * con) - 40)
		PAINT ((21 * con) - 33, 45), 8, 15
	ELSEIF wallchoice = 16 THEN
			  'LINE (1, 30)-(16, (21 * con) - 30), 0, BF
			  'PUT (1, 30), wall9
	ELSEIF wallchoice = 17 THEN
			  'LINE ((21 * con) - 15, 30)-(21 * con, (21 * con) - 30), 0, BF
			  'PUT ((21 * con) - 15, 30), wall9
	ELSEIF wallchoice = 18 THEN
			  'LINE (16, 30)-(26, (21 * con) - 30), 0, BF
			  'PUT (16, 30), wall11
	ELSEIF wallchoice = 19 THEN
			  'LINE ((21 * con) - 25, 30)-((21 * con) - 15, (21 * con) - 30), 0, BF
			  'PUT ((21 * con) - 25, 30), wall12
	ELSEIF wallchoice = 2 THEN
		LINE ((21 * con) - 1, 2)-((21 * con) - 1, (21 * con) - 1)
		LINE ((21 * con) - 1, 2)-((21 * con) - 15, 15)
		LINE ((21 * con) - 1, (21 * con) - 1)-((21 * con) - 15, (21 * con) - 15)
		LINE ((21 * con) - 15, (21 * con) - 15)-((21 * con) - 15, 15)
		PAINT ((21 * con) - 5, 16), 8, 15
	ELSEIF wallchoice = 20 THEN
			  'LINE (20, 40)-(30, (21 * con) - 40), 0, BF
			  'PUT (20, 40), wall14
	ELSEIF wallchoice = 21 THEN
			  'LINE ((21 * con) - 25, 40)-((21 * con) - 15, (21 * con) - 40), 0, BF
			  'PUT ((21 * con) - 25, 40), wall15
	ELSEIF wallchoice = 22 THEN
			  'LINE (1, 15)-(16, (21 * con) - 15), 0, BF
			  'PUT (1, 15), wall6
	ELSEIF wallchoice = 23 THEN
			  'LINE ((21 * con) - 15, 15)-((21 * con), (21 * con) - 15), 0, BF
			  'PUT ((21 * con) - 15, 15), wall7
	ELSEIF wallchoice = 3 THEN
		LINE (15, 15)-((21 * con) - 15, 15)
		LINE (15, (21 * con) - 15)-((21 * con) - 15, (21 * con) - 15)
		PAINT (18, 18), 8, 15
	ELSEIF wallchoice = 4 THEN
			  'LINE (1, 15)-(15, (21 * con) - 15), 0, BF
			  'PUT (1, 15), wall5
	ELSEIF wallchoice = 5 THEN
		LINE (2, 15)-(2, (21 * con) - 1)
		LINE (2, 15)-(15, 15)
		LINE (2, (21 * con) - 15)-(15, (21 * con) - 15)
		LINE (15, (21 * con) - 15)-(15, 15)
		PAINT (5, 30), 8, 15
		LINE ((21 * con) - 1, 15)-((21 * con) - 1, (21 * con) - 15)
		LINE ((21 * con) - 1, 15)-((21 * con) - 15, 15)
		LINE ((21 * con) - 1, (21 * con) - 15)-((21 * con) - 15, (21 * con) - 15)
		LINE ((21 * con) - 15, (21 * con) - 15)-((21 * con) - 15, 15)
		PAINT ((21 * con) - 5, 16), 8, 15
	ELSEIF wallchoice = 6 THEN
		LINE (15, 15)-(30, 30)
		LINE (15, (21 * con) - 15)-(30, (21 * con) - 30)
		LINE (30, 30)-(30, (21 * con) - 30)
		PAINT (28, 40), 8, 15
	ELSEIF wallchoice = 7 THEN
		LINE ((21 * con) - 15, (21 * con) - 15)-((21 * con) - 30, (21 * con) - 30)
		LINE ((21 * con) - 15, 15)-((21 * con) - 30, 30)
		LINE ((21 * con) - 30, 30)-((21 * con) - 30, (21 * con) - 30)
		PAINT ((21 * con) - 28, 38), 8, 15
	ELSEIF wallchoice = 8 THEN
		LINE (1, 1)-(21 * con, 21 * con), 15, B
		LINE (15, 30)-(15, (21 * con) - 30)
		LINE (15, 30)-(30, 30)
		LINE (15, (21 * con) - 30)-(30, (21 * con) - 30)
		LINE (30, (21 * con) - 30)-(30, 30)
		PAINT (18, 33), 8, 15
	ELSEIF wallchoice = 9 THEN
		LINE ((21 * con) - 15, 30)-((21 * con) - 15, (21 * con) - 30)
		LINE ((21 * con) - 15, 30)-((21 * con) - 30, 30)
		LINE ((21 * con) - 15, (21 * con) - 30)-((21 * con) - 30, (21 * con) - 30)
		LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 30, 30)
		PAINT ((21 * con) - 18, 33), 8, 15
	END IF
END SUB

SUB WallsLoad


END SUB
