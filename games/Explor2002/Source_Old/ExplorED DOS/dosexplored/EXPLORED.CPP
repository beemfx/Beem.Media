/*
	ExplorEd: A DOS Based map editor for explor type maps.
	Copyright(C) 2001, Beem Software

	Author: Blaine Myers
	Start Date January 12, 2001
*/
/*
	Log:

	January 12, 2001
	I've created a GUI and I'm pretty satisfied.  I'm having troubles dealing
	with sprites and moving them from one function to another.  Using the arrow
	keys is really crappy.  If you press a capitol of the corresponding letter
	it reads it as the up arrow.

	My next goal will be to write a program similar to my QBasic Moveen program
	once I have completed that I may continue to develop this one.

	January 13, 2001
	I perfected the location of the placement of the cursor.  Now it needs an
	input consistent with a x, y format. The cursor now moves fine except that
	it leaves behind a lot of funny pixel formations.

	What needs to be done now is design sprites for different tiles and then
	impliment them by placing them on the map when certain buttons are pressed.

	January 14, 2001
	Now if you press 'T' it places a tile sprite on the screen it doesn't it
	will need to activate the fact that there is a tile at that location for
	the save feature.

	I'm facing many issues with the buffered memory.  I've perfected the binary
	writing but now the cursor disapears for an unexplained reason. My goodness
	I think it's working!  I believe open works correctly it just doesn't
	re-display the tileset. It now opens the tileset fine, but the cursor doesn't
	work quite right.

	The file commands are really screwy.  Save seems to work fine. The rest of
	them create visual errors.

	July 21, 2001
	Removed the necessity for the temb.buf file which cleared up a lot of the
	memory issues.

	But still a lot of memory issues remain.  If you only edit the first map
	loaded and then us SaveAs you can make multiple maps.  NewMap and LoadMap
	cause a lot of errors.  Probably need to redo the graphicsloading to fix
	that.  OpenMap will load the screen correctly but after that the cursor
	gets very screwed up.

	<no longer keeping track of dates>

	BoardEdit has been slighly altered for greater effect.  Updated to map
	type 2.  0's instead of 1's.

	Changed tiles to 'D' 's and 'W' 's for Door and Wall correspondingly.
	Improved the algorithm for mapping out the board when initial map load
	happens.  This improved some of the memory issues.

	Fixed a damn good portion of the memory issues.  I'm not even sure if any
	are left.  Have expiramented quite a bit.

	Updated to map type 3 it took a damn bit of a long time but I am so fucking
	satisfied now.  There are a lot of bugs it will take time to fix them. Most
	bugs are fixed.  I know memory issues exist when saving.  Need to make it so
	alternate tile properties may be altered besides 1 and 2.  To do that need
	to make it so you can change the size of fileHeader.mapNumProperty.

	Wrote a new function that takes input.  It is used to take input for property
	and for new map names, as well as save as.  Works pretty damn good.

	Greatly increased the LoadMap function now scrolls down when more than 23
	maps are present.  It supports a maximum number of maps described by a
	definition in openmap.h.

	Preforming a Save causes memory issues.

	One thing to implement.  If escape is pressed while in the LoadMap menu
	the program should return to the previous map, as it was right before the
	LoadMap was called.  Right now it will return to the previous map, but in the
	state it was in when it was last saved.

	I'd also like to implement a screenshot feature.

	Now supports mouse, the mouse doesn't actually do anything yet though.

	October 18, 2001
	I have implemented the EXPLORMAP class which contains all the variables of
	an explor type map, as well as the functions to load an explormap into memory,
	save an explor map on the disk, and edit and explor map.  Mapboard.cpp and
	mapboard.h contain this class and work independently of any other programs.
	Just include #include "mapboard.h" in the file that uses the EXPLORMAP class
   and include the mapboard.cpp as part of the project.

	With this new class it should be much easier to port the code to windows.
	The code in now C++ rather than C language.

	I also separated the source into 3 parts.  One for the defintion of the
	CASTLEMAP class: mapboard.cpp.  Another for the openfile process: openfile.cpp.
	And finally the main program; explored.cpp.

   I also implemented overlaoding functions for the input for easier usage.

*/

