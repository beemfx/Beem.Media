DECLARE SUB graphicsload ()
DECLARE SUB intro ()
'============================================================================
'===              Joe's Copter :Flight of the Fittest                     ===
'===      Produced by B.M. Software                                v 1.03 ===
'============================================================================
CLS
SCREEN 1
DIM SHARED bullet(500), cop(100)
intro
WINDOW (0, 0)-(100, 100)
graphicsload
LET x = 50
LET y = 50
PUT (x, y), cop
143 PUT (x, y), cop
move$ = INKEY$
IF move$ = "6" THEN
        LET x = x + 5
ELSEIF move$ = "4" THEN
        LET x = x - 5
ELSEIF move$ = "8" THEN
        LET y = y + 5
ELSEIF move$ = "2" THEN
        LET y = y - 5
ELSEIF move$ = CHR$(27) THEN
        END
ELSEIF move$ = " " THEN
        GOTO 615
END IF
IF x <= 1 THEN LET x = 95
IF x >= 99 THEN LET x = 5
IF y >= 99 THEN LET y = 5
IF y <= 1 THEN LET y = 95
PUT (x, y), cop
DO
FOR T = 1 TO 10000: NEXT T
GOTO 143
LOOP
615 CLS
PUT (x, y), cop
LET bu = x + 5
LET y = y
IF bu > 90 THEN bu = 90
FOR bu = bu TO 90
70 PUT (bu, y), bullet
816 PUT (bu + 1, y), bullet
FOR l = 1 TO 1000: NEXT l: NEXT bu
PUT (bu, y), bullet
CLS
PUT (x, y), cop
GOTO 143

SUB graphicsload
LINE (2, 52)-(5, 52)
LINE (0, 55)-(5, 55)
LINE (2, 52)-(2, 55)
LINE (5, 52)-(5, 55)
GET (1, 52)-(5, 55), cop
CLS
LET x = 10: LET y = 10
LINE (x + 5, y)-(x + 10, y)
GET (x + 5, y)-(x + 10, y), bullet
CLS
END SUB

SUB intro
LINE (50, 100)-(200, 150) 'bottom of ski
LINE (200, 150)-(205, 145) ' curve of ski
LINE (60, 104)-(65, 100) ' leg of ski
LINE (190, 146)-(195, 140)' front leg of ski
LINE (65, 100)-(195, 140)' bottom of copter
LINE (195, 140)-(240, 130)'front bottom
LINE (240, 130)-(195, 100)'top front
LINE (195, 100)-(193, 80)' windshield
LINE (193, 80)-(10, 20)'top
LINE (10, 20)-(5, 30)'back
LINE (5, 30)-(60, 50)' bottom back
LINE (60, 50)-(65, 100)'bottom back
CIRCLE (15, 30), 15'back propeller
LINE (200, 60)-(70, 20)'top propeller
LINE (140, 41)-(136, 60) 'twirler
FOR A = 1 TO 1000: NEXT A
LOCATE 11, 11: PRINT "Joes Coptor"
LOCATE 23, 20: PRINT "B.M. SOFTWARE"
PLAY "o2t190msccccccc"
DO: LOOP UNTIL INKEY$ = " "
CLS
END SUB

