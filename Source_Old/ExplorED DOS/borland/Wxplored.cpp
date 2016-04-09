/*
	wxplored.cpp - ExplorED for Windows

	Author: Blaine Myers for Beem Software

	Language: C++ Win32 API

	Version x.xxW
*/
/*
	Note to self:
	Be sure to prompt whether or not to save when quitting.
	Impliment save feature.
	Impliment property editing: either shift click or right click.
	Impliment load feature.
*/
/*
	Log:

	October 30, 2001

	Began Development of ExplorED for Windows, only created a window.

	October 31, 2001

	WinExplorED is really coming along.  The interface works fairly correctly.
	I'm having trouble dealing with file input output so I haven't implimented
	most features yet.

	File input is now working.  I had to specifie certain variables as being
	short rather than defaulting to int.  Now if the program is started
	default.map is loaded.  Or you can used a filname as a command line perameter
	if you do that that map will be loaded.  I have not implimented either
	the ability to save or the ability to load when not loading from the start.

	Developing the win port wasn't nearly as hard as I thought it would be.

	November 7, 2001

   Implemented save and save as feature, both work fine.
*/

/*
	NOTE: The following Log applies to the dos version of ExplorED

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
#define EXIT  exit(0);
//#define EXIT  
#define MAXFILENAMELEN 256

//#define MAXX 15
//#define MAXY 15
#define MAXX explormap.getMapWidth()
#define MAXY explormap.getMapHeight()

#include <windows.h>
#include <stdio.h>

#include "wxplored.h"
#include "mapboard.h"
#include "resource.h"


/*
BOOL RegisterBoardWindowClass(void);
LRESULT MainEditWindowProc(HWND hEditWnd, unsigned msg, WORD wParam, LONG lParam);
*/
char edAppName[]="WExplorED";
//char edEditWinName[]="WExplorEDit";

