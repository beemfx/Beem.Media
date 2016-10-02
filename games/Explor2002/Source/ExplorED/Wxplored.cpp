/*
	wxplored.cpp - ExplorED for Windows

	Author: Blaine Myers for Beem Software

	Language: C++ Win32 API

	Version x.xxW
*/
/*
	Note to self:
	Be sure to prompt whether or not to save when quitting.
	Impliment property editing: either shift click or right click.
	Make sure if an invalid map is loaded a, no bug occurs.  Rather
	the utility reports it, and asks to open a new map.
*/


#define NOCHILD

#define MAXFILENAMELEN _MAX_PATH

//#define MAXX 15
//#define MAXY 15
#define MAXX explormap.getMapWidth()
#define MAXY explormap.getMapHeight()
#define EDWNDSIZE 15
#define TWIDTH 40

#include <windows.h>
#include <stdio.h>
//#include <winreg.h>

#include "wxplored.h"
#include "mapboard.h"
#include "resource.h"

#ifndef NOCHILD
char edAppName[]="mainWnd";
char edStatWinName[]="statWnd";
#endif //nochild
char edEditWinName[]="editWnd";
static HWND hEditWnd=NULL;

EXPLORMAP explormap;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	#ifndef NOCHILD
	HWND hMainWnd;
	#endif
	//HWND hStatWnd;
	HACCEL hAccel;

	int errcode;
	TCHAR temperrmessage[100];

	#ifndef NOCHILD
	if(!RegisterWindowClass())return 0;
	#endif
	if(!RegisterEditWindowClass())return 0;
	//if(!RegisterStatusWindowClass())return 0;
	

	//The following code will take the command line perameters

	//MessageBox(NULL, lpszCmdLine, "Notice", MB_OK);

	if(!(strlen(lpszCmdLine)<1)){
		 //errcode=explormap.openMap(lpszCmdLine);
		 strcpy(explormap.boardname, lpszCmdLine);
		 errcode=explormap.openMap(explormap.boardname);
		 if(errcode!=0){
			sprintf(temperrmessage, "Error #%i: Could not open map", errcode);
			MessageBox(NULL, temperrmessage, "Error Opening Map", MB_OK);
			return -1;
		 }
	}else{
		strcpy(explormap.boardname, "default.map");
		errcode=explormap.openMap(explormap.boardname);
		if(errcode!=0){
			sprintf(temperrmessage, "Error #%i: Could not open previously used map", errcode);
			MessageBox(NULL, temperrmessage, "Error Opening Map", MB_OK);
			return -1;
		}
	}

	#ifndef NOCHILD
	hMainWnd=CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_CONTROLPARENT|WS_EX_CONTEXTHELP,
							edAppName,
							"ExplorED",
							WS_DLGFRAME|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX|WS_SIZEBOX|
							WS_MAXIMIZEBOX|WS_THICKFRAME,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							640,//GetSystemMetrics(SM_CXSCREEN),// 540,
							480,//GetSystemMetrics(SM_CYSCREEN)-GetSystemMetrics(SM_CYCAPTION), //520,
							NULL,
							NULL,
							hInstance,
							NULL);
	#endif //nochild
	#ifdef NOCHILD
	hEditWnd=CreateWindow(edEditWinName,
							"ExplorED",
							WS_DLGFRAME|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,//|WS_SIZEBOX|
							//WS_MAXIMIZEBOX|WS_THICKFRAME,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							TWIDTH*EDWNDSIZE+GetSystemMetrics(SM_CXSIZEFRAME)+GetSystemMetrics(SM_CXHSCROLL),
							TWIDTH*EDWNDSIZE+GetSystemMetrics(SM_CYSIZEFRAME)+GetSystemMetrics(SM_CYVSCROLL)+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENUSIZE),
							NULL,
							NULL,
							hInstance,
							NULL);
	#endif //NOCHILD
	#ifndef NOCHILD
	DWORD editStyles=WS_CHILDWINDOW|WS_BORDER|WS_DLGFRAME|WS_SYSMENU|WS_MINIMIZEBOX|WS_VSCROLL|WS_HSCROLL;
	
	hEditWnd=CreateWindowEx(WS_EX_WINDOWEDGE,
							edEditWinName,
							"Edit Window",
							WS_CHILD|editStyles,
							20,
							20,
							TWIDTH*EDWNDSIZE,//+GetSystemMetrics(SM_CXHSCROLL)+GetSystemMetrics(SM_CXSIZEFRAME),
							TWIDTH*EDWNDSIZE,//+GetSystemMetrics(SM_CYVSCROLL)+GetSystemMetrics(SM_CYSIZEFRAME)+GetSystemMetrics(SM_CYCAPTION),
							hMainWnd,
							NULL,
							hInstance,
							NULL);
	#endif //NOCHILD

	//char buf[100];
	//GetClientRect(hEditWnd, &desiredRect);
	//sprintf(buf, "Width: %i\nHeight: %i", desiredRect.right, desiredRect.bottom);
	//MessageBox(NULL, buf, "Note", MB_OK);

	/*hStatWnd=CreateWindowEx(NULL,
							edStatWinName,
							"Status Window",
							WS_BORDER|WS_DLGFRAME|WS_SYSMENU,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							100,
							100,
							hMainWnd,
							NULL,
							hInstance,
							NULL);*/

	#ifndef NOCHILD
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
	#endif
	ShowWindow(hEditWnd, nCmdShow);
	UpdateWindow(hEditWnd);
	//UpdateWindow(hStatWnd);
	//SetFocus(hEditWnd);
	//ShowWindow(hStatWnd, SW_SHOWNORMAL);
	
	//if(!IsChild(hMainWnd, hEditWnd))return 0;//return if child window not successfully created
	hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while(TRUE){
		if(!GetMessage(&msg, NULL, 0, 0)){
			//MessageBox(NULL, "Successfully Quit", "Notice", MB_OK);
			return msg.wParam;
		}
		if(!TranslateAccelerator(msg.hwnd, hAccel, &msg)){
			TranslateMessage(&msg); DispatchMessage(&msg);
		}
	}
}

