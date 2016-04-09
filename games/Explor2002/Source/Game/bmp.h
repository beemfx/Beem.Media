#ifndef __BMP_H__
#define __BMP_H__

#include <ddraw.h>
#include <windows.h>
#include <windowsx.h>
#include "defines.h"

class CBitmapReader{
protected:
	HBITMAP m_hBitmap;
	int m_nFileWidth, m_nFileHeight;
public:
	CBitmapReader();
	~CBitmapReader();
	BOOL draw(LPDIRECTDRAWSURFACE surface);
	BOOL draw(LPDIRECTDRAWSURFACE surface, int w, int h, int x, int y);
	BOOL draw(LPDIRECTDRAWSURFACE surface, int w1, int h1, int w2, int h2, int x, int y);
	BOOL load(char *filename);

};
#endif