EXPLORMAP explormap;

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine,
																						 int nCmdShow)
{
	MSG msg;
	HWND hMainWnd;
	HACCEL hAccel;

	int errcode;
	TCHAR temperrmessage[100];
	//HWND hEditWnd;

	if(!hPrevInstance)
		RegisterWindowClass();
	/*
	if(!hPrevInstance)
		RegisterBoardWindowClass();
	*/

	//The following code will take the command line perameters

	//MessageBox(NULL, lpszCmdLine, "Notice", MB_OK);
	if(!(strlen(lpszCmdLine)<1)){
		 //errcode=explormap.openMap(lpszCmdLine);
		 strcpy(explormap.boardname, lpszCmdLine);
		 errcode=explormap.openMap(explormap.boardname);
		 if(errcode!=0){
			sprintf(temperrmessage, "Error #%i: Could not open map", errcode);
			MessageBox(NULL, temperrmessage, "Error Opening Map", MB_OK);
		 }
	}else{
		strcpy(explormap.boardname, "default.map");
		errcode=explormap.openMap(explormap.boardname);
	}

	hMainWnd=CreateWindow(edAppName,
								 "ExplorED For Windows",
								 WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX|
								 WS_CLIPCHILDREN|WS_CLIPSIBLINGS|
								 WS_VSCROLL|WS_HSCROLL|
								 //WS_THICKFRAME|WS_CAPTION|WS_MAXIMIZEBOX, //For resizeable
								 WS_DLGFRAME,                               //For Not resizeable
								 CW_USEDEFAULT,
								 CW_USEDEFAULT,
								 640,
								 480,
								 NULL,
								 NULL,
								 hInstance,
								 NULL);

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
	/*
	hEditWnd=CreateWindow(edEditWinName,
								  "Edit Board:",
								  WS_CHILDWINDOW|WS_SYSMENU|WS_CAPTION|//WS_THICKFRAME|WS_BORDER|
								  WS_DLGFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_VISIBLE,
								  CW_USEDEFAULT,
								  CW_USEDEFAULT,
								  640,
								  480,
								  hMainWnd,
								  NULL,
								  hInstance,
								  NULL);

	ShowWindow(hEditWnd, SW_SHOWNORMAL);
	UpdateWindow(hEditWnd);
	*/

	hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while(GetMessage(&msg, hMainWnd, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccel, &msg)) 
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
/*
LRESULT MainEditWindowProc(HWND hEditWnd, unsigned msg, WORD wParam, LONG lParam)
{
	HDC hDc;

	switch (msg)
	{
		case WM_LBUTTONDOWN:
			MessageBox(hEditWnd, "Pressed Left Mouse Button", "Notice", MB_OK|MB_ICONINFORMATION);
			break;
		case WM_PAINT:
			MainWindowPaint(hEditWnd, hDc);
	}
	return 0;
}
*/
LRESULT MainWindowProc(HWND hMainWnd, unsigned msg, WORD wParam, LONG lParam)
{
	 HDC hDc;
	 POINTS mpoint;
	 RECT vWindow;

	 TCHAR buffermessage[500];
	 int cursor_x, cursor_y;

	 GetClientRect(hMainWnd, &vWindow);

	 switch (msg)
	 {
		case WM_CREATE:
			break;
		case WM_LBUTTONDOWN:
			mpoint=MAKEPOINTS(lParam);
			cursor_x = (mpoint.x/(vWindow.right/MAXX))+1;
			cursor_y = (mpoint.y/(vWindow.bottom/MAXY))+1;
			sprintf(buffermessage, "Mouse x:%i Mouse y:%i Cursor x:%i Cursor y:%i",
										mpoint.x, mpoint.y, cursor_x, cursor_y);
			//MessageBox(hMainWnd, buffermessage, "Notice", MB_OK);
			explormap.boardEdit(cursor_x,cursor_y);
			RedrawWindow(hMainWnd,NULL,NULL,RDW_INVALIDATE);
			return 0;
		case WM_PAINT:
			MainWindowPaint(hMainWnd, hDc);
			return 0;
		case WM_COMMAND:
			MainCommandProc(hMainWnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			EXIT;
			return 0;
	 }
	 return DefWindowProc(hMainWnd, msg, wParam, lParam);
}

BOOL MainCommandProc(HWND hMainWnd, WORD wCommand, WORD wNotify, HWND hControl)
{
	char tempfilename[256]; //Make sure not to keep this arround.
	char temp[500];

	switch (wCommand)
	{
		/* The File Menu */
		case CM_FILEEXIT:
			DestroyWindow(hMainWnd);
			return 0;
		case CM_FILENEW:
			return 0;
		case CM_FILESAVE_AS:
			if (GetSaveFileName(hMainWnd, tempfilename)==TRUE){
				sprintf(temp, "Filename was:%s", tempfilename);
				//MessageBox(hMainWnd, temp, "Notice", MB_OK);
				strcpy(explormap.boardname, tempfilename);
			}else return 0;
		case CM_FILESAVE:
			if((explormap.saveMap(explormap.boardname)==0))
				MessageBox(hMainWnd, "File Save Successfully", "Notice", MB_OK|MB_ICONINFORMATION);
			return 0;
		case CM_FILEPRINT:
			return 0;
		case CM_FILEOPEN:
			if(GetOpenFileName(hMainWnd, tempfilename)==TRUE){
				sprintf(temp, "Filename was:%s", tempfilename);
				MessageBox(hMainWnd, temp, "Notice", MB_OK);
				//explormap.openMap("default.map");
				//RedrawWindow(hMainWnd, NULL,NULL, RDW_INVALIDATE);
			}else return 0;
			return 0;
	}
	return FALSE;
}

int GetSaveFileName(HWND hWnd, char *filename)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "Map Files (*.map)\0*.map\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAXFILENAMELEN;
	ofn.lpstrTitle = "Save Map As...";
	ofn.Flags = OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_NONETWORKBUTTON;

	return GetSaveFileName(&ofn);
}

int GetOpenFileName(HWND hWnd, char *filename)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof( OPENFILENAME );
	ofn.hwndOwner = hWnd; // An invalid hWnd causes non-modality
	ofn.lpstrFilter = "Map Files (*.map)\0*.map\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = filename;  // Stores the result in this variable
	ofn.nMaxFile = MAXFILENAMELEN;
	ofn.lpstrTitle = "Open Map";  // Title for dialog
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

	return GetOpenFileName(&ofn);
}
void MainWindowPaint(HWND hWnd, HDC hDc)
{
	#define GRIDCOLOR RGB(0,0,0)
	#define WALLCOLOR RGB(140,87,15)
	#define DOORCOLOR RGB(84,219,60)
	#define BGCOLOR RGB(255,255,255)

	//I want to remove those defines
	#define blockheight (vWindow.bottom)/MAXY
	#define blockwidth (vWindow.right)/MAXX

	int i;
	int j;

	//int testiles[225];
	//ZeroMemory(testiles, sizeof(testiles));

	TCHAR buffer[100];

	PAINTSTRUCT ps;
	RECT vWindow;
	HPEN hpen;
	HGDIOBJ hpenOld;
	HGDIOBJ hbrushOld;
	HBRUSH wallbrush, doorbrush, blankbrush;

	wallbrush=CreateSolidBrush(WALLCOLOR);
	doorbrush=CreateSolidBrush(DOORCOLOR);
	blankbrush=CreateSolidBrush(BGCOLOR);

	GetClientRect(hWnd, &vWindow);

	hDc=BeginPaint(hWnd, &ps);
	hpen=CreatePen(PS_SOLID,2, GRIDCOLOR);
	hpenOld=SelectObject(hDc, hpen);

	//Painting The Grid
	for(i=0; i<=MAXX; i++){
		MoveToEx(hDc, i*blockwidth, 0, NULL);
		LineTo(hDc, i*blockwidth, vWindow.bottom);
	}
	for(i=0; i<=MAXY;i++){
		MoveToEx(hDc, 0,i*blockheight, NULL);
		LineTo(hDc, vWindow.right, i*blockheight);
	}
	//Paint the board
	for(j=1;j<=MAXY;j++){
		for(i=1;i<=MAXX;i++){

			switch (explormap.getTileStat(i, j))
			{
				case 10:
					hbrushOld=SelectObject(hDc, wallbrush);
					FloodFill(hDc, (i-1)*blockwidth+2, (j-1)*blockheight+2, GRIDCOLOR);
					break;
				case 20:
					hbrushOld=SelectObject(hDc, doorbrush);
					FloodFill(hDc, (i-1)*blockwidth+2, (j-1)*blockheight+2, GRIDCOLOR);
					break;
				default:
					hbrushOld=SelectObject(hDc, blankbrush);
					FloodFill(hDc, (i-1)*blockwidth+2, (j-1)*blockheight+2, GRIDCOLOR);
					break;
			}
			//#define DEBUG2
			#ifdef DEBUG2
			sprintf(buffer, "%i   ", explormap.getTileStat(i, j));
			TextOut(hDc, (i-1)*blockwidth+2, (j-1)*blockheight+2,buffer, strlen(buffer));
			#endif
		}
	}
	EndPaint(hWnd, &ps);
	SelectObject(hDc, hpenOld);
	DeleteObject(hpen);
	SelectObject(hDc, hbrushOld);
	DeleteObject(wallbrush);
	DeleteObject(doorbrush);
	DeleteObject(blankbrush);
}


