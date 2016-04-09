#include <windows.h>
#include <ddraw.h>
#include <stdio.h>

#include "defines.h"
#include "ddsetup.h"
#include "resource.h"
#include "gmapboard.h"
#include "bmp.h"
#include "tiles.h"
#include "tilemgr.h"
#include "player.h"
#include "directmidi.h"

#pragma comment(lib, "../DXLIB/dxguid.lib")
#pragma comment(lib, "../DXLIB/ddraw.lib")

//#define TEST_RENDERING1
#ifdef TEST_RENDERING1
int global_test_number=0;
#endif

//Function Prototype
long CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL LoadImages();
BOOL keyboard_handler(WPARAM keystroke);
void ShutDownDirectDraw();
void ReleaseSurfaces();
BOOL ProcessFrame();
BOOL ComposeFrame();
BOOL PageFlip();
BOOL RestoreSurfaces();
BOOL InitImages();
BOOL GetImages();
BOOL StartLevel(char *mapname, int x, int y, Direction Face, char *musicfile);

//Global variables
HWND g_hwnd;

DWORD g_dwTransparentColor;
int g_nScreenWidth=SCREEN_WIDTH;
int g_nScreenHeight=SCREEN_HEIGHT;
int g_nColorDepth=COLOR_DEPTH;


LPDIRECTDRAW lpDirectDrawObject=NULL;
LPDIRECTDRAWSURFACE lpPrimary=NULL;
LPDIRECTDRAWSURFACE lpSecondary=NULL;
LPDIRECTDRAWSURFACE lpBackground=NULL;
BOOL ActiveApp;

CGameMap g_cGameBoard;
CPlayerObject g_cPlayer(1, 1, NORTH);
CDirectMidi MusicPlayer;

CBitmapReader background;

CBitmapReader defaultImageSet;
CBitmapReader defaultDoorSet;
CTileSet g_cTileSets[NUM_TILE_SETS];

HWND hWnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	hWnd=CreateDefaultWindow("Explor", hInstance);
	if(!hWnd)return FALSE;
	g_hwnd=hWnd;
	ShowWindow(hWnd, nShowCmd);
	SetFocus(hWnd);
	ShowCursor(FALSE);
	BOOL ok=InitDirectDraw(hWnd);
	if(ok)ok=InitImages();
	if(!ok){
		DestroyWindow(hWnd);
		return FALSE;
	}
	
	StartLevel("maps\\default.map", 2, 2, SOUTH, "music\\mmcannon.mid");
	//StartLevel("maps\\tunnel.map", 2, 2, SOUTH, "music\\bl_btear.mid");
	while(TRUE)
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
			if(!GetMessage(&msg, NULL, 0, 0))return msg.wParam;
			TranslateMessage(&msg); DispatchMessage(&msg);

		}
		else if(ActiveApp)ProcessFrame(); else WaitMessage();
	return 0;
}
BOOL StartLevel(char *mapname, int x, int y, Direction Face, char *musicfile){
	g_cGameBoard.openMap(mapname);
	g_cPlayer.SetFace(Face);
	if((x<=g_cGameBoard.getMapWidth()&&x>0)&&((y<=g_cGameBoard.getMapHeight()&&y>0)))
		g_cPlayer.SetLocation(x, y);
	else g_cPlayer.SetLocation(1, 1);
	g_cGameBoard.SetTileType(20, DOOR);
	if(musicfile!=NULL){
		if(GetFileAttributes(musicfile)){
			MusicPlayer.Load(musicfile);
			MusicPlayer.Play();
		}
	}
	return TRUE;
}
/*
void PutText(char* text,LPDIRECTDRAWSURFACE surface){
  HDC hdc;
  if(SUCCEEDED(surface->GetDC(&hdc))){
    RECT rect;
    rect.left=10; rect.right=g_nScreenWidth-10; 
    rect.top=10; rect.bottom=g_nScreenHeight-10; 
    DrawText(hdc,text,-1,&rect,0);
    surface->ReleaseDC(hdc);
  }
}
*/
BOOL RenderTFrontTile(int index, CTileSet *set){
	switch (index){
		case 0://Nothing this is the tile behind the player
		break;

		case 1:
		set->draw(lpSecondary, 3, 80, 240);
		break;

		case 2:
		set->draw(lpSecondary, 0, 320, 240);
		set->draw(lpSecondary, 3, 80, 240);
		set->draw(lpSecondary, 7, 640-80, 240);
		break;

		case 3:
		set->draw(lpSecondary, 7, 640-80, 240);
		break;

		case 4:
		set->draw(lpSecondary, 11, 0, 240);
		break;

		case 5:
		set->draw(lpSecondary, 0, 0, 240);
		set->draw(lpSecondary, 4, 200, 240);
		break;

		case 6:
		set->draw(lpSecondary, 0, 320, 240);
		break;

		case 7:
		set->draw(lpSecondary, 8, 640-200, 240);
		set->draw(lpSecondary, 0, 640, 240);
		break;

		case 8:
		set->draw(lpSecondary, 14, 640, 240);
		break;

		case 9:
		set->draw(lpSecondary, 17, 20, 240);
		break;

		case 10:
		set->draw(lpSecondary, 12, 140, 240);
		set->draw(lpSecondary, 1, 0, 240);
		break;

		case 11:
		set->draw(lpSecondary, 1, 160, 240);
		set->draw(lpSecondary, 5, 260, 240);
		break;

		case 12:
		set->draw(lpSecondary, 1, 320, 240);
		break;

		case 13:
		set->draw(lpSecondary, 9, 640-260, 240);
		set->draw(lpSecondary, 1, 640-160, 240);
		break;

		case 14:
		set->draw(lpSecondary, 15, 640-140, 240);
		set->draw(lpSecondary, 1, 640, 240);
		break;

		case 15:
		set->draw(lpSecondary, 19, 640-20, 240);
		break;

		case 16:
		set->draw(lpSecondary, 21, 110, 240);
		set->draw(lpSecondary, 2, 0, 240);
		break;

		case 17:
		set->draw(lpSecondary, 18, 170, 240);
		set->draw(lpSecondary, 2, 80, 240);
		break;

		case 18:
		set->draw(lpSecondary, 13, 230, 240);
		set->draw(lpSecondary, 2, 160, 240);
		break;

		case 19:
		set->draw(lpSecondary, 6, 290, 240);
		set->draw(lpSecondary, 2, 240, 240);
		break;

		case 20:
		set->draw(lpSecondary, 2, 320, 240);
		break;

		case 21:
		set->draw(lpSecondary, 10, 640-290, 240);
		set->draw(lpSecondary, 2, 640-240, 240);
		break;

		case 22:
		set->draw(lpSecondary, 16, 640-230, 240);
		set->draw(lpSecondary, 2, 640-160, 240);
		break;

		case 23:
		set->draw(lpSecondary, 20, 640-170, 240);
		set->draw(lpSecondary, 2, 640-80, 240);
		break;

		case 24:
		set->draw(lpSecondary, 22, 640-110, 240);
		set->draw(lpSecondary, 2, 640, 240);
		break;

	}
	return TRUE;
}

