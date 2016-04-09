SCREEN 13
dcolor = 138
DIM SHARED door2(950), door3(950), door1(2500), door4(950), door5(650)
DIM SHARED door6(650), door7(650), door8(150), door9(325), door10(150)
DIM SHARED door11(300), door12(150)
'Row One
'door1
        CLS
        LINE (1, 1)-(25, 25)
        LINE (1, 1)-(1, 150)
        LINE (25, 25)-(25, 125)
        LINE (25, 125)-(1, 150)
        PAINT (2, 5), dcolor, 15
        LINE (1, 47)-(25, 58)
        LINE (1, 101)-(25, 91)
        GET (1, 1)-(25, 150), door2
  
'door2
        CLS
        LINE (1, 25)-(25, 1)
        LINE (1, 25)-(1, 125)
        LINE (25, 1)-(25, 150)
        LINE (25, 150)-(1, 125)
        PAINT (5, 50), dcolor, 15
        LINE (25, 101)-(1, 91)
        LINE (25, 47)-(1, 58)
        GET (1, 1)-(25, 150), door3
        CLS


'Row In Front
        CLS
'        door1
        LINE (1, 1)-(100, 100), 15, B
        PAINT (5, 5), dcolor, 15
        LINE (1, 33)-(100, 33)
        LINE (1, 66)-(100, 66)
        LINE (50, 1)-(50, 33)
        LINE (50, 66)-(50, 100)
        GET (1, 1)-(100, 100), door1
        CLS
'PUT (1, 1), door2
'PUT (26, 25), door1
'PUT (126, 1), door3

        CLS
'        door4
        LINE (1, 1)-(25, 100), 15, B
        PAINT (5, 5), dcolor, 15
        LINE (1, 33)-(25, 33)
        LINE (1, 66)-(25, 66)
        GET (1, 1)-(25, 100), door4
        CLS
'PUT (1, 25), door4
'PUT (26, 25), door1
'PUT (126, 25), door4

'       door5
        LINE (1, 1)-(1, 100)
        LINE (1, 1)-(25, 25)
        LINE (25, 25)-(25, 75)
        LINE (1, 100)-(25, 75)
        PAINT (2, 5), dcolor, 15
        LINE (1, 33)-(25, 42)
        LINE (1, 66)-(25, 58)
        LINE (17, 17)-(17, 39)
        LINE (17, 61)-(17, 83)
        GET (1, 1)-(25, 100), door5
        CLS
'PUT (1, 25), door4
'PUT (26, 25), door5
'PUT (126, 25), door4

'       door6
        LINE (1, 25)-(25, 1)
        LINE (1, 25)-(1, 75)
        LINE (1, 75)-(25, 100)
        LINE (25, 100)-(25, 1)
        PAINT (5, 50), dcolor, 15
        LINE (1, 42)-(25, 33)
        LINE (1, 58)-(25, 66)
        LINE (8, 18)-(8, 39)
        LINE (8, 61)-(8, 82)
        GET (1, 1)-(25, 100), door6
'CLS
'PUT (1, 1), door2
'PUT (126, 1), door3
'PUT (26, 25), door5
'PUT (101, 25), door6

'2nd Row Back
'       door7
        CLS
        LINE (1, 1)-(50, 50), 15, B
        PAINT (2, 2), dcolor, 15
        LINE (1, 17)-(50, 17)
        LINE (1, 34)-(50, 34)
        LINE (25, 1)-(25, 17)
        LINE (25, 34)-(25, 50)
        GET (1, 1)-(50, 50), door7
CLS
'PUT (51, 50), door7
'PUT (1, 50), door7
'PUT (101, 50), door7

'       door8
        LINE (1, 1)-(12, 12)
        LINE (1, 1)-(1, 50)
        LINE (1, 50)-(12, 37)
        LINE (12, 38)-(12, 12)
        PAINT (2, 5), dcolor, 15
        LINE (1, 16)-(12, 20)
        LINE (1, 34)-(12, 28)
        LINE (8, 9)-(8, 19)
        LINE (8, 30)-(8, 41)
        GET (1, 1)-(12, 50), door8
'CLS
'PUT (1, 1), door2
'PUT (26, 25), door5
'PUT (25, 25), door9
'PUT (51, 50), door8

'       door9
        CLS
        LINE (1, 1)-(25, 50), 15, B
        PAINT (2, 2), dcolor, 15
        LINE (1, 17)-(25, 17)
        LINE (1, 34)-(25, 34)
        GET (1, 1)-(25, 50), door9
'CLS
'PUT (1, 1), door2
'PUT (26, 50), door9
'PUT (51, 50), door8

'       door10
        CLS
        LINE (12, 1)-(1, 12)
        LINE (1, 12)-(1, 38)
        LINE (1, 38)-(12, 50)
        LINE (12, 50)-(12, 1)
        PAINT (10, 5), dcolor, 15
        LINE (1, 20)-(12, 16)
        LINE (1, 28)-(12, 34)
        GET (1, 1)-(12, 50), door10
'CLS
'PUT (1, 1), door2
'PUT (26, 50), door9
'PUT (51, 50), door8
'PUT (101, 50), door7
'PUT (89, 50), door10

'       door11
        CLS
        LINE (1, 1)-(25, 25), 15, B
        PAINT (2, 2), dcolor, 15
        LINE (1, 8)-(25, 8)
        LINE (1, 17)-(25, 17)
        LINE (13, 1)-(13, 8)
        LINE (13, 17)-(13, 25)
        GET (1, 1)-(25, 25), door11

'CLS
'PUT (1, 1), door2
'PUT (26, 25), door5
'PUT (51, 50), door8
'PUT (63, 62), door11
'PUT (89, 50), door10

'       door12
        CLS
        LINE (1, 1)-(12, 25), 15, B
        PAINT (2, 2), dcolor, 15
        LINE (1, 17)-(12, 17)
        LINE (1, 8)-(12, 8)
        GET (1, 1)-(12, 25), door12
CLS
PUT (63, 62), door11
'PUT (89, 62), door11
'PUT (115, 62), door11
'PUT (140, 62), door12
'PUT (1, 62), door12
'PUT (13, 62), door11
'PUT (38, 62), door11

