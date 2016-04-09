
SUB drawwall (wallchoice)
	IF wallchoice = 1 THEN
			  LINE (1, 2)-(14, 21 * con), 0, BF
			  PUT (1, 2), wall1
	ELSEIF wallchoice = 10 THEN
			  LINE (30, 30)-((21 * con) - 30, (21 * con) - 30), 0, BF
			  PUT (30, 30), wall10
	ELSEIF wallchoice = 11 THEN
			  LINE (30, 30)-(40, (21 * con) - 30), 0, BF
			  PUT (30, 30), wall11
	ELSEIF wallchoice = 12 THEN
			  LINE ((21 * con) - 40, 30)-((21 * con) - 30, (21 * con) - 30), 0, BF
			  PUT ((21 * con) - 40, 30), wall12
	ELSEIF wallchoice = 13 THEN
			  LINE (40, 40)-((21 * con) - 40, (21 * con) - 40), 0, BF
			  PUT (40, 40), wall13
	ELSEIF wallchoice = 14 THEN
			  LINE (25, 40)-(30, (21 * con) - 40), 0, BF
			  PUT (25, 40), wall13
	ELSEIF wallchoice = 15 THEN
			  LINE ((21 * con) - 40, 40)-((21 * con) - 30, (21 * con) - 40), 0, BF
			  PUT ((21 * con) - 40, 40), wall13
	ELSEIF wallchoice = 16 THEN
			  LINE (1, 30)-(16, (21 * con) - 30), 0, BF
			  PUT (1, 30), wall9
	ELSEIF wallchoice = 17 THEN
			  LINE ((21 * con) - 15, 30)-(21 * con, (21 * con) - 30), 0, BF
			  PUT ((21 * con) - 15, 30), wall9
	ELSEIF wallchoice = 18 THEN
			  LINE (16, 30)-(26, (21 * con) - 30), 0, BF
			  PUT (16, 30), wall11
	ELSEIF wallchoice = 19 THEN
			  LINE ((21 * con) - 25, 30)-((21 * con) - 15, (21 * con) - 30), 0, BF
			  PUT ((21 * con) - 25, 30), wall12
	ELSEIF wallchoice = 2 THEN
			  LINE ((21 * con) - 15, 1)-((21 * con), (21 * con)), 0, BF
			  PUT ((21 * con) - 15, 1), wall2
	ELSEIF wallchoice = 20 THEN
			  LINE (20, 40)-(30, (21 * con) - 40), 0, BF
			  PUT (20, 40), wall14
	ELSEIF wallchoice = 21 THEN
			  LINE ((21 * con) - 25, 40)-((21 * con) - 15, (21 * con) - 40), 0, BF
			  PUT ((21 * con) - 25, 40), wall15
	ELSEIF wallchoice = 22 THEN
			  LINE (1, 15)-(16, (21 * con) - 15), 0, BF
			  PUT (1, 15), wall6
	ELSEIF wallchoice = 23 THEN
			  LINE ((21 * con) - 15, 15)-((21 * con), (21 * con) - 15), 0, BF
			  PUT ((21 * con) - 15, 15), wall7
	ELSEIF wallchoice = 3 THEN
			  LINE (15, 15)-((21 * con) - 15, (21 * con) - 15), 0, BF
			  PUT (15, 15), wall3
	ELSEIF wallchoice = 4 THEN
			  LINE (1, 15)-(15, (21 * con) - 15), 0, BF
			  PUT (1, 15), wall5
	ELSEIF wallchoice = 5 THEN
			  LINE ((21 * con) - 15, 15)-(21 * con, (21 * con) - 15), 0, BF
			  PUT ((21 * con) - 15, 15), wall5
	ELSEIF wallchoice = 6 THEN
			  LINE (15, 15)-(30, (21 * con) - 30), 0, BF
			  PUT (15, 15), wall6
	ELSEIF wallchoice = 7 THEN
			  LINE ((21 * con) - 30, 15)-((21 * con) - 15, (21 * con) - 15), 0, BF
			  PUT ((21 * con) - 30, 15), wall7
	ELSEIF wallchoice = 8 THEN
			  LINE (15, 30)-(30, (21 * con) - 30), 0, BF
			  PUT (15, 30), wall8
	ELSEIF wallchoice = 9 THEN
			  LINE ((21 * con) - 30, 30)-((21 * con) - 15, (21 * con) - 30), 0, BF
			  PUT ((21 * con) - 30, 30), wall9
	END IF
END SUB

