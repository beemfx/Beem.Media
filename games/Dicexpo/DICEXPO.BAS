DECLARE SUB software ()
DECLARE SUB intro ()
DECLARE SUB rules ()
DECLARE SUB diceload ()
DECLARE SUB thegames ()
DECLARE SUB diceroll ()
SCREEN 12
WINDOW (0, 0)-(100, 100)
DIM SHARED dice1 AS INTEGER, dice2 AS INTEGER, cash, bet AS INTEGER
LET bet = 10
LET cash = 100
RANDOMIZE TIMER
    DIM SHARED diceas1(2600)
    DIM SHARED diceas2(2600)
    DIM SHARED diceas3(2600)
    DIM SHARED diceas4(2600)
    DIM SHARED diceas5(2600)
    DIM SHARED diceas6(2600)

software
diceload
intro
thegames

SUB diceload
    CLS
    LINE (20, 35)-(45, 60), 15, B
    PAINT (21, 36), 0, 15
    CIRCLE (33, 48), 2, 15
    PAINT (33, 48), 15
    GET (20, 35)-(45, 60), diceas1
  
    CIRCLE (25, 41), 2, 15
    PAINT (25, 41), 15
    CIRCLE (40, 54), 2, 15
    PAINT (40, 54), 15
    GET (20, 35)-(45, 60), diceas3

    CIRCLE (25, 54), 2, 15
    PAINT (25, 54), 15
    CIRCLE (40, 41), 2, 15
    PAINT (40, 41), 15
    GET (20, 35)-(45, 60), diceas5
    CLS
  
    LINE (20, 35)-(45, 60), 15, B
    CIRCLE (25, 41), 2, 15
    PAINT (25, 41), 15
    CIRCLE (40, 54), 2, 15
    PAINT (40, 54), 15
    GET (20, 35)-(45, 60), diceas2
  
    CIRCLE (25, 54), 2, 15
    PAINT (25, 54), 15
    CIRCLE (40, 41), 2, 15
    PAINT (40, 41), 15
    GET (20, 35)-(45, 60), diceas4

    CIRCLE (25, 47.5), 2, 15
    PAINT (25, 47.5), 15
    CIRCLE (40, 47.5), 2, 15
    PAINT (40, 47.5), 15
    GET (20, 35)-(45, 60), diceas6

END SUB

SUB diceroll
CLS
  
    COLOR 12: LOCATE 15, 30: PRINT "PRESS SPACE"
10
    DO
    LOOP UNTIL INKEY$ = " ": CLS
    LET dice1 = RND * 1 * 7: LET dice2 = RND * 1 * 7
   
    PAINT (1, 1), 3, 15
    LINE (10, 25)-(90, 75), 15, B
    PAINT (11, 26), 2, 15
    COLOR 3: LOCATE 25, 20: PRINT "Your Cash"; cash
    IF dice1 <= 1 THEN LET dice1 = 1
    IF dice2 <= 1 THEN LET dice2 = 1
    IF dice1 >= 6 THEN LET dice1 = 6
    IF dice2 >= 6 THEN LET dice2 = 6
    LINE (20, 35)-(45, 60), 0, BF
    LINE (50, 35)-(75, 60), 0, BF
    IF dice1 = 1 THEN PUT (20, 35), diceas1
    IF dice2 = 1 THEN PUT (50, 35), diceas1
    IF dice1 = 2 THEN PUT (20, 35), diceas2
    IF dice2 = 2 THEN PUT (50, 35), diceas2
    IF dice1 = 3 THEN PUT (20, 35), diceas3
    IF dice2 = 3 THEN PUT (50, 35), diceas3
    IF dice1 = 4 THEN PUT (20, 35), diceas4
    IF dice2 = 4 THEN PUT (50, 35), diceas4
    IF dice1 = 5 THEN PUT (20, 35), diceas5
    IF dice2 = 5 THEN PUT (50, 35), diceas5
    IF dice1 = 6 THEN PUT (20, 35), diceas6
    IF dice2 = 6 THEN PUT (50, 35), diceas6
    IF dice1 = dice2 THEN 20
    LET cash = cash + bet
    GOTO 10
20 LET cash = 10
BEEP
COLOR 4: LOCATE 16, 27: PRINT "LOSER: YOU GOT DOUBLES"
SLEEP 100
thegames
END SUB

