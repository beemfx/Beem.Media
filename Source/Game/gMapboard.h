#ifndef __MAPBOARD_H__
#define __MAPBOARD_H__

#include <windows.h>
#include "defines.h"

typedef unsigned short USHORT;

typedef struct eMapHeader {
	char mapType[2];
	unsigned short mapVersion;
	unsigned long mapFileSize;
	unsigned short mapReserved1;
	unsigned short mapReserved2;
	unsigned short mapWidth;
	unsigned short mapHeight;
	unsigned long mapDataSize;
	unsigned long mapTileDataSize;
	unsigned long mapPropertyDataSize;
	unsigned short mapNumProperty;
} MAPHEADER;

class CGameMap {
	private:
		BOOL mapLoaded;
		USHORT * tiles;
		USHORT * prop;
		MAPHEADER fileHeader;
		unsigned short tbase(int tx, int ty)const;
		char boardname[_MAX_PATH];
		TileType m_nType[256];
	public:
		CGameMap();
		~CGameMap();
		//int saveMap(char openmap[_MAX_PATH]);
		//int resetBoard(void);
		int openMap(char openmap[_MAX_PATH]);
		//int boardEdit(int x, int y, unsigned int propnum, unsigned int newvalue);
		//int boardEdit(int x, int y);
		USHORT getTileStat(int x, int y, int propnum)const;
		USHORT getTileStat(int x, int y)const;
		USHORT getMapWidth(void)const;
		USHORT getMapHeight(void)const;
		USHORT getNumProperty(void)const;
		BOOL generateTFront(USHORT tfront[TFRONT_SIZE], const Direction FaceDirection, const int xloc, const int yloc);
		void SetTileType(int index, TileType newType);
		TileType GetTileType(int index);
};

#endif