#ifndef NOCHILD
LRESULT MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	char bufmsg[100];
	switch(uMsg){
		case WM_CREATE:{ 

			sprintf(bufmsg, "ExplorED - [%s]", explormap.boardname);
			SetWindowText(hWnd, bufmsg);break;
			
			}
		case WM_DESTROY:PostQuitMessage(0);break;
		case WM_COMMAND:
			MainCommandProc(hWnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);break;
		case WM_PAINT:
			RECT vWindow;
			GetClientRect(hWnd, &vWindow);
			PAINTSTRUCT ps;
			HDC hDc;
			hDc=BeginPaint(hWnd, &ps);
			FillRect(hDc, &vWindow, HBRUSH(COLOR_APPWORKSPACE+1));
			EndPaint(hWnd, &ps);
			break;
		case WM_SETFOCUS:
			SetFocus(hEditWnd);
			break;
		default: return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0L;
}
#endif //NOCHILD
/*
LRESULT StatWindowProc(HWND hWnd, unsigned msg, WORD wParam, LONG lParam)
{
	HDC hDc;
	PAINTSTRUCT ps;
	char buf[100];
	int i;

	switch(msg)
	{
		case WM_CREATE:break;
		case WM_DESTROY:break;
		case WM_PAINT:{
			hDc=BeginPaint(hWnd, &ps);
			TEXTMETRIC tMetric;
			GetTextMetrics(hDc, &tMetric);
			sprintf(buf, "Tile Type: %i", explormap.getTileStat(1, 1));
			TextOut(hDc, 0, 0, buf, strlen(buf));
			for(i=1; i<=explormap.getNumProperty();i++){
				sprintf(buf, "Property %i: %i", i, explormap.getTileStat(1, 1, i));
				TextOut(hDc, 0, i*tMetric.tmHeight, buf, strlen(buf));
			}
			EndPaint(hWnd, &ps);
			DeleteObject(hDc);
		}
		default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0L;
}
*/
LRESULT EditWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	 POINTS mpoint;
	 RECT vWindow;

	 GetClientRect(hWnd, &vWindow);

	 switch (msg)
	 {
		#ifdef NOCHILD
		case WM_DESTROY:PostQuitMessage(0);break;
		#else
		case WM_DESTROY:break;
		#endif
		case WM_CREATE:
			UpdateScrollBar(hWnd);
			#ifdef NOCHILD
			char bufmsg[1024];
			sprintf(bufmsg, "ExplorED - [%s]", explormap.boardname);
			SetWindowText(hWnd, bufmsg);break;
			#endif //NOCHILD
			break;
		case WM_LBUTTONDOWN:
			//This does not work correctly now
			mpoint=MAKEPOINTS(lParam);
			if(TranslatePoints(hWnd, mpoint)){
				SCROLLINFO si;
				si.cbSize=sizeof(si);
				si.fMask=SIF_ALL;
				GetScrollInfo(hWnd, SB_VERT, &si);
				int vPos=si.nPos;
				GetScrollInfo(hWnd, SB_HORZ, &si);
				int hPos=si.nPos;
				explormap.boardEdit(mpoint.x+hPos, mpoint.y+vPos);
				RedrawWindow(hWnd,NULL,NULL,RDW_INVALIDATE);
			}
			break;
		case WM_PAINT:{
			SCROLLINFO si;
			si.cbSize=sizeof(si);
			si.fMask=SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &si);
			int horzPos=si.nPos;
			GetScrollInfo(hWnd, SB_VERT, &si);
			int vertPos=si.nPos;

			EditWindowPaint(hWnd, horzPos, vertPos);
			break;
		}
		case WM_VSCROLL:{
			//vertical or y position scrolling
			VertScrollManager(hWnd, LOWORD(wParam));
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			}break;
		case WM_HSCROLL:{
			//horizontal or x position scrolling
			HorzScrollManager(hWnd, LOWORD(wParam));
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			}break;
		case WM_COMMAND:
			#ifdef NOCHILD
			MainCommandProc(hWnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);break;
			#endif NOCHILD
		default:return DefWindowProc(hWnd, msg, wParam, lParam);
	 }
	 return 0L;
}
BOOL TranslatePoints(HWND hWnd, POINTS &points){
	
	/*
	for(int i=0;i<EDWNDSIZE;i++){
		if(i*TWIDTH<points.x&&points.x<TWIDTH*(i+1))points.x=i+1;
		if(i*TWIDTH<points.y&&points.y<TWIDTH*(i+1))points.y=i+1;
	}
	*/
	
	/*
	for(int i=0, int j=1;i<EDWNDSIZE*TWIDTH;i+=TWIDTH, j++){
		if((points.x>i)&&(points.x<=i+TWIDTH))points.x=j;
		if((i<points.y)&&(points.y<=i+TWIDTH))points.y=j;
	}
	*/
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	int cxBlock = rect.right/EDWNDSIZE;
	int cyBlock = rect.bottom/EDWNDSIZE;

	int x = points.x/cxBlock;
	int y = points.y/cxBlock;
	points.x=x+1;
	points.y=y+1;

	
	if(points.x>EDWNDSIZE)return FALSE;
	if(points.y>EDWNDSIZE)return FALSE;
	if(points.x<1)return FALSE;
	if(points.y<1)return FALSE;
	return TRUE;
}

