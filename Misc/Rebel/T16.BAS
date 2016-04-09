SCREEN 13
WINDOW (0, 0)-(100, 100)
DIM right1(1000), straight(1100), right2(1100), left1(1000), left2(1100)


'Srait on back
LINE (45, 50)-(55, 50)
LINE (45, 50)-(50, 60)
LINE (50, 60)-(55, 50)
LINE (55, 50)-(62, 43)
LINE (50, 60)-(50, 72)
LINE (45, 50)-(39, 43)
PAINT (50, 54), 25, 15
CIRCLE (50, 54), 2
PAINT (50, 54), 44, 15
GET (39, 43)-(62, 72), straight

'Right 1 back
LINE (10, 50)-(18, 45)
LINE (10, 50)-(17, 57)
LINE (17, 57)-(18, 45)
LINE (18, 45)-(21, 35)
LINE (10, 50)-(2, 46)
LINE (17, 57)-(20, 67)
PAINT (15, 51), 25, 15
CIRCLE (15, 51), 2
PAINT (15, 51), 44, 15
GET (2, 35)-(21, 67), right1


'Right 2
LINE (80, 60)-(88, 61)
LINE (80, 60)-(85, 50)
LINE (85, 50)-(88, 61)
LINE (85, 50)-(85, 40)
LINE (80, 60)-(73, 63)
LINE (88, 61)-(96, 68)
PAINT (84, 57), 25, 15
CIRCLE (84, 57), 2
PAINT (84, 57), 44, 15
GET (73, 40)-(96, 68), right2
DO: LOOP UNTIL INKEY$ = " "
CLS
SCREEN 13
WINDOW (0, 0)-(-100, 100)
'Right 1 back
LINE (-10, 50)-(-18, 45)
LINE (-10, 50)-(-17, 57)
LINE (-17, 57)-(-18, 45)
LINE (-18, 45)-(-21, 35)
LINE (-10, 50)-(-2, 46)
LINE (-17, 57)-(-20, 67)
PAINT (-15, 51), 25, 15
CIRCLE (-15, 51), 2
PAINT (-15, 51), 44, 15
GET (-2, 35)-(-21, 67), left1

'Right 2
LINE (-80, 60)-(-88, 61)
LINE (-80, 60)-(-85, 50)
LINE (-85, 50)-(-88, 61)
LINE (-85, 50)-(-85, 40)
LINE (-80, 60)-(-73, 63)
LINE (-88, 61)-(-96, 68)
PAINT (-84, 57), 25, 15
CIRCLE (-84, 57), 2
PAINT (-84, 57), 44, 15


'Note how I simply inversed they x coordinates to make the ship go the
'opposite way.
WINDOW (0, 0)-(-100, 100)

'Right 1 back
LINE (-10, 50)-(-18, 45)
LINE (-10, 50)-(-17, 57)
LINE (-17, 57)-(-18, 45)
LINE (-18, 45)-(-21, 35)
LINE (-10, 50)-(-2, 46)
LINE (-17, 57)-(-20, 67)
PAINT (-15, 51), 25, 15
CIRCLE (-15, 51), 2
PAINT (-15, 51), 44, 15

'Right 2
LINE (-80, 60)-(-88, 61)
LINE (-80, 60)-(-85, 50)
LINE (-85, 50)-(-88, 61)
LINE (-85, 50)-(-85, 40)
LINE (-80, 60)-(-73, 63)
LINE (-88, 61)-(-96, 68)
PAINT (-84, 57), 25, 15
CIRCLE (-84, 57), 2
PAINT (-84, 57), 44, 15
GET (-73, 40)-(-96, 68), left2
'CLS
WINDOW (0, 0)-(100, 100)

