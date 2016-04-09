DIM SHARED wall1(1300), wall2(1350), wall3(4400), wall5(1000)
DIM SHARED wall6(1100), wall7(1100), wall8(600), wall9(600), wall10(1300)
DIM SHARED wall11(400), wall12(400), wall13(300), wall14(200), wall15(200)
DIM SHARED direction, n, s, e, w, charac$, m$, x, y, oldx, oldy, maxx, maxy
DIM SHARED board$(1000), wall(190), blank(190), black(100), minx, miny
DIM SHARED faces(100), facen(100), facee(100), facew(100), graphic(100)
DIM SHARED xcord, ycord, true, false
DIM SHARED dda, ddb, ddc, ddd, dde, ddf, ddg, ddh, ddi, ddj, ddk, ddl
DIM SHARED ddp, ddq, ddm, ddn, ddo, wallchoice, wallx(190), blankx(190)
DIM SHARED facesa(100), facena(100), faceea(100), facewa(100), autom, dir$
DIM SHARED gbQuit AS INTEGER

const con = 4.52
dir$ = ""

declare SUB wallload()
declare SUB drawwall (wallchoice)
