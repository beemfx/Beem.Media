 ' ======================================================================
 ' ===   This is eulers formula B.M. software                        ====
 ' ======================================================================
 CLS
 PRINT : PRINT : PRINT : PRINT "This Program will tell you if an Object is a Polygon"
PRINT
COLOR 1: INPUT "Enter Number of Edges"; e
COLOR 2: INPUT "Enter Number of Vertices"; V
COLOR 3: INPUT "Enter Number of Faces"; f
 disc = f + V - e
 IF disc = 2 THEN 5
 PRINT
COLOR 4: PRINT "This is not a Polygon"
 END

5 COLOR 14: PRINT : PRINT "This is a Polygon"