/*
	About Explor Map Type 3:

	Explor Maps are read in the following manner:
	The first bytes are the fileheader described by the typedef MAPHEADER.
	Directly after the map data is the tile data.  Each tile is an unsigned int
	which represents the type of tile (see below).  Directly after the tile
	type is the property data.  They are unsigned ints as well.  There may be
	as many properties as you wish per tile.

	Tile types:
		 0: Nothing - Means nothing is there
		10: Wall - Regular wall represented by 'W' on the display
		20: Door - A Door represented by 'D' on the display
	Possible Future Tile tipes:
		xx: Invisible Wall - Wall you cannot see but cannot pass through
		xx: Visible Emptiness - You see a wall but can pass through

	Property values:
		The property values can be incremented by 1 and 2 on the keyboard.
		They have not been assigned to any specific functions yet.  But may
		either in explor source code or ExplorSCRIPT.
*/

/*******************************************************************
The following definitions are to change certain things about the
source.
********************************************************************/
#define SHOWMOUSE
//#define DEBUG

//Included Files
#include <conio.h>
#include <string.h>
#include <ctype.h>

#include "explored.h"
#include "mapboard.h"
#include "openmap.h"
#include "mouse.h"

//Definitions


/* Type Definitions */
typedef unsigned short int BIT;

/* Enumerated Items */
const enum eboard {TILE, PROP};
const enum etile {PUT, ERASE};

/* Global Variables */
static void far *ptr[4];
void far *tile[4];

int xloc = 1, yloc=1;
int firstime = 0;
int firstime1  = 0;
char filename[13];

EXPLORMAP explormap;

int main(int argc, char *argv[])
{
//	char *filename;
	Initialize();
//	if(argv[1] != NULL){
//		filename = argv[1];
//	}else{
		strcpy(filename, "default.map");
//	}
	GetSprite(tile);
	GetCur(ptr);
	LoadDisp();
	PutCur(ptr, xloc, yloc, NULL, NULL);
	OpenMap(filename);

	dtext("ExplorED Started");
	DispTileStats();

	initMouse();
	#ifdef SHOWMOUSE
	initCursor();
	#endif

	while(GetKey() != 1){
	DispTileStats();
	}
	closegraph();
	return 0;
}

/*
	int takeInput(char theoutput[80], char type[]);
	writes input out to the screen and copies it to char array defined by
	theoutput.  Type must be specified as "INT" or "STRING"
	If the type is "INT" the function returns and unsigned short int.

	Valid characters that can be entered:
		for "STRING" a-z, A-Z, and '.'
		for "INT" 0-9
*/
unsigned int takeInput(void)
{
	int value;
	int position = 0;
	char bufstring[1];
	char theoutput[80];
	char keystroke;

	setfillstyle(SOLID_FILL, BLACK);
	bar(200, 400, 600, 410);

	do{
		keystroke = getch();

		switch(keystroke)
		{
			case 27:
				return 301;
			case 13:
				position = 80;
				break;
			case 8: //Hitting backspace
				if(position > 0){
					//setfillstyle(SOLID_FILL, WHITE);
					bar(202+(position-1)*8, 400, 202+position*8, 410);
					position--;
					theoutput[position] = NULL;
				}
				break;
			default:
				if(((48<=keystroke)&&(keystroke<=59))){
					sprintf(bufstring, "%c", keystroke);
					theoutput[position] = keystroke;
					outtextxy(202+position*8, 402, bufstring);
					position++;
				}
		}
	}while(position < 80);

	setfillstyle(SOLID_FILL, 6);
	bar(200, 400, 600, 410);
	setfillstyle(SOLID_FILL, BLACK);

	return atoi(theoutput);
}

