@echo off
set PATH=C:\QB45;%PATH%
echo Compiling graphics.bas
bc /o graphics.bas graphics.obj ;
echo Compling walls.bas
bc /o walls.bas walls.obj ;
bc /o walls2.bas walls2.obj ;
echo Compling main.bas
bc /o main.bas main.obj ;
link /nod main.obj walls2.obj graphics.obj, EXPLOR.exe, EXPLOR.map, C:\qb45\lib\bcom45.lib
