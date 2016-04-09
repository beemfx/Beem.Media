#ifndef __DDSETUP_H__
#define __DDSETUP_H__

#include <ddraw.h>

extern long CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD color(COLORREF rgb, LPDIRECTDRAWSURFACE surface);
BOOL InitSurfaces(HWND hWnd);
HWND CreateDefaultWindow(char *name, HINSTANCE hInstance);
BOOL InitDirectDraw(HWND hWnd);

#endif