int takeInput(char theoutput[80])
{
	int keystroke;
	int position = 0;
	char bufstring[1];
	setfillstyle(SOLID_FILL, BLACK);
	bar(200, 400, 600, 410);

		do{
			keystroke = getch();

			switch(keystroke)
			{
				case 27://hitting escape
					return 301;
				case 13://Hitting enter
					position = 80;
					break;
				case 8://Hitting Backspace
					if(position > 0){
						//setfillstyle(SOLID_FILL, WHITE);
						bar(202+(position-1)*8, 400, 202+position*8, 410);
						position--;
						theoutput[position] = NULL;
					}
					break;
				default:
					if(((97<=keystroke)&&(keystroke<=122)) || ((65<=keystroke)&&(keystroke<=90)) || (keystroke==46)){
						sprintf(bufstring, "%c", keystroke);
						theoutput[position] = keystroke;
						outtextxy(202+position*8, 402, bufstring);
						position++;
					}
					break;
			}

		}while(position < 80);

	setfillstyle(SOLID_FILL, 6);
	bar(200, 400, 600, 410);
	setfillstyle(SOLID_FILL, BLACK);
	return 0;
}

/*
int quiting(int c); process for quiting.  returns 1 if program should quit
int c can really be just about anything
*/
int quiting(int c)
{
	dtext("Are you sure you want to quit Y/n");
	while(c != 'Y' || c != 'y' || c != 'n' || c != 'N' || c != 27){
		c = getch();
		if(c == 'Y' || c == 'y' || c == 27){
			dtext("Quiting: Do You want to save Y/n");
			c = getch();
			if (c == 'Y' || c == 'y')
				explormap.saveMap(filename);
			else
				;
			return 1;
		}
		else if(c == 'N' || c == 'n'){
			dtext("");
			break;
		}
	}
}
void putWall(int wswitch)
{
	switch (wswitch){
		case PUT:
			setcolor(BROWN);
			settextstyle(0, 0, 2);
			outtextxy(xloc*25+xloc+6, yloc*20+yloc+5, "W");
			settextstyle(0, 0, 0);
			setcolor(WHITE);
			break;
		case ERASE:
			setcolor(BLACK);
			settextstyle(0, 0, 2);
			outtextxy(xloc*25+xloc+6, yloc*20+yloc+5, "W");
			setcolor(WHITE);
			settextstyle(0, 0, 0);
			break;
		default:
			dtext("Error 511: wsitch not valid");
			break;
	}
}

void putDoor(int dswitch)
{
	switch (dswitch){
		case PUT:
			setcolor(GREEN);
			settextstyle(0, 0, 2);
			outtextxy(xloc*25+xloc+6, yloc*20+yloc+5, "D");
			settextstyle(0, 0, 0);
			setcolor(WHITE);
			break;
		case ERASE:
			setcolor(BLACK);
			settextstyle(0, 0, 2);
			outtextxy(xloc*25+xloc+6, yloc*20+yloc+5, "D");
			setcolor(WHITE);
			settextstyle(0, 0, 0);
			break;
		default:
			dtext("Error 512: dswitch not valid");
			break;
	}
}
void DispTileStats(void)
{
	//Need to change EXPLORMAP class to make these work.

	char whatToDisp[100];
	setfillstyle(SOLID_FILL, BLACK);
	sprintf(whatToDisp, "(T)ile State: %i", explormap.getTileStat(xloc, yloc));
	bar(440, 50, 600, 56);
	outtextxy(440, 50, whatToDisp);
	sprintf(whatToDisp, "Property One: %i", explormap.getTileStat(xloc, yloc, 0));
	bar(440, 60, 600, 66);
	outtextxy(440, 60, whatToDisp);
	sprintf(whatToDisp, "Property Two: %i", explormap.getTileStat(xloc, yloc, 1));
	bar(440, 70, 600, 76);
	outtextxy(440, 70, whatToDisp);
	sprintf(whatToDisp, "X Location: %i", xloc);
	bar(440, 100, 600, 106);
	outtextxy(440, 100, whatToDisp);
	sprintf(whatToDisp, "Y Location: %i", yloc);
	bar(440, 110, 600, 116);
	outtextxy(440, 110, whatToDisp);

}

