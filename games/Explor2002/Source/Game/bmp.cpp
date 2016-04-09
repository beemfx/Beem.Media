#include "bmp.h"
#include "defines.h"

extern int g_nScreenWidth, g_nScreenHeight;

CBitmapReader::CBitmapReader(){
	m_hBitmap=NULL; m_nFileWidth=m_nFileHeight=0;
}

CBitmapReader::~CBitmapReader(){
	if(m_hBitmap)DeleteObject(m_hBitmap);
}

BOOL CBitmapReader::draw(LPDIRECTDRAWSURFACE surface){
	return draw(surface, g_nScreenWidth, g_nScreenHeight, m_nFileWidth, m_nFileHeight, 0, 0);
}

BOOL CBitmapReader::draw(LPDIRECTDRAWSURFACE surface, int w, int h, int x, int y){
	return draw(surface, w, h, w, h, x, y);
}

BOOL CBitmapReader::draw(LPDIRECTDRAWSURFACE surface, int w1, int h1, int w2, int h2, int x, int y){
	HDC hDCSurface, hDCBitmap;

	surface->GetDC(&hDCSurface);
	hDCBitmap=CreateCompatibleDC(hDCSurface);
	SetMapMode(hDCBitmap, GetMapMode(hDCSurface));

	SelectObject(hDCBitmap, m_hBitmap);
	SetStretchBltMode(hDCSurface, COLORONCOLOR);

	StretchBlt(hDCSurface, 0, 0, w1, h1, hDCBitmap, x, y, w2, h2, SRCCOPY);

	DeleteDC(hDCBitmap);
	surface->ReleaseDC(hDCSurface);
	return TRUE;
}

BOOL CBitmapReader::load(char *filename){
	if(m_hBitmap){DeleteObject(m_hBitmap); m_hBitmap=NULL;};

	m_hBitmap=(HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(m_hBitmap==NULL)return FALSE;

	BITMAP bm;
	GetObject(m_hBitmap, sizeof(bm), &bm);
	m_nFileWidth=bm.bmWidth; m_nFileHeight=bm.bmHeight;
	return TRUE;

}