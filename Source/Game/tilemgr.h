#ifndef __TILEMGR_H__
#define __TILEMGR_H__

#include "tiles.h"
#include "bmp.h"
#include "defines.h"

class CTileSet{
	private:
		CTileObject *m_cTiles[NUM_TILES];
		//CBitmapReader bitmap;
	public:
		CTileSet();
		~CTileSet();
		BOOL draw(LPDIRECTDRAWSURFACE dest, int index, int x, int y);
		void InitTileObjects();
		BOOL GetImages(CBitmapReader *bitmap);
		BOOL Restore();
		BOOL Release();
		//BOOL LoadImageFile(char *filename);
};

#endif