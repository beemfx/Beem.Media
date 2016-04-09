' ====================================================================
' =       This program is used to blow away thine enemy              =
' =    This is version 3.0 wich allows you to name your enemy        =
' =    No newer versions of this game are planned to be made         =
' =      Constructed and Created by B.M. SOFTWARE                    =
' =         Executive producer Blaine Myers                          =
' =          Special thanks to  Michael Sharp                        =
' =                       Just have fun     Press Space to Kill      =
' =  I have no Idea why I call it v 3.0 becaus it should probally    =
' =  be called v 1.03 but its 3.0 this is the first game I made with =
' =  real animation.                                                 =
' ====================================================================
'
'1.04 Now Released guy moves across entire screen now

 DIM ex(160)
 CLS
 KEY OFF
 SCREEN 1
 PRINT "Please enter speed '1' for 75Mhz"
 INPUT "20 for 450Mhz:", speed
 PRINT
 INPUT "Name thine enemy:", A$
177 CLS
 LINE (190, 199)-(160, 150)
 LINE (300, 199)-(200, 150)
 LINE (160, 150)-(200, 150)
  LINE (160, 150)-(160, 170)
 LINE (160, 170)-(170, 199)
   '      guy
 LINE (150, 99)-(150, 110)
 LINE (150, 110)-(160, 120)
 LINE (150, 110)-(140, 120)
 LINE (150, 99)-(160, 110)
 LINE (150, 99)-(140, 110)
 r1 = 6
 CIRCLE (150, 95), r1
 PAINT (150, 95), 4, 4
 GET (140, 90)-(160, 140), ex
 PUT (140, 90), ex
 PUT (1, 90), ex
 FOR i = 1 TO 200 STEP 5
 PUT (i, 90), ex
 PUT (i + 5, 90), ex
 FOR j = 1 TO 1000 * speed
 NEXT j
 NEXT i
 DO UNTIL INKEY$ = " "
 IF INKEY$ = CHR$(27) THEN END
 GOTO 177
 LOOP
 CLS
 KEY OFF
 LINE (190, 199)-(160, 150)
 LINE (300, 199)-(200, 150)
 LINE (160, 150)-(200, 150)
 LINE (160, 150)-(160, 170)
 LINE (160, 170)-(170, 199)
 '      guy
 LINE (150, 99)-(150, 110)
 LINE (150, 110)-(160, 120)
 LINE (150, 110)-(140, 120)
 LINE (150, 99)-(160, 110)
 LINE (150, 99)-(140, 110)
 CIRCLE (150, 95), r1
 PAINT (150, 95), 4, 4
 LINE (190, 150)-(150, 99)
 BEEP
 FOR wait1 = 1 TO 10000 * speed
 NEXT wait1
 LINE (160, 95)-(170, 95)
 CLS
 LINE (190, 199)-(160, 150)
 LINE (300, 199)-(200, 150)
 LINE (160, 150)-(200, 150)
 LINE (160, 150)-(160, 170)
 LINE (160, 170)-(170, 199)
 LINE (130, 99)-(170, 99)
 LOCATE 5, 5: PRINT "You Blew "; A$; " Away"
LOCATE 7, 10: PRINT "Press Space"
DO: LOOP UNTIL INKEY$ = " "

