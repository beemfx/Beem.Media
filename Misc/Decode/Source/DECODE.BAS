'No Clue Who this was originally written by but I know that it was written
'For  a macintosh, anyway I converted it to Qbasic and added some colors and
'my own special other stuff anyway it is really great to use if you want
'to give this to a friend and send messages or just to code the name of the
'girl you like go on and do it
'Programer unknown.  Transfered to qbasic code by B.M. Software
CLS
COLOR 15: PRINT "     ATTENTION:PLEASE TURN CAPS LOCK ON"
11 COLOR 1: PRINT " YOUR MESSAGE ";
COLOR 2: INPUT A$
b$ = "": FOR T = LEN(A$) TO 1 STEP -1
V = ASC(MID$(A$, T, 1))
IF V < 65 OR V > 90 THEN 72
V = V - 64: V = 26 - V: V = V + 64
72 b$ = b$ + CHR$(V): NEXT T
COLOR 3: PRINT "HIT SPACE BAR TO CODE IT"
DO: LOOP UNTIL INKEY$ = " "
COLOR 4: PRINT " THE MESSAGE IS: ";
COLOR 5: PRINT b$
COLOR 6: PRINT "ENCODE DECODE ANOUTHER Y/n";
COLOR 7: INPUT redo$
IF redo$ = "Y" OR redo$ = "y" THEN 11
END