void SaveMap(char openmap[FNAMELEN])
{
	if (openmap == NULL){
		dtext("Save Map as what:");
		takeInput(openmap);
	}
	strcpy(filename, openmap);
	explormap.saveMap(openmap);
	dtext("Saved");
}

/*
	void dtext(char *string);
	This function outputs a string into the text window.  Returns no value.
*/
void dtext(char *string)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	bar(200, 380, 600, 390);
	setcolor(WHITE);
	outtextxy(202, 382, string);
}
/*
	void NewMap(void);
	This function show clear the current board and replace it with nothing and
	allow the user to rename the current map.  It doesn't work right, yet.
*/
void NewMap(void)
{
	int i;
	int j;
	dtext("Name the new map:");
	takeInput(filename);
	clearviewport();
//	Initialize();
	GetCur(ptr);
//GetSprite(tile);
	LoadDisp();

	explormap.resetBoard();
	xloc = 1; yloc = 1;
	PutCur(ptr, xloc, yloc, NULL, NULL);
	firstime = 0;
}

/*
	void OpenMap(char openmap[13]);
	This function clears the current map
	then either:
		a) if and argument is included: attempts to open the file
		b) runs the LoadMap function
	then displays the new map on the screen.
	Should be programmed later to return a certain value if it failed
	currently returns nothing.
*/
void OpenMap(char openmap[13])
{

	int i;
	int j;
	clearviewport();
	clrscr();
	closegraph();

	if(openmap == NULL){
		LoadMap(filename);
	}else{
		strcpy(filename, openmap);
	}

	Initialize();

	explormap.openMap(filename);

	/* To fix the memory issues all we fucking had to do was re-get the
	images used for the sprites */
	GetCur(ptr); // This Fixed all the memory issues
	//GetSprite(tile);
	LoadDisp();


	//The following code displays what the map looks like in the viewport.
	for(i=1;i<16;i++){
		for(j=1;j<16;j++){
			xloc = j;
			yloc = i;
			switch(explormap.getTileStat(xloc, yloc)){
				case 10:
					putWall(PUT);
					break;
				case 20:
					putDoor(PUT);
					break;
				default:
					break;
			}
		}
	}
	xloc = 1;
	yloc = 1;
//	firstime1 = 0;
	#ifdef SHOWMOUSE
	initCursor();
	#endif
	PutCur(ptr, xloc, yloc, NULL, NULL);
}

/*
	void BoardEdit(int x, int y, int stat);
	this edits the current x, y position on the board according to the value
	of stat given.
*/
void BoardEdit(int x, int y, int stat, unsigned int propedit)
{
//	int tileselect[4] = {0, 10, 20, 30};
	char buffer[80];
	int newpropvalue;

	if(stat == TILE){
		switch(explormap.boardEdit(x, y)){
			case 10:
				putWall(PUT);
				dtext("Wall Placed");
				break;
			case 20:
				putWall(ERASE);	  //Puts door image down
				putDoor(PUT);
				dtext("Wall Erased, Door Placed");
				break;
			case 0:
				putDoor(ERASE);
				dtext("Door Erased");
				break;
			default:
				dtext("Error 201: Tile incorrectly marked, defaulting to zero");
				break;
		}
// Edit Property[propedit]
	}else if(stat == PROP){
		dtext("Enter the property value");
		newpropvalue = takeInput();
		explormap.boardEdit(x, y, propedit, newpropvalue);
	}
}