SUB intro
CLS
LINE (10, 40)-(10, 80)
CIRCLE (10, 60), 15, 15, 4.7, 1.58
CIRCLE (10, 60), 12, 15, 4.97, 1.32
LINE (13, 44.5)-(13, 75.5)
PAINT (11, 41), 3, 15
LINE (30, 40)-(45, 40)
LINE (30, 40)-(30, 45)
LINE (30, 45)-(35, 45)
LINE (45, 40)-(45, 45)
LINE (45, 45)-(40, 45)
LINE (40, 45)-(40, 75)
LINE (40, 75)-(45, 75)
LINE (45, 75)-(45, 80)
LINE (45, 80)-(30, 80)
LINE (30, 80)-(30, 75)
LINE (30, 75)-(35, 75)
LINE (35, 75)-(35, 45)
PAINT (36, 74), 4, 15
CIRCLE (62, 60), 15, 15
CIRCLE (62, 60), 12, 15
PAINT (49, 60), 5, 15
LINE (69, 10)-(80, 90), 0, BF
LINE (69, 42.4)-(69, 47)
LINE (69, 73)-(69, 77.5)
LINE (75, 40)-(75, 80)
LINE (75, 80)-(90, 80)
LINE (90, 80)-(90, 75)
LINE (90, 75)-(80, 75)
LINE (80, 75)-(80, 63)
LINE (80, 63)-(90, 63)
LINE (90, 63)-(90, 58)
LINE (90, 58)-(80, 58)
LINE (80, 58)-(90, 58)
LINE (80, 58)-(80, 45)
LINE (80, 45)-(90, 45)
LINE (90, 45)-(90, 40)
LINE (90, 40)-(75, 40)
PAINT (76, 41), 9, 15
COLOR 12
DO
COLOR RND * 1 * 15
'E
LINE (40, 20)-(45, 21)
LINE (40, 20)-(41, 15)
LINE (41, 15)-(46, 15)
LINE (46, 15)-(41.5, 14)
LINE (41.5, 14)-(42, 10)
LINE (42, 10)-(46.5, 10)

'X
LINE (48, 10)-(52, 20)
LINE (48.5, 22)-(51.8, 9)
'P
LINE (53, 10)-(54, 21)
LINE (54, 21)-(57, 18)
LINE (57, 18)-(53.9, 16)

'O
LINE (58, 15)-(60, 20)
LINE (60, 20)-(63, 14)
LINE (63, 14)-(59.2, 11)
LINE (59.2, 11)-(58, 15)

'S
LINE (65, 10)-(69, 9)
LINE (69, 9)-(65.3, 15)
LINE (65.3, 15)-(68.6, 20)

'I
LINE (72, 10.5)-(73, 19)
LINE (71, 10)-(73, 11)
LINE (71.5, 20)-(74, 19)

'T
LINE (78, 10)-(77, 21)
LINE (75, 20)-(80, 22)

'I
LINE (82, 9.5)-(83, 20.5)
LINE (81, 10)-(83, 9)
LINE (81.5, 20)-(84, 21)

'O
LINE (85.5, 15)-(87, 20)
LINE (87, 20)-(90, 14)
LINE (90, 14)-(86, 10)
LINE (86, 10)-(85.5, 15)

'N
LINE (91, 11)-(93, 19)
LINE (93, 19)-(95, 15)
LINE (95, 15)-(97, 22)
LOOP UNTIL INKEY$ = " "

END SUB

SUB rules
CLS
COLOR 6: LOCATE 5, 5: PRINT "1) Dice Roll"

COLOR 1: LOCATE 25, 5: PRINT "Select Rules for Game"
DO: game$ = INKEY$
LOOP UNTIL game$ = "1"
IF game$ = "1" THEN
        CLS : PRINT : PRINT "Dice Roll": PRINT
              PRINT "The Rules are: press space to roll the die."
              PRINT "Every time you roll you will win your bet in dollars."
              PRINT "If you roll doubles you lose all your money."
              PRINT "Get it, Got it, Good."
              SLEEP 100
              thegames
              
        END IF

END SUB

SUB software
LOCATE 15, 35: PRINT "B.M. SOFTWARE"
CIRCLE (50, 70), 10, 1
PAINT (50, 70), 1
LINE (35, 70)-(42, 65), 14
LINE (42, 65)-(44, 60), 14
LINE (44, 60)-(65, 75), 14
LINE (65, 75)-(35, 70), 14
PAINT (50, 70), 14
LINE (0, 30)-(100, 0), 0, BF

SLEEP 2
END SUB

SUB thegames

CLS
LET bet = bet
LET cash = cash
IF bet >= cash THEN LET bet = cash
COLOR 1: LOCATE 5, 5: PRINT "1) Dice Roll"
COLOR 13: LOCATE 15, 5: PRINT "Press the number of the game you want or '?' for Rules"
LOCATE 16, 5: PRINT "Hold shift and press < or > to change your bet"
COLOR 14: LOCATE 20, 5: PRINT "Your Cash "; cash
COLOR 14: LOCATE 20, 15: PRINT "$"
COLOR 12: LOCATE 21, 15: PRINT "Your Gamble"
LOCATE 21, 27: PRINT bet
5 : DO: game$ = INKEY$: LOOP UNTIL game$ = "1" OR game$ = "0" OR game$ = "?" OR game$ = "/" OR games$ = "," OR games$ = "." OR game$ = ">" OR game$ = "<" OR game$ = CHR$(27)
IF game$ = "1" THEN diceroll
IF game$ = "0" THEN END
IF game$ = "?" THEN rules
IF game$ = "/" THEN rules
IF game$ = CHR$(27) THEN END
IF game$ = "." OR game$ = ">" THEN
        LET bet = bet + 10
        IF bet >= cash THEN LET bet = cash
        COLOR 12: LOCATE 21, 27: PRINT bet
        GOTO 5
   END IF
 
IF game$ = "," OR game$ = "<" THEN
        LET bet = bet - 10
        IF bet = 0 THEN LET bet = 10
        COLOR 12: LOCATE 21, 27: PRINT bet
        GOTO 5
    END IF
END SUB

