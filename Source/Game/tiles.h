#ifndef __TILES_H__
#define __TILES_H__

#include <ddraw.h>
#include "bmp.h"


class CTileObject{
	protected:
		LPDIRECTDRAWSURFACE m_lpTileImage;
		int m_nWidth, m_nHeight;
		void CreateSurface();
		RECT m_rectSource;
	public:
		CTileObject(int width, int height);
		~CTileObject();
		BOOL load(CBitmapReader *buffer, int x, int y, int w, int h);
		void Release();
		BOOL Restore();
		void draw(LPDIRECTDRAWSURFACE dest, int x, int y, int w, int h);
};

#endif