BOOL UpdateScrollBar(HWND hWnd){
	SCROLLINFO si;
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	si.nMin=0;
	si.nMax=explormap.getMapWidth()-1;
	si.nPage=EDWNDSIZE;
	si.nPos=0;
	SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
	si.nMax=explormap.getMapHeight()-1;
	SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
	return TRUE;
}

BOOL VertScrollManager(HWND hWnd, WORD nScrollCode)
{
	SCROLLINFO si;
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	GetScrollInfo(hWnd, SB_VERT, &si);

	switch (nScrollCode){ 
		
		case SB_PAGEDOWN:
		case SB_LINEDOWN:
			if(si.nPos<=si.nMax-EDWNDSIZE)si.nPos++;
			break;
		case SB_PAGEUP:
		case SB_LINEUP:
			if(si.nPos>0)si.nPos--;
			break;
		case SB_BOTTOM:
			si.nPos=si.nMax;
			break;
		case SB_TOP:
			si.nPos=0;
			break;
		case SB_THUMBTRACK:
			si.nPos=si.nTrackPos;
			break;
		default:
			break;
	}
	si.fMask=SIF_POS;
	SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
	return TRUE;	
}
BOOL HorzScrollManager(HWND hWnd, WORD nScrollCode)
{
	SCROLLINFO si;
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	GetScrollInfo(hWnd, SB_HORZ, &si);

	switch (nScrollCode){ 
		case SB_PAGERIGHT:
		case SB_LINERIGHT:
			if(si.nPos<=si.nMax-EDWNDSIZE)si.nPos++;
			break;
		case SB_PAGELEFT:
		case SB_LINELEFT:
			if(si.nPos>0)si.nPos--;
			break;
		case SB_RIGHT:
			si.nPos=si.nMax;
			break;
		case SB_LEFT:
			si.nPos=0;
			break;
		case SB_THUMBTRACK:
			si.nPos=si.nTrackPos;
			break;
		default:
			break;
	}

	si.fMask=SIF_POS;
	SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
	return TRUE;	
}

