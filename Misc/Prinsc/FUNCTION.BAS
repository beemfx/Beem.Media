DECLARE SUB prinsc (b$, overest, downest)
CLS
SCREEN 13
COLOR 4
prinsc "Joe is the most coolest", 10, 11

SUB prinsc (b$, downest, overest)
lens = LEN(b$)
FOR printes = 1 TO lens
LOCATE downest, overest: PRINT LEFT$(b$, printes)
FOR j = 1 TO 1000: NEXT j
NEXT printes

END SUB

