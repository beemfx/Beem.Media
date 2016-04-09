'Huckleberry's Adventure v 1.00 by Blaine Myers
'Notes
'Depending on processor speed movespeed may need to be changed.
'There may be unknown bugs.
'This edition is the cheaters edition which allows continuing from
'where the user left off.
'It is common knowledge that there are not icebergs in the Mississippi
'this was put in for humorous effect.
DECLARE SUB ended ()
DECLARE SUB mainmenu ()
DECLARE SUB playgame ()
DECLARE SUB story ()
DECLARE SUB win ()
DECLARE SUB ending ()
DECLARE SUB title ()
DECLARE SUB question ()
DECLARE SUB check ()
DECLARE SUB die ()
DECLARE SUB moving ()
DECLARE SUB paints ()
DECLARE SUB Graphicsload ()
DIM SHARED raft(1000), ans, false, true, x, questions, movespeed
LET movespeed = 2000 'Needs to be modified to work with computer
LET true = 1
LET false = NOT true
title
Graphicsload
mainmenu

SUB check
IF ans = true THEN
        moving
ELSEIF ans = false THEN
        CLS : paints
        die
        CLS : paints
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
FOR j = 1 TO movespeed: NEXT j
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
LOCATE 5, 2: PRINT "Do you wish to continue Y)es or N)o"
LINE (0, 25)-(100, 25), 1
PAINT (25, 13), 1
LINE (53, 25)-(65, 25)
LINE (65, 25)-(60, 30)
LINE (60, 30)-(57, 27)
LINE (57, 27)-(55, 32)
LINE (55, 32)-(53, 25)
PAINT (55, 26), 167, 15
DO
move$ = INKEY$
LOOP UNTIL move$ = "Y" OR move$ = "y" OR move$ = "N" OR move$ = "n"
IF move$ = "Y" OR move$ = "y" THEN
        LET ans = true
        LET questions = questions - 1
ELSEIF move$ = "N" OR move$ = "n" THEN
        mainmenu
END IF
END SUB

SUB ended
CLS
COLOR 15
LOCATE 10, 15: PRINT "GAME OVER"
COLOR 16
END
END SUB

SUB ending
PRINT "Huck has reached his goal; he has"
PRINT "found Jim. His adventure is over for"
PRINT "now...     His adventures down the"
PRINT "Mighty Mississippi will continue in"
PRINT "Huckleberry's Return: Huckleberry's"
PRINT "Adventure Part II."
DO: LOOP UNTIL INKEY$ = " "
mainmenu
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

SUB mainmenu
CLS
COLOR 4
LOCATE 5, 10: PRINT "Main Menu"
COLOR 3
LOCATE 8, 8: PRINT "1. The Game"
LOCATE 10, 8: PRINT "2. The Story"
LOCATE 12, 8: PRINT "3. Quit"
COLOR 15
LOCATE 18, 6: PRINT "Game and Music by Blaine Myers"
LOCATE 19, 6: PRINT "Special Thanks to Craig Decker"
LOCATE 20, 9: PRINT "(Special Hacked Edition)"
 DO
 select$ = INKEY$
 LOOP UNTIL select$ = "1" OR select$ = "2" OR select$ = "3"
COLOR 15
IF select$ = "1" THEN
        playgame
ELSEIF select$ = "2" THEN
        story
ELSEIF select$ = "3" THEN
       COLOR 16
       ended
END IF
COLOR 16
CLS
END SUB

SUB moving
PUT (x, 26), raft
FOR j = 1 TO movespeed: NEXT j
PUT (x, 26), raft
LET x = x + 1
IF x > 75 THEN LET x = 5
END SUB

SUB paints
LINE (0, 25)-(100, 25), 1
PAINT (25, 13), 1
END SUB

SUB playgame
CLS
paints
LET x = 5
LET questions = 1
ans = true
DO
question
moving
check
LOOP
END SUB

