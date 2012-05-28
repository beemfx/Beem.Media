DECLARE SUB software ()
DECLARE SUB title ()
DECLARE SUB view1 ()
DECLARE SUB story ()
DECLARE SUB credits ()
DECLARE SUB instructions ()
DECLARE SUB mainmenu ()
'ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
'บ                                                                 บ
'บ                  E.X.P.L.O.R (tm)                               บ
'บ                                                                 บ
'บ                         A New World                             บ       
'บ (Non-Commercial Development Releas Data, no game here)          บ
'บ                                      v. BETA 0.04               บ
'บ                                                                 บ
'บ           Copywrite(C) 2001, Beem Software by Blaine Myers      บ
'บ                                                                 บ
'ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
'This is what I have saved from the original Beta release of explor.
'To find the beta release look in the zip file oldver.  That code is
'so obsolete and lousy you really shouldn't look at it.  Beta 2 is
'much more better.  I've kept the software, title, mainmenu, functions,
'and story because they may still be usefull.  I'll probably use bitmaps
'for this but until then I'm keeping these around.

SCREEN 13
WINDOW SCREEN (0, 0)-(160, 100)
dir$ = "c:\mydocu~1\programs\explor\"
software
title
mainmenu

SUB credits
CLS
COLOR 89: PRINT "PROGRAMMING"
COLOR 89: PRINT : PRINT "Lead Programmer"
COLOR 15: PRINT "Blaine Myers"
COLOR 89: PRINT "Assistant Programmers"
COLOR 15: PRINT "Hirobi Shicoby"
PRINT "Atasha Yensuki"
PRINT "Joe Gillis (Joface)"
PRINT "Hakeem Alajuan"
PRINT "The Grey Cat"
PRINT "U.C.L.A. Team Red"
COLOR 89: PRINT "Backup Team"
COLOR 15: PRINT "Bond, James Bond"
PRINT "Alec Guiness"
PRINT "John Cassidy Parker"
PRINT "and The Blue Baby"
COLOR 89: PRINT : PRINT "ARTWORK"
PRINT : PRINT "Lead Artist"
COLOR 15: PRINT "Blaine Myers"
COLOR 89: PRINT "3D Art Director"
COLOR 15: PRINT "Blaine Myers"
SLEEP 10
CLS
COLOR 89: PRINT "ACTORS"
COLOR 15: PRINT "Jean Luc Picard.....Star of the Game"
PRINT "James Bond..........The Planet"
PRINT "Luke Skywalker......The Holy One"
PRINT "Bill Clinton........Leader of the Pack"
PRINT "Queen Elizabeth.....Enslaved Woman"
PRINT "Tom Cruise..........Friendly Spy"
PRINT "Power Rangers.......Super Friends"
PRINT "The Beatles.........Concert Stars"
PRINT "Blaine Myers........The One"
PRINT "Leonardo DiCaprio...The Corps Lev. 2"
PRINT "John................Unknown"
COLOR 89: PRINT : PRINT "STUNT MEN"
COLOR 15: PRINT "Brandon (Shorty) Bellows"
PRINT "David Ninja"
PRINT "Crazy Lou"
PRINT "B the Bomb"
SLEEP 10
CLS
COLOR 89: PRINT : PRINT "SPECIAL THANKS TO"
COLOR 15: PRINT "Hacksoft"
PRINT "LaPeste"
PRINT "Star Trek"
PRINT "Star Fox"
PRINT "Star Wars"
PRINT "StarGate"
PRINT "Star 102.7"
PRINT "and Any other Stars"
PRINT "T.T.G. Tattle Tail Gargoyle"
PRINT "Travis the Green"
PRINT "(Blade) Michael Sharp"
PRINT "Jon Van Caneghem"
COLOR 89: PRINT : PRINT "NOT SO SPECIAL THANKS TO"
COLOR 15: PRINT "Adam Kay"
COLOR 89: PRINT : PRINT "SUPER SPECIAL THANKS TO"
COLOR 15: PRINT "Craig Decker"
PRINT "For Getting Me Started"
SLEEP 10
CLS
mainmenu

END SUB

SUB instructions
 CLS
SCREEN 13

WINDOW (1, 1)-(100, 100)
DIM uparrow(100), downarrow(100), leftarrow(100), rightarrow(100)
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (52.5, 50.5)-(52.5, 54.2), 0
LINE (52.5, 54.2)-(54.5, 52), 0
LINE (52.5, 54.2)-(50.5, 52), 0
GET (50, 50)-(55, 55), uparrow
 CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (52.5, 50.5)-(52.5, 54.2), 0
