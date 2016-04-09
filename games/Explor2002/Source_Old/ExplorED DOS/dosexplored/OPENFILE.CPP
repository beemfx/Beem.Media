#include "openmap.h"
#include "explored.h"

int LoadMap(char templist[13])
/*
	LoadMap generates a scrolling list of filenames which you can select and
	load.  Changes char array described by templist to the filename returns 0
	if successfully preformed -1 if failed.
*/
{
	char thelist[MAXFLIST][FNAMELEN];
	int i;
	int highcount;
	int lownum=0;
	int selection = 0;
	int button;

	Initialize();
	highcount = GenList(thelist);

	printList(thelist, 0, highcount);
	setcolor(RED);
	outtextxy(1, 35, "--->");

	do{
	setcolor(WHITE);
	button = getch();
	switch(button){
		case UP:
			if(selection > lownum){
				if(selection != 0){
					selection--;
					setcolor(RED);
					outtextxy(1, 35+16*(selection-lownum), "--->");
					setcolor(BLACK);
					outtextxy(1, 35+16*((selection+1)-lownum), "--->");
					setcolor(WHITE);
				}
			}else{
				if(selection > 0){
					lownum--;
					printList(thelist,lownum, highcount);
					selection--;
				}
			}
			break;
		case DOWN:
			if(selection < (lownum+MAXTODISP-1)){
				if(selection != (highcount-1)){
					selection++;
					setcolor(RED);
					outtextxy(1, 35+16*(selection-lownum), "--->");
					setcolor(BLACK);
					outtextxy(1, 35+16*((selection-1)-lownum), "--->");
					setcolor(WHITE);
				}
			}else{
				if(selection < highcount-1){
					lownum++;
					printList(thelist,lownum, highcount);
					selection++;
				}
			}
			break;
		case 27:
			return -1;
			break;
		case 13:
			clrscr();
			strcpy(templist, thelist[selection]);
			closegraph();
			return 0;
			break;
		default:
			;
	}
	}while(1);
	return 0;
}


int printList(char listtoprint[MAXFLIST][FNAMELEN], int startposition, int maximum)
/*
	Prints a list of length MAXTODISP on the screen.  The list it prints must
	come from a multiple dimensional string array each string no more than 13
	characters in length.  Prints starting from teh startposition in the array.
*/
{
	int looping;

	gotoxy(1, 1);
	printf("Directory Listing of *.map");
	for(looping = 0; looping < MAXTODISP; looping++){
		if(looping == maximum){
			return 1;
		}
		gotoxy(5, looping+3);
		printf("File #%d: %s             ", startposition+1, listtoprint[startposition]);
		startposition++;
	}
	return 0;
}

int GenList(char templist[MAXFLIST][FNAMELEN])
/*
	Generates a list of files and copies them to the array labeld by templist
	it then returns the number of files.
*/
{
	struct find_t files;
	int numfiles;
	int i;
	char filelist[MAXFLIST][13];

	_dos_findfirst("*.map",_A_NORMAL,&files);
	numfiles = 0;
	do{
		strcpy(filelist[numfiles], files.name);
		numfiles++;
	}
	while (_dos_findnext(&files) == 0);

	for (i=0; i<numfiles; i++){
		strcpy(templist[i], filelist[i]);
	}

	return numfiles;
}