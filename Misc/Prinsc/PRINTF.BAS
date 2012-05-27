'This program is just about the most coolest small thing I have made
'I just happened to be looking at the game nibbles and I saw the LEFT$ and
'the RIGHT$ function after looking at what it could do I realized that I
'could make a program that just prints the text out on the screen
'This program can be used in any screen mode
'I recomend that you use this as a sub directory and follow this example
'when you want to use it
'
'b$ = "Whatever you want"   this sets the value for the text
'overest = 6: downest = 5   this sets the LOCATE function
'prinsc                     this will run the SUB
'
'
'The sub directory should look like this
'
'SUB prinsc
'lens = LEN(b$)
'FOR printes = 1 to lens
'LOCATE downest, overest: PRINT LEFT$(b$, printes)
'FOR j = 1 to 1000: NEXT j
'NEXT printes
'END SUB
'
'for this to work you have to make the SUB called prinsc
'you can call the SUB whatever you  want but you will need to
'create one that way in whatever program you make you can use it very
'easily.  Note the overest and downest are used for the LOCATE function
'the b$ is used for the PRINT function.
'that example is bad joes copter 2 uses it more effectively.
'In joes copter 2 it looks like this
'DECLARE printes(downest, overest, b$)
'printes(x, y, "the message")
'where x is characters over and y is characters down
'the sub should look like this
'SUB printes(overest, downest, b$)
'lens = len(b$)
'for printao = 1 to lens
'LOCATE downest, overest: PRINT LEFT$(b$, printao)
'FOR j=1 to 1000: NEXT j
'NEXT printao
'END SUB

CLS
COLOR 15
downest = 5: overest = 6
b$ = "This is an example of scrolling print."
lens = LEN(b$)
FOR printao = 1 TO lens
LOCATE downest, overest: PRINT LEFT$(b$, printao)
FOR j = 1 TO 20000: NEXT j

NEXT printao