LINE (52.5, 50.5)-(50.5, 53), 0
LINE (52.5, 50.5)-(54.5, 53), 0
GET (50, 50)-(55, 55), downarrow
 CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (50.5, 52.5)-(54.5, 52.5), 0
LINE (54.5, 52.5)-(52, 50.5), 0
LINE (54.5, 52.5)-(52, 54.5), 0
GET (50, 50)-(55, 55), rightarrow
CLS
LINE (50, 50)-(55, 55), 8, B
LINE (50.2, 50.2)-(54.8, 54.8), 89, BF
LINE (50.5, 52.5)-(54.5, 52.5), 0
LINE (50.5, 52.5)-(53, 54.5), 0
LINE (50.5, 52.5)-(53, 50.5), 0
GET (50, 50)-(55, 55), leftarrow
CLS
COLOR 2: LOCATE 1, 14: PRINT "INSTRUCTIONS"
COLOR 5: LOCATE 3, 1: PRINT "To control your character use the UP"
PRINT "and DOWN arrows to move forward and"
PRINT "backward to turn left or right us the"
PRINT "LEFT and RIGHT arrows."
PUT (5, 60), uparrow
PUT (5, 52), downarrow
PUT (5, 44), rightarrow
PUT (5, 36), leftarrow
COLOR 11: LOCATE 10, 6: PRINT "MOVE FORWARD"
LOCATE 12, 6: PRINT "MOVE BACKWARD"
LOCATE 14, 6: PRINT "TURN RIGHT"
LOCATE 16, 6: PRINT "TURN LEFT"
LOCATE 18, 1
COLOR 15: PRINT "As you explor the 3D world you will find"
PRINT "many mysterious and wondrous things."
PRINT : PRINT "            (press space)"
DO: LOOP UNTIL INKEY$ = " "
mainmenu

END SUB

SUB mainmenu
CLS
COLOR 40
LOCATE 5, 15: PRINT "Main Menu"
COLOR 45
LOCATE 9, 10: PRINT "1. The Game"
LOCATE 11, 10: PRINT "2. The Story"
LOCATE 13, 10: PRINT "3. Instructions"
LOCATE 15, 10: PRINT "4. Credits"
LOCATE 17, 10: PRINT "5. Quit"
COLOR 15: LOCATE 22, 30: PRINT "v 0.04b"
DO
 move$ = INKEY$
LOOP UNTIL move$ = "1" OR move$ = "2" OR move$ = "3" OR move$ = "4" OR move$ = "5"
IF move$ = "1" THEN
              view1
              DO: LOOP UNTIL INKEY$ = CHR$(27)
              mainmenu
ELSEIF move$ = "2" THEN
             story
ELSEIF move$ = "3" THEN
              instructions
ELSEIF move$ = "4" THEN
             credits

ELSEIF move$ = "5" THEN
              'gameover
 
END IF

END SUB

SUB software
LOCATE 10, 9: PRINT "Beem Software Presents"
SLEEP 2
END SUB

SUB story
CLS
SCREEN 13
WINDOW (0, 0)-(100, 100)
LINE (0, 30)-(100, 30)
LINE (40, 60)-(50, 40), 1, BF
LINE (45, 40)-(45, 55), 0
LINE (40, 40)-(38, 38), 220
LINE (38, 38)-(52, 38), 220
LINE (52, 38)-(50, 40), 220
LINE (50, 40)-(40, 40), 220
PAINT (50, 39), 220
LINE (45, 38)-(45, 40), 0
LINE (50, 60)-(40, 75), 4, BF
LINE (40, 75)-(35, 70), 4, BF
LINE (50, 75)-(55, 70), 4, BF
CIRCLE (45, 80), 4, 6
PAINT (45, 80), 6
LINE (35, 70)-(33, 60), 6
LINE (33, 60)-(30, 60), 6
LINE (30, 60)-(35, 75), 6
LINE (35, 75)-(35, 70), 6
PAINT (31, 61), 6
LINE (55, 70)-(58, 60), 6
LINE (58, 60)-(60, 60), 6
LINE (60, 60)-(55, 75), 6
LINE (55, 70)-(55, 75), 6
PAINT (56, 71), 6
LINE (44, 78)-(46, 78), 0
LINE (43, 81)-(43, 82), 0
LINE (47, 81)-(47, 82), 0
LINE (45, 80)-(45, 81), 0
LINE (41, 86)-(49, 84), 230, BF
LINE (41, 86)-(42, 81), 230, BF
LINE (48.5, 86)-(49.5, 81), 230, BF
LOCATE 19, 1: PRINT "You work for the E.X.P.L.O.R. an elite "
LOCATE 20, 1: PRINT "group of explorers sent out to find"
LOCATE 21, 1: PRINT "strange new planets and civilizations."
LOCATE 22, 1: PRINT "You are now on board the Starship "
LOCATE 23, 1: PRINT "Enterprize, where you are in command."
DO: LOOP UNTIL INKEY$ = " "