BOOL MainCommandProc(HWND hMainWnd, WORD wCommand, WORD wNotify, HWND hControl)
{
	char tempfilename[_MAX_PATH];
	char buf[100];
	int errvalue;

	switch (wCommand)
	{
		/* The File Menu */
		case CM_FILEEXIT:
			DestroyWindow(hMainWnd);
			return 0;
		case CM_FILENEW:
			return 0;
		case CM_FILESAVE_AS:
			if (GetSaveFileName(hMainWnd, explormap.boardname)==TRUE){
				//sprintf(temp, "Filename was:%s", tempfilename);
				//MessageBox(hMainWnd, temp, "Notice", MB_OK);
				//strcpy(explormap.boardname, tempfilename);
				sprintf(buf, "ExplorED - [%s]", explormap.boardname);
				SetWindowText(hMainWnd, buf);
			}else return 0;
			//Fall through and actually write to disk
		case CM_FILESAVE:
			if((explormap.saveMap(explormap.boardname)==0))
				MessageBox(hMainWnd, "File Saved Successfully", "Notice", MB_OK|MB_ICONINFORMATION);
			return 0;
		case CM_FILEPRINT:
			return 0;
		case CM_FILEOPEN:
			strcpy(tempfilename, explormap.boardname);
			if(GetOpenFileName(hMainWnd, tempfilename)==TRUE){
				//sprintf(temp, "Filename was:%s", tempfilename);
				//MessageBox(hMainWnd, temp, "Notice", MB_OK);
				//strcpy(explormap.boardname, tempfilename);
				if((errvalue=explormap.openMap(tempfilename))==0){
					strcpy(explormap.boardname, tempfilename);
					RedrawWindow(hMainWnd, NULL,NULL, RDW_INVALIDATE);
					sprintf(buf, "ExplorED - [%s]", explormap.boardname);
					SetWindowText(hMainWnd, buf);
				}else{
					//If fails to open map it reopens the previous map
					sprintf(buf, "Error %i: Map was invalid.", errvalue);
					MessageBox(hMainWnd, buf, "Warning Notice", MB_OK|MB_ICONWARNING);
				
					if(explormap.openMap(explormap.boardname)!=0){
					//If the last used map fails we bail out.
						MessageBox(hMainWnd, "Could Not Reopen Current map", 
												"Error Notice", MB_OK|MB_ICONERROR);
						PostQuitMessage(0);
					}
					RedrawWindow(hMainWnd, NULL, NULL, RDW_INVALIDATE);
				}
			}else return 0;
			UpdateScrollBar(GetWindow(hMainWnd, GW_CHILD));
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

void EditWindowPaint(HWND hWnd, int minX, int minY)//, HDC hDc)
{
	int i;
	int j;
	HDC hDc;
	PAINTSTRUCT ps;
	RECT vWindow;
	
	GetClientRect(hWnd, &vWindow);
	
	
	#define NODEFPAINT
	#ifndef NODEFPAINT
		const short blockheight=(vWindow.bottom)/EDWNDSIZE;
		const short blockwidth=(vWindow.right)/EDWNDSIZE;
	#else
		#define blockheight (vWindow.bottom)/EDWNDSIZE
		#define blockwidth (vWindow.right)/EDWNDSIZE
	#endif
	HBITMAP wallbitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(WALL_BITMAP), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
	HBITMAP doorbitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(DOOR_BITMAP), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
	HBITMAP blankbitmap=(HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(BLANK_BITMAP), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

	hDc=BeginPaint(hWnd, &ps);

	//if(USINGXP)FillRect(hDc, &vWindow, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//#define PAINTGRID
	#ifdef PAINTGRID
	HPEN hpen;
	HGDIOBJ hpenOld;
	#define GRIDCOLOR RGB(0,0,0)
	hpen=CreatePen(PS_SOLID,2, GRIDCOLOR);
	hpenOld=SelectObject(hDc, hpen);
	//FillRect(hDc, &vWindow, (HBRUSH)GetStockObject(WHITE_BRUSH));
	//Painting The Grid
	for(i=0; i<=EDWNDSIZE; i++){
		MoveToEx(hDc, i*blockwidth, 0, NULL);
		LineTo(hDc, i*blockwidth, vWindow.bottom);
	}
	for(i=0; i<=EDWNDSIZE;i++){
		MoveToEx(hDc, 0,i*blockheight, NULL);
		LineTo(hDc, vWindow.right, i*blockheight);
	}
	#endif
	
	//Paint the board
	
	for(j=minY;j<=EDWNDSIZE+minY;j++){
		for(i=minX;i<=EDWNDSIZE+minX;i++){

			switch (explormap.getTileStat(i, j))
			{
				case 10:
					DrawState(hDc, NULL, NULL, (LPARAM)wallbitmap, 0, (i-1-minX)*blockwidth, (j-1-minY)*blockheight, 0, 0, DST_BITMAP|DSS_NORMAL); 
					break;
				case 20:
					DrawState(hDc, NULL, NULL, (LPARAM)doorbitmap, 0, (i-1-minX)*blockwidth, (j-1-minY)*blockheight, 0, 0, DST_BITMAP|DSS_NORMAL);
					break;
				default:
					DrawState(hDc, NULL, NULL, (LPARAM)blankbitmap, 0, (i-1-minX)*blockwidth, (j-1-minY)*blockheight, 0, 0, DST_BITMAP|DSS_NORMAL);
					break;
			}
		}
	}
	
	EndPaint(hWnd, &ps);
	#ifdef PAINTGRID
	SelectObject(hDc, hpenOld);
	DeleteObject(hpen);
	#endif
	
	DeleteObject(wallbitmap);
	DeleteObject(doorbitmap);
	DeleteObject(blankbitmap);
}

#ifndef NOCHILD
BOOL RegisterWindowClass(void)
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize=sizeof(WNDCLASSEX);
	wndClass.style=NULL;
	wndClass.lpfnWndProc=(WNDPROC)MainWindowProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=GetModuleHandle(NULL);
	wndClass.hIcon=LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(ICON_1));
	wndClass.hCursor=LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)(COLOR_APPWORKSPACE+1);
	wndClass.lpszMenuName=MAKEINTRESOURCE(MENU_MAIN);
	wndClass.lpszClassName=edAppName;
	wndClass.hIconSm=NULL;
	if(!RegisterClassEx(&wndClass))return FALSE;
	return TRUE;
}
#endif //nochild

