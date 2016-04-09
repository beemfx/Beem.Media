#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

#include "defines.h"
#include "ddsetup.h"
#include "resource.h"


extern LPDIRECTDRAW lpDirectDrawObject;
extern LPDIRECTDRAWSURFACE lpPrimary;
extern LPDIRECTDRAWSURFACE lpSecondary;
extern LPDIRECTDRAWSURFACE lpBackground;

extern DWORD g_dwTransparentColor;
extern HWND g_hwnd;
extern int g_nColorDepth;
extern int g_nScreenWidth, g_nScreenHeight;

//Sets Transparent Color
DWORD color(COLORREF rgb, LPDIRECTDRAWSURFACE surface){
	DWORD dw=CLR_INVALID;
	COLORREF rgbT;
	HDC hDc;
	DDSURFACEDESC ddsd;
	HRESULT hres;

	if(rgb!=CLR_INVALID&&SUCCEEDED(surface->GetDC(&hDc))){
		rgbT=GetPixel(hDc, 0, 0);
		SetPixel(hDc, 0, 0, rgb);
		surface->ReleaseDC(hDc);
	}

	ddsd.dwSize=sizeof(ddsd);
	while((hres=surface->Lock(NULL, &ddsd, 0, NULL))==DDERR_WASSTILLDRAWING);
	if(SUCCEEDED(hres)){
		dw=*(DWORD*)ddsd.lpSurface;
		if(ddsd.ddpfPixelFormat.dwRGBBitCount!=32)
			dw&=(1<<ddsd.ddpfPixelFormat.dwRGBBitCount)-1;
		surface->Unlock(NULL);
	}
	
	if(rgb!=CLR_INVALID&&SUCCEEDED(surface->GetDC(&hDc))){
		SetPixel(hDc, 0, 0, rgbT);
		surface->ReleaseDC(hDc);
	}
	return dw;
}

BOOL InitSurfaces(HWND hWnd){
	DDSURFACEDESC ddsd;
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount=BACK_FUFFER_COUNT;
	if(FAILED(lpDirectDrawObject->CreateSurface(&ddsd, &lpPrimary, NULL)))return FALSE;

	DDSCAPS ddscaps;
	ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
	if(FAILED(lpPrimary->GetAttachedSurface(&ddscaps, &lpSecondary)))return FALSE;
	
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight=g_nScreenHeight; ddsd.dwWidth=g_nScreenWidth;
	if(FAILED(lpDirectDrawObject->CreateSurface(&ddsd,&lpBackground,NULL)))return FALSE;

	LPDIRECTDRAWCLIPPER lpClipper;
	if(FAILED(lpDirectDrawObject->CreateClipper(NULL,&lpClipper,NULL)))return FALSE;
	if(FAILED(lpClipper->SetHWnd(NULL,hWnd)))return FALSE;
	if(FAILED(lpSecondary->SetClipper(lpClipper)))return FALSE;
	
	g_dwTransparentColor=color(TRANSPARENT_COLOR,lpPrimary);
	return TRUE;
}

BOOL InitDirectDraw(HWND hWnd){
	if(FAILED(DirectDrawCreate(NULL,&lpDirectDrawObject, NULL)))return FALSE;
	if(FAILED(lpDirectDrawObject->SetCooperativeLevel(hWnd,DDSCL_EXCLUSIVE|
	DDSCL_FULLSCREEN)))return FALSE;

	if(FAILED(lpDirectDrawObject->SetDisplayMode(g_nScreenWidth, g_nScreenHeight, g_nColorDepth)))return FALSE;
	if(!InitSurfaces(g_hwnd))return FALSE;
	return TRUE;
}

HWND CreateDefaultWindow(char *name, HINSTANCE hInstance){
	WNDCLASS wndClass;
	
	wndClass.style=CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=WindowProc;
	wndClass.cbClsExtra=wndClass.cbWndExtra=0;
	wndClass.hInstance=hInstance;
	wndClass.hIcon=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hCursor=LoadCursor(hInstance, IDC_ARROW);
	wndClass.hbrBackground=NULL;
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName=name;
	
	RegisterClass(&wndClass);

	return CreateWindowEx(WS_EX_TOPMOST, name, name,
		WS_POPUP,0,0,CW_USEDEFAULT, CW_USEDEFAULT,//GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN),
		NULL, NULL, hInstance, NULL);
}