LOCATE 19, 1: PRINT "You lived your life as Captain of the "
LOCATE 20, 1: PRINT "Starship Enterprize when suddenly you"
LOCATE 21, 1: PRINT "were beamed off the Ship and ended     "
LOCATE 22, 1: PRINT "up on a strange Planet Where no one"
LOCATE 23, 1: PRINT "is in sight. To bad for you.          "

FOR li = 30 TO 70
LINE (li + 1, 31)-(li + 2, 90), 14, BF
LINE (li, 90)-(li + 1, 31), 0, BF
FOR time.delay = 1 TO 10000: NEXT time.delay
NEXT li
LINE (71, 31)-(72, 90), 0, BF
DO: LOOP UNTIL INKEY$ = " "
LINE (71, 90)-(72, 31), 0, BF
CIRCLE (50, 70), 10, 1
PAINT (50, 70), 1
LINE (35, 70)-(42, 65), 14
LINE (42, 65)-(44, 60), 14
LINE (44, 60)-(65, 75), 14
LINE (65, 75)-(35, 70), 14
PAINT (50, 70), 14
LINE (0, 30)-(100, 0), 0, BF

LOCATE 20, 1: PRINT "   E.X.P.L.O.R.: TRANSMISSION COMPLETE"
LOCATE 22, 15: PRINT "(Press Space)"
DO: LOOP UNTIL INKEY$ = " "
mainmenu

END SUB

SUB title
WINDOW (0, 0)-(300, 300)
CLS
LINE (50, 225)-(250, 75), 1, BF
LINE (50, 225)-(250, 75), 2, B
LINE (60, 215)-(240, 85), 15, BF
LINE (60, 215)-(240, 85), 7, B
LINE (70, 190)-(75, 130), 38, BF
LINE (75, 190)-(90, 185), 38, BF
LINE (75, 160)-(90, 165), 38, BF
LINE (75, 130)-(90, 135), 38, BF
LINE (95, 190)-(120, 130), 38
LINE (120, 130)-(125, 130), 38
LINE (125, 130)-(100, 190), 38
LINE (100, 190)-(95, 190), 38
PAINT (98, 188), 38
LINE (95, 130)-(120, 190), 38
LINE (120, 190)-(125, 190), 38
LINE (125, 190)-(100, 130), 38
LINE (100, 130)-(95, 130), 38
PAINT (98, 132), 38
PAINT (124, 188), 38
LINE (130, 190)-(135, 130), 38, BF
CIRCLE (135, 176), 10, 38, 4.5, 2
PAINT (140, 176), 38
LINE (150, 190)-(155, 130), 38, BF
LINE (155, 135)-(170, 130), 38, BF
CIRCLE (190, 160), 20, 38
CIRCLE (190, 160), 15, 38
PAINT (171, 160), 38
LINE (215, 190)-(220, 130), 38, BF
CIRCLE (220, 175), 12, 38, 4.5, 2
PAINT (221, 175), 38
LINE (220, 160)-(235, 130), 38
LINE (235, 130)-(230, 130), 38
LINE (230, 130)-(215, 160), 38
PAINT (232, 131), 38
LOCATE 17, 15: COLOR 40: PRINT "A New World"
DO: LOOP UNTIL INKEY$ = " "

END SUB

SUB view1
CLS
LET con = 4.52
LINE (0, 0)-(22 * con, 22 * con), 15, B
LINE (23 * con, 1)-(160, 100), 15, B
LINE ((23 * con) + 1, 2)-(159, 35), 15, B
COLOR 14: LOCATE 2, 28: PRINT "E.X.P.L.O.R."
END SUB

