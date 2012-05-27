'This is a neat little Program to solve the Quadratic equation
'You know that tough eqution in geometry that everybody hates
'I made it you use it any questions
'B.M. Software Produced
COLOR 4: CLS : PRINT "This Program Solves the Roots of the Quadratic Equation"
 PRINT "By B.M. Software"
 PRINT
COLOR 1: PRINT "A*X*X + B*X + C = 0"
 PRINT
COLOR 2: INPUT "Enter the Value of A"; A
COLOR 3: INPUT "Enter the Value of B"; b
COLOR 9: INPUT "Enter the Value of C"; c
 PRINT : PRINT
COLOR 5: PRINT "The Roots of the Equation Are:"
 PRINT
disc = b * b - 4 * A * c
IF disc = 0 THEN 490
 IF disc <= 0 THEN 580

 X1 = (-b + SQR(disc)) / (2 * A)
 X2 = (-b - SQR(disc)) / (2 * A)
COLOR 6: PRINT "X1 = "; X1
COLOR 6: PRINT "X2 = "; X2
PRINT "Real, Distinct Roots"
GOTO 650
490  ' REAL EQUAL ROOTS
 X1 = -b / (2 * A)
 X2 = X1
COLOR 6: PRINT "X1 = "; X1
COLOR 6: PRINT "X2 = "; X2
 PRINT "Real, Equal Roots"
 GOTO 650
580 'COMPLEX ROOTS
 X.REAL = -b / (2 * A)
 X.IMAG = SQR(-disc) / (2 * A)
COLOR 6: PRINT "X1 = "; X.REAL; "+ "; X.IMAG; "I"
COLOR 6: PRINT "X2 = "; X.REAL; "- "; X.IMAG; "I"
 PRINT "Complex Roots"
650 END