BOOL RegisterEditWindowClass(void)
{
	WNDCLASSEX wndClassB;
	ZeroMemory(&wndClassB, sizeof(WNDCLASSEX));

	wndClassB.cbSize=sizeof(WNDCLASSEX);
	#ifdef NOCHILD
	wndClassB.style=NULL;
	#else
	wndClassB.style=CS_HREDRAW|CS_VREDRAW|CS_NOCLOSE;
	#endif
	wndClassB.lpfnWndProc=(WNDPROC)EditWindowProc;
	wndClassB.cbClsExtra=0;
	wndClassB.cbWndExtra=0;
	wndClassB.hInstance=GetModuleHandle(NULL);
	wndClassB.hIcon=LoadIcon(wndClassB.hInstance, MAKEINTRESOURCE(IDI_ICON3));
	wndClassB.hCursor=LoadCursor(NULL, IDC_CROSS);
	wndClassB.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	#ifdef NOCHILD
	wndClassB.lpszMenuName=MAKEINTRESOURCE(MENU_MAIN);
	#else
	wndClassB.lpszMenuName=NULL;
	#endif //nochild
	wndClassB.lpszClassName=edEditWinName;
	wndClassB.hIconSm=NULL;

	if(!RegisterClassEx(&wndClassB))return FALSE;
	return TRUE;
}

/*
BOOL RegisterStatusWindowClass(void)
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize=sizeof(WNDCLASSEX);
	wndClass.style=CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=(WNDPROC)StatWindowProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=GetModuleHandle(NULL);
	wndClass.hIcon=LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_ICON3));
	wndClass.hCursor=LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName=edStatWinName;
	wndClass.hIconSm=NULL;

	if(!RegisterClassEx(&wndClass))return FALSE;
	return TRUE;
}
*/

