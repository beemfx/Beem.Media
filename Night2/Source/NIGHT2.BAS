'============================================================================
'===        this program was designed because I was bored                 ===
'===    developed by B.M. software           1998                         ===
'===      This is a dumb little program that took me about 10 min. to make===
'===      coming next from my software company is joes Copter a neat      ===
'===        little program where you fly a helecopter(At least I call it ===
'===    that),  I wrote this program before I knew much about qbasic      ===
'=== and I am typing these remarks after I wrote this program             ===
'===  I Do not like making lots of good artwork because it takes too much ===
'=== time so I just stick to stick figures they only take five lines and  ===
'=== a circle but theres sounds too and I didn't waste times with the mus ===
'===ic i just typed in random notes  and the end part that says           ===
'=== night killers 2 it was the best title i came up with because I was   ===
'=== not thinking much about it (originally the end title was STARCRAFT 2)===
'===    I think that                                                      ===
'===  Maybe later I turn this into an intro for a game that I make        ===
'============================================================================
CLS : SCREEN 1
FOR j = 1 TO 1: NEXT j
PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT
PRINT "          B.M. Software Presents"
FOR j = 1 TO 50000: NEXT j: CLS
DIM tony(160)
WINDOW (0, 0)-(100, 100): LINE (1, 75)-(100, 75): LINE (10, 95)-(10, 95)
CIRCLE (1, 100), 10: CIRCLE (2, 90), 1: CIRCLE (3, 100), 2: CIRCLE (4, 95), 1
CIRCLE (7, 98), 1.3: LINE (75, 50)-(75, 45): LINE (75, 45)-(74, 40)
LINE (75, 45)-(76, 40): LINE (75, 50)-(74, 47): LINE (75, 50)-(76, 47)
CIRCLE (75, 53), 2: PAINT (75, 53), 5: GET (70, 40)-(80, 60), tony
PUT (25, 42), tony: FOR j = 1 TO 1000: NEXT j: LINE (30, 50)-(40, 50)
LINE (40, 50)-(40, 48): LINE (40, 48)-(30, 48): LINE (30, 48)-(30, 50)
DIM bullet(160): FOR i% = 440 TO 1000 STEP 5: SOUND i%, i% / 1000
NEXT i%: CIRCLE (39, 50), 3: PAINT (39, 51), 5: BEEP
PRINT : PRINT : PRINT : PRINT "                   I'll See You In "
GET (39, 47)-(41, 51), bullet: FOR x = 39 TO 73: PUT (x, 47), bullet
PUT (x + 1, 47), bullet: FOR j = 1 TO 500: NEXT j: NEXT x: PUT (70, 40), tony
PUT (73, 47), bullet: PRINT : PRINT "                      ahhhh...."
PRINT "                                                                      /"
FOR b = 1 TO 25: CIRCLE (74, 50), b: COLOR b: FOR c = 1 TO 500: NEXT c
NEXT b: CLS : CIRCLE (7, 98), 1.3: CIRCLE (2, 90), 1: CIRCLE (3, 100), 2
CIRCLE (4, 95), 1: CIRCLE (1, 100), 10: LINE (1, 75)-(100, 75)
COLOR 0: PUT (25, 42), tony: LINE (30, 50)-(40, 48): LINE (40, 48)-(40, 46)
LINE (40, 46)-(30, 48): LINE (30, 45)-(30, 48): DIM gun(160)
GET (31, 45)-(40, 50), gun: FOR ja = 45 TO 60: PUT (31, ja), gun
PUT (31, ja + 1), gun: FOR be = 1 TO 1000: NEXT be: NEXT ja: CLS
CIRCLE (2, 90), 1: CIRCLE (3, 100), 2: CIRCLE (4, 95), 1: CIRCLE (7, 98), 1.3
CIRCLE (1, 100), 10: LINE (1, 75)-(100, 75): PUT (31, ja), gun: PUT (25, 42), tony
FOR la = 25 TO 80: PUT (la, 42), tony: PUT (la + 1, 42), tony
FOR h = 1 TO 1000: NEXT h: NEXT la: PLAY "t200o1gggl1el4fffl1G"
FOR j = 1 TO 1000: NEXT j: CLS : COLOR 1
PRINT : PRINT : PRINT : PRINT : PRINT : PRINT
PRINT "             Night Killers ": LINE (30, 70)-(30, 80): DIM st(160)
GET (30, 69)-(31, 81), st: FOR jo = 30 TO 65: PUT (jo, 69), st
LINE (40, 90)-(60, 80): LINE (60, 80)-(40, 60):
LINE (40, 60)-(60, 60)
PUT (jo + 1, 69), st: FOR u = 1 TO 500: NEXT u: NEXT jo: COLOR 7
LINE (25, 50)-(40, 10): LINE (40, 10)-(60, 10): LINE (60, 10)-(70, 50)
LINE (25, 50)-(30, 55): LINE (30, 55)-(65, 55): LINE (65, 55)-(70, 50)
CIRCLE (40, 40), 5: CIRCLE (56, 40), 5: PAINT (40, 40), 12: PAINT (56, 40), 12

