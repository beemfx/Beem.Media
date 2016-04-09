/* Included Files */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//#include "graph.h"
#include <graphics.h>
#include <alloc.h>

/* Definitions */
#define UP 0 + 'H'
#define DOWN 0 + 'P'
#define LEFT 0 + 'K'
#define RIGHT 0 + 'M'

#define MAPWIDTH 15
#define FNAMELEN 13

/* Function Declarations */
void GetSprite(void far *buf1[4]);
void PutSprite(void far *buf1[4], int x, int y);
void BoardEdit(int x, int y, int stat, unsigned int propedit);
void OpenMap(char openmap[13]);
void NewMap(void);
void dtext(char *string);
void SaveMap(char openmap[13]);
int GetKey(void);
void GetCur(void far *buf[4]);
void PutCur(void far *buf[4], int x, int y, int oldx, int oldy);
void LoadDisp(void);
void DispTileStats(void);
void putDoor(int dswitch);
void putWall(int wswitch);
int quiting(int c);
int takeInput(char theoutput[80]);
unsigned int takeInput(void);
void Initialize();
