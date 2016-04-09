CLS

DIM a1 AS INTEGER, a2 AS INTEGER, a3 AS INTEGER, b1 AS INTEGER, b2 AS INTEGER, b3 AS INTEGER, c1 AS INTEGER, c2 AS INTEGER, c3 AS INTEGER
LET try = 0
1 LOCATE 1, 1: PRINT try

 LET a1 = (RND * 8) + 1

2 LET a2 = (RND * 8) + 1
IF a2 = a1 THEN 2

3 LET a3 = (RND * 8) + 1
IF a3 = a2 OR a3 = a1 THEN 3

4 LET b1 = (RND * 8) + 1
IF b1 = a1 OR b1 = a2 OR b1 = a3 THEN 4

5 LET b2 = (RND * 8) + 1
IF b2 = b1 OR b2 = a1 OR b2 = a3 OR b2 = a2 THEN 5

6 LET b3 = (RND * 8) + 1
IF b3 = b2 OR b3 = b1 OR b3 = c3 OR b3 = c2 OR b3 = c1 OR b3 = a3 OR b3 = a2 OR b3 = a1 THEN 6

7 LET c1 = (RND * 8) + 1
IF c1 = a1 OR c1 = a2 OR c1 = a3 OR c1 = b1 OR c1 = b2 OR c1 = b3 THEN 7

8 LET c2 = (RND * 8) + 1
IF c2 = a1 OR c2 = a2 OR c2 = a3 OR c2 = b1 OR c2 = b2 OR c2 = b3 OR c2 = c1 THEN 8
9 LET c3 = (RND * 8) + 1
IF c3 = a1 OR c3 = a2 OR c3 = a3 OR c3 = b1 OR c3 = b2 OR c3 = b3 OR c3 = c1 OR c3 = c2 THEN 9

LET try = try + 1
LET ex = a1 + a2 + a3
IF b1 + b2 + b3 = ex AND c1 + c2 + c3 = ex AND a1 + b1 + c1 = ex AND a2 + b2 + c2 = ex AND a3 + b3 + c3 = ex AND a1 + b2 + c3 = ex AND a3 + b2 + c1 = ex THEN 1000

LOCATE 2, 3: PRINT a1, a2, a3
LOCATE 3, 3: PRINT b1, b2, b3
LOCATE 4, 3: PRINT c1, c2, c3

GOTO 1


1000
LOCATE 2, 3: PRINT a1, a2, a3
LOCATE 3, 3: PRINT b1, b2, b3
LOCATE 4, 3: PRINT c1, c2, c3

