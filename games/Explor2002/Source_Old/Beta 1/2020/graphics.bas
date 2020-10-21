' (c) 2020 Beem Media

'$INCLUDE: 'graphics.bh'

DIM SHARED wall(21), blank(21), black(21)
DIM SHARED faces(25), facen(25), facee(25), facew(25)
DIM SHARED wallx(21), blankx(21)
DIM SHARED facesa(25), facena(25), faceea(25), facewa(25)

SUB GraphicsInit
	SCREEN 13 '320x200 8-bit
	WINDOW SCREEN (0, 0)-(160, 100) ' Not sure why I picked this...
	CLS
	
	CALL GraphicsLoadSprites
END SUB

SUB GraphicsSetDefaultViewport
	WINDOW SCREEN (0, 0)-(160, 100) ' Not sure why I picked this...
END SUB

SUB GraphicsDrawFaceN(x,y)
	PUT (x , y), facen
END SUB

SUB GraphicsDrawFaceE(x,y)
	PUT (x , y), facee
END SUB

SUB GraphicsDrawFaceS(x,y)
	PUT (x , y), faces
END SUB

SUB GraphicsDrawFaceW(x,y)
	PUT (x , y), facew
END SUB

SUB GraphicsDrawFaceNA(x,y)
	PUT (x , y), facena
END SUB

SUB GraphicsDrawFaceEA(x,y)
	PUT (x , y), faceea
END SUB

SUB GraphicsDrawFaceSA(x,y)
	PUT (x , y), facesa
END SUB

SUB GraphicsDrawFaceWA(x,y)
	PUT (x , y), facewa
END SUB

SUB GraphicsDrawWall(x,y)
	PUT (x , y), wall
END SUB

SUB GraphicsDrawBlank(x,y)
	PUT (x , y), blank
END SUB

SUB GraphicsDrawBlack(x,y)
	PUT (x , y), black
END SUB

SUB GraphicsDrawWallX(x,y)
	PUT (x , y), wallx
END SUB

SUB GraphicsDrawBlankX(x,y)
	PUT (x , y), blankx
END SUB


SUB GraphicsLoadSprites

	LINE (1, 1)-(5, 5), 254, BF
	GET (1, 1)-(5, 5), wall
	LINE (1, 1)-(5, 5), 0, BF
	GET (1, 1)-(5, 5), blank


	COLOR 15
	CLS

	LINE (40.5, 42.5)-(44, 42.5), 253
	LINE (40.5, 42.5)-(42, 41), 253
	LINE (40.5, 42.5)-(42, 44), 253
	GET (40, 40)-(44.52, 44.52), facew
	CLS


	LINE (40.5, 42.5)-(44, 42.5), 253
	LINE (44, 42.5)-(42.5, 41), 253
	LINE (44, 42.5)-(42.5, 44), 253
	GET (40, 40)-(44.52, 44.52), facee
	CLS


	LINE (42.5, 40.5)-(42.5, 44), 253
	LINE (42.5, 40.5)-(44, 42), 253
	LINE (42.5, 40.5)-(40.5, 42), 253
	GET (40, 40)-(44.52, 44.52), facen

	CLS

	LINE (42.5, 40.5)-(42.5, 44), 253
	LINE (42.5, 44)-(44, 42), 253
	LINE (42.5, 44)-(40.5, 42), 253
	GET (40, 40)-(44.52, 44.52), faces
	CLS
	LINE (1, 1)-(5, 5), 3, BF
	GET (1, 1)-(5, 5), wallx
	LINE (1, 1)-(5, 5), 0, BF
	GET (1, 1)-(5, 5), blankx
	CLS
	COLOR 15
	CLS

	LINE (40.5, 42.5)-(44, 42.5), 5
	LINE (40.5, 42.5)-(42, 41), 5
	LINE (40.5, 42.5)-(42, 44), 5
	GET (40, 40)-(44.52, 44.52), facewa
	CLS


	LINE (40.5, 42.5)-(44, 42.5), 5
	LINE (44, 42.5)-(42.5, 41), 5
	LINE (44, 42.5)-(42.5, 44), 5
	GET (40, 40)-(44.52, 44.52), faceea
	CLS


	LINE (42.5, 40.5)-(42.5, 44), 5
	LINE (42.5, 40.5)-(44, 42), 5
	LINE (42.5, 40.5)-(40.5, 42), 5
	GET (40, 40)-(44.52, 44.52), facena

	CLS

	LINE (42.5, 40.5)-(42.5, 44), 5
	LINE (42.5, 44)-(44, 42), 5
	LINE (42.5, 44)-(40.5, 42), 5
	GET (40, 40)-(44.52, 44.52), facesa
	CLS
END SUB