int ConvertTileToTileSet(int tile){
	switch(tile){
		case 10:return 0;
		case 20:return 1;
		default:return 0;
	}
}

BOOL Render3D(USHORT tfront[25]){
	//Remember all rendering needs to be backwards with the closest row last
	//and the furthest row first
	int i=0;
	for(i=24;i>=21;i--){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}

	for(i=16;i<=19;i++){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}

	if(tfront[20]>0)
			RenderTFrontTile(20, &g_cTileSets[ConvertTileToTileSet(tfront[20])]);

	for(i=15;i>=13;i--){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}
	for(i=9;i<=11;i++){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}

	for(i=4;i<=5;i++){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}

	if(tfront[12]>0)
			RenderTFrontTile(12, &g_cTileSets[ConvertTileToTileSet(tfront[12])]);

	for(i=8;i>=7;i--){
		if(tfront[i]>0)
			RenderTFrontTile(i, &g_cTileSets[ConvertTileToTileSet(tfront[i])]);
	}

	if(tfront[6]>0)
			RenderTFrontTile(6, &g_cTileSets[ConvertTileToTileSet(tfront[6])]);

	if(tfront[1]>0)
			RenderTFrontTile(1, &g_cTileSets[ConvertTileToTileSet(tfront[1])]);

	if(tfront[3]>0)
			RenderTFrontTile(3, &g_cTileSets[ConvertTileToTileSet(tfront[3])]);

	if(tfront[2]>0)
			RenderTFrontTile(2, &g_cTileSets[ConvertTileToTileSet(tfront[2])]);

	return TRUE;
}
void DrawBackground(){	
	RECT bgRect;
	bgRect.top=bgRect.left=0;
	bgRect.right=g_nScreenWidth;
	bgRect.bottom=g_nScreenHeight;
	
	lpSecondary->Blt(&bgRect, lpBackground, &bgRect,DDBLT_WAIT, NULL);
}
BOOL ComposeFrame(){
	DrawBackground();
	
	USHORT temptfront[TFRONT_SIZE];

	g_cGameBoard.generateTFront(temptfront, g_cPlayer.GetFace(), 
			g_cPlayer.GetXLoc(), g_cPlayer.GetYLoc());

	g_cPlayer.CopyTFront(temptfront);

	Render3D(g_cPlayer.m_aTFront);
	
	return TRUE;	
}