SUB question
IF questions = 1 THEN
        LOCATE 3, 1: PRINT "Huck meets Jim on Jacksons Island"
        LOCATE 4, 1: PRINT "T)rue or F)alse"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                CLS : paints
                LET ans = true
                LET questions = 2
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 2
        END IF
ELSEIF questions = 2 THEN
        LOCATE 3, 1: PRINT "Huck is not embarrased to hang out"
        LOCATE 4, 1: PRINT "naked with Jim"
        LOCATE 5, 1: PRINT "T)rue or F)alse"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                CLS : paints
                LET ans = true
                LET questions = 3
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 3
        END IF
ELSEIF questions = 3 THEN
        LOCATE 3, 1: PRINT "When Huck first saw Jim his reaction"
        LOCATE 4, 1: PRINT "was?"
        LOCATE 5, 1: PRINT "A) I need a friend right now."
        LOCATE 6, 1: PRINT "B) I better turn him in."
        LOCATE 7, 1: PRINT "C) I wish I never met him."
        LOCATE 8, 1: PRINT "D) I bet I was glad to see him!"

        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = false
                LET questions = 4
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = false
                LET questions = 4
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = false
                LET questions = 4
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = true
                LET questions = 4
                CLS : paints
        END IF
ELSEIF questions = 4 THEN
        LOCATE 3, 1: PRINT "One way Jim and Huck are alike"
        LOCATE 4, 1: PRINT "A) They are both running from something."
        LOCATE 5, 1: PRINT "B) Their skin is the same color."
        LOCATE 6, 1: PRINT "C) They have the same mother."
        LOCATE 7, 1: PRINT "D) They talk with the same accent."
        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = true
                LET questions = 5
                CLS : paints
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = false
                LET questions = 5
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = false
                LET questions = 5
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = true
                LET questions = 5
                END IF
ELSEIF questions = 5 THEN
        LOCATE 3, 1: PRINT "Jim had no hair on his chest."
        LOCATE 4, 1: PRINT "T)rue or F)alse"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = false
                LET questions = 6
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = true
                LET questions = 6
                CLS : paints
        END IF
ELSEIF questions = 6 THEN
        LOCATE 1, 1: PRINT "Finish this sentence that Huck"
        LOCATE 2, 1: PRINT "says about Jim 'Well, he was"
        LOCATE 3, 1: PRINT "right; he was most always right;"
        LOCATE 4, 1: PRINT "he had...'"
        LOCATE 5, 1: PRINT "A) a good attitude 'bout that."
        LOCATE 6, 1: PRINT "B) them scars; proof enough."
        LOCATE 7, 1: PRINT "C) an uncommon level head for a"
        LOCATE 8, 1: PRINT "Negro."
        LOCATE 9, 1: PRINT "D) a way 'round that."
        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = false
                LET questions = 7
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = false
                LET questions = 7
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = true
                LET questions = 7
                CLS : paints
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = false
                LET questions = 7
        END IF
ELSEIF questions = 7 THEN
        LOCATE 3, 1: PRINT "When Jim finds Pap's body he"
        LOCATE 4, 1: PRINT "immediately tells Huck the"
        LOCATE 5, 1: PRINT "Good/Bad news."
        LOCATE 6, 1: PRINT "T)rue or F)alse"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = false
                LET questions = 8
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = true
                LET questions = 8
                CLS : paints
        END IF
ELSEIF questions = 8 THEN
        LOCATE 3, 1: PRINT "Huck believes that helping a Negro is"
        LOCATE 4, 1: PRINT "A) Bad luck."
        LOCATE 5, 1: PRINT "B) A step into everlasting fire."
        LOCATE 6, 1: PRINT "C) Good Luck."
        LOCATE 7, 1: PRINT "D) The key to everlasting joy."
        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = false
                LET questions = 9
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = true
                LET questions = 9
                CLS : paints
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = false
                LET questions = 9
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = false
                LET questions = 9
        END IF