SUB wallload
	SCREEN 13
	WINDOW SCREEN (1, 1)-(160, 100)
 
	LINE (1, 1)-(21 * con, 21 * con), 15, B
	LINE (2, 2)-(2, (21 * con) - 1)
	LINE (2, 2)-(15, 15)
	LINE (2, (21 * con) - 1)-(15, (21 * con) - 15)
	LINE (15, (21 * con) - 15)-(15, 15)
	PAINT (5, 10), 8, 15

	GET (2, 2)-(15, (21 * con) - 1), wall1
	LINE ((21 * con) - 1, 2)-((21 * con) - 1, (21 * con) - 1)
	LINE ((21 * con) - 1, 2)-((21 * con) - 15, 15)
	LINE ((21 * con) - 1, (21 * con) - 1)-((21 * con) - 15, (21 * con) - 15)
	LINE ((21 * con) - 15, (21 * con) - 15)-((21 * con) - 15, 15)
	PAINT ((21 * con) - 5, 16), 8, 15
	GET ((21 * con) - 1, (21 * con) - 1)-((21 * con) - 15, 2), wall2

	LINE (15, 15)-((21 * con) - 15, 15)
	LINE (15, (21 * con) - 15)-((21 * con) - 15, (21 * con) - 15)
	PAINT (18, 18), 8, 15
	GET (15, 15)-((21 * con) - 15, (21 * con) - 15), wall3
	CLS
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

	GET ((21 * con) - 1, (21 * con) - 15)-((21 * con) - 15, 15), wall5
	LINE (15, 15)-(30, 30)
	LINE (15, (21 * con) - 15)-(30, (21 * con) - 30)
	LINE (30, 30)-(30, (21 * con) - 30)
	PAINT (28, 40), 8, 15
	GET (15, 15)-(30, (21 * con) - 15), wall6

	LINE ((21 * con) - 15, (21 * con) - 15)-((21 * con) - 30, (21 * con) - 30)
	LINE ((21 * con) - 15, 15)-((21 * con) - 30, 30)
	LINE ((21 * con) - 30, 30)-((21 * con) - 30, (21 * con) - 30)
	PAINT ((21 * con) - 28, 38), 8, 15
	GET ((21 * con) - 30, 15)-((21 * con) - 15, (21 * con) - 15), wall7
	CLS
	LINE (1, 1)-(21 * con, 21 * con), 15, B

	LINE (15, 30)-(15, (21 * con) - 30)
	LINE (15, 30)-(30, 30)
	LINE (15, (21 * con) - 30)-(30, (21 * con) - 30)
	LINE (30, (21 * con) - 30)-(30, 30)
	PAINT (18, 33), 8, 15
	GET (15, 30)-(30, (21 * con) - 30), wall8

	LINE ((21 * con) - 15, 30)-((21 * con) - 15, (21 * con) - 30)
	LINE ((21 * con) - 15, 30)-((21 * con) - 30, 30)
	LINE ((21 * con) - 15, (21 * con) - 30)-((21 * con) - 30, (21 * con) - 30)
	LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 30, 30)
	PAINT ((21 * con) - 18, 33), 8, 15
	GET ((21 * con) - 15, (21 * con) - 30)-((21 * con) - 30, 30), wall9
	LINE ((21 * con) - 30, 30)-(30, 30)
	LINE ((21 * con) - 30, (21 * con) - 30)-(30, (21 * con) - 30)
	PAINT (38, 38), 8, 15
	GET (30, 30)-((21 * con) - 30, (21 * con) - 30), wall10
	CLS
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

	GET (30, 30)-(40, (21 * con) - 30), wall11

	LINE ((21 * con) - 30, (21 * con) - 30)-((21 * con) - 40, (21 * con) - 40)
	LINE ((21 * con) - 30, 30)-((21 * con) - 40, 40)
	LINE ((21 * con) - 40, 40)-((21 * con) - 40, (21 * con) - 40)
	PAINT ((21 * con) - 33, 45), 8, 15
	GET ((21 * con) - 40, 30)-((21 * con) - 30, (21 * con) - 30), wall12
	LINE (40, 40)-((21 * con) - 40, 40)
	LINE (40, (21 * con) - 40)-((21 * con) - 40, (21 * con) - 40)
	PAINT (45, 45), 8, 15
	GET (40, 40)-((21 * con) - 40, (21 * con) - 40), wall13
	CLS
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

	GET (30, 40)-(40, (21 * con) - 40), wall14

	LINE ((21 * con) - 30, (21 * con) - 40)-((21 * con) - 40, (21 * con) - 40)
	LINE ((21 * con) - 30, 40)-((21 * con) - 40, 40)
	LINE ((21 * con) - 40, 40)-((21 * con) - 40, (21 * con) - 40)
	PAINT ((21 * con) - 33, 45), 8, 15
	GET ((21 * con) - 40, 40)-((21 * con) - 30, (21 * con) - 40), wall15
	CLS


END SUB

