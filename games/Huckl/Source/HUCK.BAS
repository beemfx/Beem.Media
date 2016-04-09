DECLARE SUB win ()
DECLARE SUB ending ()
DECLARE SUB title ()
DECLARE SUB question ()
DECLARE SUB check ()
DECLARE SUB die ()
DECLARE SUB moving ()
DECLARE SUB paints ()
DECLARE SUB Graphicsload ()
DIM SHARED raft(1000), ans, false, true, x, questions
LET true = 1
LET false = NOT true
title
Graphicsload
paints
LET x = 5
LET questions = 1
ans = true
DO
question
moving
check
LOOP

SUB check
IF ans = true THEN
        moving
ELSEIF ans = false THEN
        die
END IF
END SUB

SUB die
LINE (53, 25)-(65, 25)
LINE (65, 25)-(60, 30)
LINE (60, 30)-(57, 27)
LINE (57, 27)-(55, 32)
LINE (55, 32)-(53, 25)
PAINT (55, 26), 167, 15
FOR x = 5 TO 40 STEP 1
PUT (x, 26), raft
FOR j = 1 TO 2000: NEXT j
PUT (x, 26), raft
NEXT x
LINE (48, 25)-(53, 30)
LINE (53, 30)-(50, 30)
LINE (50, 30)-(46, 25)
LINE (46, 25)-(48, 25)
CIRCLE (43, 25), 2
PAINT (43, 25), 6, 15
PAINT (47, 26), 5, 15
LINE (40, 25)-(35, 30)
LINE (35, 30)-(33, 30)
LINE (33, 30)-(37, 25)
LINE (37, 25)-(40, 25)
PAINT (38, 26), 5, 15
SLEEP 1
CLS
LOCATE 3, 4
PRINT "Huck has hit an Iceberg and drowned"
LOCATE 4, 6
PRINT "He is reminded of the Titanic"
LINE (0, 25)-(100, 25), 1
PAINT (25, 13), 1
LINE (53, 25)-(65, 25)
LINE (65, 25)-(60, 30)
LINE (60, 30)-(57, 27)
LINE (57, 27)-(55, 32)
LINE (55, 32)-(53, 25)
PAINT (55, 26), 167, 15

END
END SUB

SUB ending
PRINT "You have reached your goal; you have"
PRINT "found Jim. Your adventure is over for"
PRINT "now...     Your adventures down the"
PRINT "Mighty Mississippi will continue in"
PRINT "Huckleberry's Return: Hucks adventure"
PRINT "Part II."
END SUB

SUB Graphicsload
SCREEN 13
WINDOW (0, 0)-(100, 100)
LINE (50, 50)-(60, 50)
CIRCLE (60, 51.5), 1
LINE (50, 53)-(60, 53)
CIRCLE (50, 51.5), 1, 15, 2, 5
PAINT (52, 51), 231, 15
LINE (53, 53)-(53, 70)
LINE (57, 53)-(55, 55)
LINE (55, 55)-(55, 60)
CIRCLE (55, 65), 3, 15, 4.7, 1.3, 2.3
CIRCLE (54, 72), 2
PAINT (54, 64), 5, 15
PAINT (54, 72), 6, 15
GET (47, 50)-(63, 75), raft
CLS
END SUB

SUB moving
PUT (x, 26), raft
FOR j = 1 TO 2000: NEXT j
PUT (x, 26), raft
LET x = x + 1
IF x > 75 THEN LET x = 5
END SUB

SUB paints
LINE (0, 25)-(100, 25), 1
PAINT (25, 13), 1
END SUB

SUB question
IF questions = 1 THEN
        LOCATE 3, 4: PRINT "Huck meets Jim on Jacksons Island "
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = true
                LET questions = 2
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 2
        END IF
ELSEIF questions = 2 THEN
        LOCATE 3, 4: PRINT "Huck and Jim hang out Naked        "
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = true
                LET questions = 3
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 3
        END IF
ELSEIF questions = 3 THEN
        LOCATE 3, 4: PRINT "Huck was not glad to see Jim        "
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = false
                LET questions = 4
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = true
                LET questions = 4
        END IF
ELSEIF questions = 4 THEN
        LOCATE 3, 4: PRINT "Why are Huck and Jim alike           "
        LOCATE 4, 4: PRINT "T for they are both running from     "
        LOCATE 5, 4: PRINT "something"
        LOCATE 6, 4: PRINT "F for they both like M&M vii"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = true
                LET questions = 5
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 5
        END IF
ELSEIF questions = 5 THEN
        LOCATE 3, 4: PRINT "Jim had no hair on his chest      "
        LOCATE 4, 4: PRINT "                                  "
        LOCATE 5, 4: PRINT "                                  "
        LOCATE 6, 4: PRINT "                                  "
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = false
                LET questions = 6
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = true
                LET questions = 6
        END IF

ELSEIF questions = 6 THEN
win
END
END IF
END SUB

SUB title
SCREEN 13
LOCATE 6, 8: PRINT "Huckleberry's Adventure"
SLEEP 3
CLS
END SUB

SUB win
LET x = 1
CLS
LINE (80, 26)-(100, 26), 232
LINE (100, 26)-(100, 31), 232
LINE (100, 31)-(90, 31), 232
LINE (90, 31)-(85, 27), 232
LINE (85, 27)-(80, 26), 232
PAINT (90, 27), 232
LINE (90, 32)-(95, 32)
LINE (95, 32)-(95, 52)
LINE (90, 32)-(92, 35)
LINE (92, 35)-(92, 51)
LINE (92, 39)-(95, 39)
LINE (92, 42)-(95, 42)
PAINT (93, 40), 3, 15
PAINT (93, 33), 237, 15
CIRCLE (93, 53), 2
PAINT (93, 53), 237, 15
PAINT (93, 47), 237, 15
FOR x = 1 TO 68 STEP 1
LINE (0, 25)-(100, 25), 1
PAINT (25, 13), 1
PUT (x, 26), raft
FOR j = 1 TO 2000: NEXT j
PUT (x, 26), raft
NEXT x
PUT (x, 26), raft
ending
END SUB