/*
	void GetSprite(void far *buf1[4]);
	This program gets the sprite for TILE and stores it in memory.
	Needs to be fixed.
*/
void GetSprite(void far *buf1[4])
{
	unsigned size;
	int block1;
	int i;
		size = imagesize(11, 11, 36, 32);
		for(block1=0;block1<=3;block1++){
			if((buf1[block1] = farmalloc(size)) == NULL){
				closegraph();
				printf("Error: not enough heap space in GetSprite %i", i);
				exit(1);
			}
		}
	for(block1=0;block1<=3;block1++){
		setfillstyle(SOLID_FILL, BROWN);
		bar(12, 12, 35, 31);
		for(i=0;i<=5; i++){
			line((12+i*5-1), 12, (12+i*5-1), 31);
		}
		for(i=0; i<=2; i++){
			line(11, 10*i+11, 16, 10*i+11);
			line(21, 10*i+11, 25, 10*i+11);
			line(31, 10*i+11, 35, 10*i+11);
		}
		for(i=0; i<=1; i++){
			line(16, 10*i+16, 21, 10*i+16);
			line(26, 10*i+16, 31, 10*i+16);
		}
		getimage(11, 11, 36, 32, buf1[block1]);
		clearviewport();
	}
}

/*
	void PutSprite(void far *buf1[4], int x, inty);
	This function puts the TILE sprite at the given explormap location
*/
void PutSprite(void far *buf1[4], int x, int y)
{
	int block1;
	if(firstime != 1){
		for(block1=0;block1<=3;block1++){
			putimage(x*25+x+1, (y*20+y), buf1[block1], OR_PUT);
			farfree(buf1[block1]);
		}
		firstime=1;
	}else{
		for(block1=0;block1<=3;block1++){
			putimage(x*25+x+1, (y*20+y), buf1[block1], XOR_PUT);
//         farfree(buf1[block1]);
		}
	}
}

/*
	void PutCur(void far *buf[4], int x, int y, int oldx, int oldy);
	Put the cursor image at the new location as well as clears the old position
	needs some repairing.
*/
void PutCur(void far *buf[4], int x, int y, int oldx, int oldy)
{
	int block;

	if(oldx == NULL && oldy == NULL && firstime1 == 0){
		for (block=0; block<=3; block++) {
			putimage(x*25+x-2, (y*20+y-2), buf[block], OR_PUT);
			farfree(buf[block]);
			firstime1 = 1;
	}
	}else if(oldx == NULL & oldy == NULL){
		for (block=0; block<=3; block++) {
			putimage(x*25+x-2, (y*20+y-2), buf[block], OR_PUT);
			farfree(buf[block]);
		}
	}else{
		for (block=0; block<=3; block++){
			putimage(oldx*25+oldx-2,(oldy*20+oldy-2), buf[block], XOR_PUT);
//			farfree(buf[block]);
		}
		for (block=0; block<=3; block++) {
			putimage(x*25+x-2, (y*20+y-2), buf[block], XOR_PUT);
//			farfree(buf[block]);
		}
	}
}

/*
	void GetCur(void far *buf[4])
	Gets the image used for the cursor and stores it in memory.  Needs some
	fixing.
*/
void GetCur(void far *buf[4])
{
	unsigned size;
	int block;
		size = imagesize(9, 9, 39, 34);
		for(block=0;block<=3;block++){
			if((buf[block] = farmalloc(size)) == NULL){
				closegraph();
				printf("Error: not enough heap space in GetCur %i", block);
				exit(1);
			}
//		setcolor(GREEN);
		rectangle(10, 10, 38, 33);
		rectangle(9, 9, 39, 34);
//		setcolor(WHITE);
		getimage(9, 9, 39, 34, buf[block]);
		}
	setcolor(BLACK);
	rectangle(10, 10, 38, 33);
	rectangle(9, 9, 39, 34);
	setcolor(WHITE);
//	farfree(buf[block]);
	clearviewport();
}

