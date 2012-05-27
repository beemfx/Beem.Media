'============================================================================
'=== This is Archer Deluxe version 1.00b                                  ===
'=== Have fun            ESTEMATED FINISH DATE 4/21/98                    ===
'=== Press Space when the guy is in front of you to kill him              ===
'=== produced by B.M. SOFTWARE                                            ===
'=== On 1/29/99 I fixed the bug so you cant see when to shoot             ===
'=== I originally meant to create better art work but I never actually    ===
'=== did that so thats why it is still the alpha version thats all.       ===
'=== I added speed adjustment 1 works for a 75 Mhz computer 20 works for  ===
'=== for a 450Mhz computer inbetween for other computers.                 ===
'============================================================================
10
CLS
SCREEN 1
PRINT
PRINT
INPUT "Please enter speed (1 for 75 Mhz 20 for 450Mhz)", speed
PRINT
 PRINT "Enter dificulty level"
 PRINT "W)imp C)hallenger or K)iller"
choice1:
DO
        a$ = INKEY$
LOOP UNTIL a$ = "K" OR a$ = "k" OR a$ = "C" OR a$ = "c" OR a$ = "w" OR a$ = "W"
CLS
        IF a$ = "K" THEN
                c = 200 * speed
        ELSEIF a$ = "C" THEN
                c = 600 * speed
        ELSEIF a$ = "W" THEN
                c = 1000 * speed
        ELSEIF a$ = "k" THEN
                c = 200 * speed
        ELSEIF a$ = "c" THEN
                c = 600 * speed
        ELSEIF a$ = "w" THEN
                c = 1000 * speed
        END IF
begin:
 KEY OFF
 DIM GUY(600)
 DIM arrow(600)
CLS
 COLOR 2, 9
'image of the one dude
 LINE (10, 100)-(50, 100)'bottom
 LINE (10, 100)-(10, 80)'left side
 CIRCLE (30, 80), 20 'main body
LINE (50, 100)-(50, 80)'right side
 LINE (15, 100)-(15, 120)'leg
 LINE (15, 120)-(25, 120)' botom of leg
 LINE (25, 120)-(25, 100)'right side of leg
 LINE (30, 100)-(30, 120)' other leg
 LINE (30, 120)-(40, 120)' part of leg
 LINE (40, 120)-(40, 100)'part of leg
 CIRCLE (40, 60), 12
 CIRCLE (30, 80), 15
 CIRCLE (30, 80), 10
 PAINT (30, 80)
'heavy weaponry
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
GET (145, 200)-(155, 140), arrow
'animation starter
 GET (10, 120)-(60, 50), GUY
FOR i = 1 TO 100 STEP 5
 PUT (i, 50), GUY
CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
 PUT (i + 5, 50), GUY
FOR j = 1 TO c
NEXT j
NEXT i
IF INKEY$ = " " THEN 300
GOTO 500
'his attack
300 CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
 PUT (100, 50), GUY
 FOR a = 1 TO 1000
 NEXT a
 CIRCLE (100, 100), 2
 FOR cd = 1 TO 1000 * speed
 NEXT cd
 CIRCLE (105, 105), 4
 FOR D = 1 TO 1000 * speed
 NEXT D
 CIRCLE (105, 110), 10
 FOR e = 1 TO 1000 * speed
NEXT e
 CIRCLE (110, 120), 20
FOR f = 1 TO 1000 * speed
NEXT f
 CIRCLE (110, 125), 40
 CLS
 COLOR 4, 4
PRINT
PRINT
PRINT
PRINT
PRINT "            Bloody Murder"
FOR g = 1 TO 20000
NEXT g: KEY OFF
 PRINT
 PRINT
 PRINT
 PRINT "         You are dead!!!"
 PRINT "      play again Y or N "
 DO: a$ = INKEY$
 LOOP UNTIL a$ = "Y" OR a$ = "y" OR a$ = "N" OR a$ = "n"
 IF a$ = "Y" THEN
        GOTO begin
 ELSEIF a$ = "y" THEN
        GOTO begin
 ELSE
 PRINT "Press Space"
 DO: LOOP UNTIL INKEY$ = " "
 END
 END IF
500 CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
'continuos movement
FOR i = 100 TO 150 STEP 5
 PUT (i, 50), GUY
CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
 PUT (i + 5, 50), GUY
FOR j = 1 TO c
NEXT j
NEXT i
IF INKEY$ = " " THEN 700
KEY OFF
 FOR n = 150 TO 250 STEP 5
 PUT (n, 50), GUY
CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
 PUT (n + 5, 50), GUY
FOR x = 1 TO c
NEXT x
NEXT n
 GOTO 1000
700 GOTO 2000
1000 CLS
 LINE (100, 150)-(200, 150)
 LINE (100, 150)-(80, 200)
 LINE (200, 150)-(230, 200)
 LINE (120, 200)-(130, 180)
 LINE (130, 180)-(130, 200)
 LINE (190, 200)-(190, 180)
 LINE (190, 180)-(200, 200)
 LINE (150, 190)-(150, 140)
 LINE (145, 140)-(155, 140)
 PUT (200, 50), GUY
 FOR a = 1 TO 1000 * speed
 NEXT a
 CIRCLE (200, 100), 2
 FOR cd = 1 TO 1000 * speed
 NEXT cd
 CIRCLE (205, 105), 4
 FOR D = 1 TO 1000 * speed
 NEXT D
 CIRCLE (205, 110), 10
FOR e = 1 TO 1000 * speed
NEXT e
 CIRCLE (210, 120), 20
FOR f = 1 TO 1000 * speed
NEXT f
 CIRCLE (210, 125), 40
 CLS
 COLOR 4, 4
PRINT
PRINT
PRINT
PRINT
PRINT "            Bloody Murder"
FOR g = 1 TO 20000
NEXT g: KEY OFF
 PRINT
 PRINT
 PRINT
 PRINT "         You are dead!!!"
 PRINT "      play again Y or N "
 DO: a$ = INKEY$
 LOOP UNTIL a$ = "Y" OR a$ = "y" OR a$ = "N" OR a$ = "n"
 IF a$ = "Y" THEN
        GOTO begin
 ELSEIF a$ = "y" THEN
        GOTO begin
 ELSE
 PRINT "Press Space"
 DO: LOOP UNTIL INKEY$ = " "
 END
 END IF
2000 LINE (150, 150)-(170, 75)
FOR j = 1 TO 30
COLOR j
FOR bn = 1 TO 100
NEXT bn
NEXT j
PRINT : PRINT : PRINT : PRINT : PRINT : PRINT "         You Dominate"
PRINT "Press Space"
DO: LOOP UNTIL INKEY$ = " "