ELSEIF questions = 9 THEN
        LOCATE 1, 1: PRINT "All of these are Role Model"
        LOCATE 2, 1: PRINT "characteristics, belonging to Jim,"
        LOCATE 3, 1: PRINT "except one."
        LOCATE 4, 1: PRINT "A) He is a strong believer in his"
        LOCATE 5, 1: PRINT "beliefs."
        LOCATE 6, 1: PRINT "B) He is willing to look at opposing"
        LOCATE 7, 1: PRINT "views. "
        LOCATE 8, 1: PRINT "C) He trusts his friends."
        LOCATE 9, 1: PRINT "D) He is willing to risk his freedom for"
        LOCATE 10, 1: PRINT "his friends."
        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = false
                LET questions = 10
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = true
                LET questions = 10
                CLS : paints
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = false
                LET questions = 10
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = false
                LET questions = 10
        END IF
ELSEIF questions = 10 THEN
        LOCATE 3, 1: PRINT "Huck tries to argue two points"
        LOCATE 4, 1: PRINT "to Jim; what are they?"
        LOCATE 5, 1: PRINT "A) Houses; Steamboats"
        LOCATE 6, 1: PRINT "B) Books; Dolphins"
        LOCATE 7, 1: PRINT "C) Soloman; Frenchman"
        LOCATE 8, 1: PRINT "D) Dreams; Fog horns"
        move$ = INKEY$
        IF move$ = "A" OR move$ = "a" THEN
                LET ans = false
                LET questions = 11
        ELSEIF move$ = "B" OR move$ = "b" THEN
                LET ans = false
                LET questions = 11
        ELSEIF move$ = "C" OR move$ = "c" THEN
                LET ans = true
                LET questions = 11
                CLS : paints
        ELSEIF move$ = "D" OR move$ = "d" THEN
                LET ans = false
                LET questions = 11
        END IF
ELSEIF questions = 11 THEN
        LOCATE 3, 1: PRINT "Jim and Huck agree that 'there warn't"
        LOCATE 4, 1: PRINT "no home like a raft, after all.'"
        LOCATE 5, 1: PRINT "T)rue or F)alse"
        move$ = INKEY$
        IF move$ = "T" OR move$ = "t" THEN
                LET ans = true
                LET questions = 12
                CLS : paints
        ELSEIF move$ = "F" OR move$ = "f" THEN
                LET ans = false
                LET questions = 12
        END IF
ELSEIF questions = 12 THEN
win
END
END IF
END SUB

SUB story
CLS
PRINT "Huckleberry has lost his good companion"
PRINT "Jim. It is up to you as his gaurdian"
PRINT "scholar to assist him in his attempt to"
PRINT "rescue Jim. If you fail, Huck's"
PRINT "quest will come to a tragic end."
PRINT
PRINT "But how am I going to help Huck you may"
PRINT "ask. The answer is simple. As Huck sails"
PRINT "down the Mighty Mississippi you will be"
PRINT "asked a series of questions concerning"
PRINT "the relationship between Jim and Huck."
PRINT "Answer them all right and prepare"
PRINT "yourself for the finale!"
PRINT
PRINT "For each question or statement you will"
PRINT "have to choose from two to four answers"
PRINT "press the button on the keyboard"
PRINT "corresponding to the answer you have"
PRINT "chosen."
PRINT : PRINT "Note:The iceberg is mererly comic effect"
PRINT "     not actual content from the book."
PRINT "         (Space to continue)"
DO: LOOP UNTIL INKEY$ = " "
mainmenu
END SUB

SUB title
SCREEN 13
LOCATE 6, 8: PRINT "Huckleberry's Adventure"
PLAY "o2abbcdabcdel2f"
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
FOR j = 1 TO movespeed: NEXT j
PUT (x, 26), raft
NEXT x
PUT (x, 26), raft
ending
END SUB