/*
	void LoadDisp(void);
	Loads the constant viewport.
*/
void LoadDisp(void)
{
//	int c;
//	int x;
//	int y;
	int i;
	setcolor(WHITE);
	rectangle(0, 479, 639, 350);
	setfillstyle(SOLID_FILL, 22);
	floodfill(1, 351, WHITE);
	rectangle(2, 364, 637, 352);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(3, 363, WHITE);
	setcolor(BLACK);
	outtextxy(6, 355, "ExplorEd: Copyright 2001, Beem Software by Blaine myers");
	setcolor(RED);
	outtextxy(5, 354, "ExplorEd: Copyright 2001, Beem Software by Blaine Myers");
	setcolor(WHITE);
	outtextxy(5, 370, "(N)ew");
	outtextxy(5, 379, "(O)pen");
	outtextxy(5, 388, "(S)ave");
	outtextxy(5, 397, "Save (A)s");
	outtextxy(5, 406, "P(r)int");
	setcolor(WHITE);
	for(i=1; i<MAPWIDTH+2; i++){
		line(i+25*i, 21, i+25*i, 314+21);
		line(26, i+20*i, 390+26, i+20*i);
	}

}

/*
	int GetKey(void);
	The bulk of the program takes input and acts accordingly.  Returns 0 if
	programs should continue. Or a 1 if program should terminate.
*/







void Initialize()
{
  int xasp, yasp;
  int GraphDriver;
  int GraphMode;
  int ErrorCode;

  GraphDriver = DETECT;                 /* Request auto-detection       */
  initgraph(&GraphDriver,&GraphMode,"");
  ErrorCode = graphresult();            /* Read result of initialization*/
  if( ErrorCode != grOk ){              /* Error occured during init    */
	 printf(" Graphics System Error: %s\n", grapherrormsg(ErrorCode));
	 exit(1);
  }
}

int disableCursor(void)
{
	mregs.x.ax = 2;
	int86(0x33, &mregs, &mregs);
}
int initCursor(void)
{
	mregs.x.ax = 1;
	int86(0x33, &mregs, &mregs);
	return 0;
}
int initMouse(void)
{
	mregs.x.ax = 0;
	int86(0x33, &mregs, &mregs);
	if(!mregs.x.ax)
		return 1;
	return 0;
}




int GetKey(void)
{
	int c;
	while(!kbhit()){
		mregs.x.ax=3;
		int86(0x33, &mregs, &mregs);
		if(mregs.x.bx>0){
			gotoxy(1,1);
//         printf("Button Pressed is %i", mregs.x.bx);
			dtext("Button pressed");
			continue;
		}else{
			//dtext("");
			continue;
		}
	}

	c = getch();
	c = toupper(c);

	switch (c){
		case UP:
			dtext("Up");
			if(yloc > 1){
				yloc--;
				PutCur(ptr, xloc, yloc, xloc, yloc+1);
			}
			break;
		case DOWN:
			dtext("Down");
			if(yloc < 15){
				yloc++;
				PutCur(ptr, xloc, yloc, xloc, yloc-1);
			}
			break;
		case LEFT:
			dtext( "Left");
			if(xloc > 1){
				xloc--;
				PutCur(ptr, xloc, yloc, xloc+1, yloc);
			}
			break;
		case RIGHT:
			dtext( "Right");
			if(xloc < 15){
				xloc++;
				PutCur(ptr, xloc, yloc, xloc-1, yloc);
			}
			break;
		case 'S':
			dtext( "Saving...");
			SaveMap(filename);
			break;
		case 'N':
			dtext( "Generating Map");
			NewMap();
			break;
		case 'O':
			dtext( "Opening");
			OpenMap(NULL);
			break;
		case 'A':
			dtext("Saving As...");
			SaveMap(NULL);
			break;
		case 'R':
			dtext( "Print: Not Implemented");
			break;
		case ('F'):     //Special currently displays filename
			dtext(filename);
			break;
		case '1':
			BoardEdit(xloc, yloc, PROP, 0);
			break;
		case '2':
			BoardEdit(xloc, yloc, PROP, 1);
			break;
		case 27:
//				if(quiting(c) == 1)
			return quiting(c);
			break;
		case 'T':
			BoardEdit(xloc, yloc, TILE, NULL);
			break;
		default:
			dtext( "Command Not Recognized");
			break;
	}
	return 0;
}