BOOL RegisterWindowClass(void)
{
	WNDCLASS wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASS));

	wndClass.style=CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=(WNDPROC)MainWindowProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=GetModuleHandle(NULL);
	wndClass.hIcon=LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(ICON_1));
	wndClass.hCursor=LoadCursor(NULL, IDC_CROSS);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=MAKEINTRESOURCE(MENU_MAIN);
	wndClass.lpszClassName=edAppName;
	if(!RegisterClass(&wndClass))
		return FALSE;
	return TRUE;
}
/*
BOOL RegisterBoardWindowClass(void)
{
	WNDCLASS wndClassB;
	ZeroMemory(&wndClassB, sizeof(WNDCLASS));

	wndClassB.style=CS_HREDRAW|CS_VREDRAW;
	wndClassB.lpfnWndProc=(WNDPROC)MainEditWindowProc;
	wndClassB.cbClsExtra=0;
	wndClassB.cbWndExtra=0;
	wndClassB.hInstance=GetModuleHandle(NULL);
	wndClassB.hIcon=LoadIcon(wndClassB.hInstance, MAKEINTRESOURCE(ICON_1));
	wndClassB.hCursor=LoadCursor(NULL, IDC_ARROW);
	wndClassB.hbrBackground=GetStockObject(WHITE_BRUSH);
	wndClassB.lpszMenuName=NULL;
	wndClassB.lpszClassName=edEditWinName;
	if(!RegisterClass(&wndClassB))
		return FALSE;
	return TRUE;
}
*/
