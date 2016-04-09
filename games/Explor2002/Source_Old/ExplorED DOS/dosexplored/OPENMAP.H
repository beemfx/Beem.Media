/*
	OpenMap.h: Process for opening a Map.  This version was designed for
	ExplorED.  The program will return the name of the chosen map.
*/
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

#define UP 0 + 'H'
#define DOWN 0 + 'P'
#define MAXFLIST 255    //How many file names can be displayed
#define MAXTODISP 23

int GenList(char templist[MAXFLIST][13]);
int LoadMap(char templist[13]);
int printList(char listtoprint[MAXFLIST][13], int startposition, int maximum);