BOOL ProcessFrame(){
	ComposeFrame();
	return PageFlip();
}

BOOL PageFlip(){
	RECT rect;
	rect.top=rect.left=0;
	rect.bottom=SCREEN_HEIGHT;
	rect.right=SCREEN_WIDTH;
	
	if(lpPrimary->Flip(NULL,DDFLIP_WAIT)==DDERR_SURFACELOST)
		return RestoreSurfaces();
	
	/*
	if(lpPrimary->Blt(&rect, lpSecondary, &rect, DDBLT_WAIT, NULL)==DDERR_SURFACELOST)
		return RestoreSurfaces();
	*/
	return TRUE;
}

BOOL RestoreSurfaces(){
	BOOL result=TRUE;
	//if(SUCCEEDED(lpDirectDrawObject->RestoreAllSurfaces()))result=result&&TRUE;
	
	if(SUCCEEDED(lpBackground->Restore()))result=result&&background.draw(lpBackground);
	else return FALSE;
	if(SUCCEEDED(lpPrimary->Restore()))result=result&&background.draw(lpPrimary);
	else return FALSE;
	if(SUCCEEDED(lpSecondary->Restore()))result=result&&background.draw(lpSecondary);
	else return FALSE;
	//Remember to restore any other surfaces in the game
	for(int i=0;i<NUM_TILE_SETS;i++){
		if(g_cTileSets[i].Restore())result=result&&TRUE;
	}
	
	result=result&&GetImages();
	return result;
}


long CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
		case WM_ACTIVATEAPP: ActiveApp=wParam;break;
		case WM_CREATE: break;
		case WM_KEYDOWN:
			if(keyboard_handler(wParam))DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			MusicPlayer.Stop();
			ShutDownDirectDraw();
			ShowCursor(TRUE);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0L;
}

BOOL LoadBackgroundFile(){
	return background.load("art\\background.bmp");
}

BOOL LoadImages(){
	if(!LoadBackgroundFile())return FALSE;
	if(!defaultImageSet.load("art\\set0001.bmp"))return FALSE;
	if(!defaultDoorSet.load("art\\set0002.bmp"))return FALSE;
	return TRUE;
}

BOOL GetBackground(){
	return background.draw(lpBackground);
}


BOOL GetImages(){
	if(!GetBackground())return FALSE;
	if(!g_cTileSets[0].GetImages(&defaultImageSet))return FALSE;
	if(!g_cTileSets[1].GetImages(&defaultDoorSet))return FALSE;
	return TRUE;
}

BOOL InitImages(){
	if(!LoadImages())return FALSE;
	for(int i=0;i<NUM_TILE_SETS;i++){
		g_cTileSets[0].InitTileObjects();
		g_cTileSets[1].InitTileObjects();
	}
	if(!GetImages())return FALSE;
	return TRUE;
}

BOOL keyboard_handler(WPARAM keystroke){ //keyboard handler
	BOOL result=FALSE;
	switch(keystroke){
		case VK_ESCAPE: result=TRUE; break;
		#ifdef TEST_RENDERING1
		case 'T':global_test_number++;
			if(global_test_number>24)global_test_number=0;break;
		#endif
		//Remember to make it so cannot pass through tiles
		case VK_UP:{
			if(g_cPlayer.m_aTFront[6]>0){
				switch(g_cGameBoard.GetTileType(g_cPlayer.m_aTFront[6])){
					case WALL:break;
					case DOOR:g_cPlayer.Move(FORWARD, 2);break;
				}
			}else g_cPlayer.Move(FORWARD, 1);
			}break;
		case VK_DOWN:
			if(g_cPlayer.m_aTFront[0]>0){
				switch(g_cGameBoard.GetTileType(g_cPlayer.m_aTFront[0])){
					case WALL:break;
					case DOOR:g_cPlayer.Move(BACKWARD, 2);break;
				}
			}else g_cPlayer.Move(BACKWARD, 1);
			break;
		case VK_LEFT:
			g_cPlayer.Turn(LEFT);
			break;
		case VK_RIGHT:
			g_cPlayer.Turn(RIGHT);
			break;
	}
	return result;
}

void ReleaseSurfaces(){
	for(int i=0;i<NUM_TILE_SETS;i++){
		g_cTileSets[i].Release();
	}
	if(lpSecondary!=NULL)
		lpSecondary->Release();
	if(lpPrimary!=NULL) 
		lpPrimary->Release();
	if(lpBackground!=NULL)
		lpBackground->Release();
}

void ShutDownDirectDraw(){
  if(lpDirectDrawObject!=NULL){
    ReleaseSurfaces();
    lpDirectDrawObject->Release();
  }
}