#ifndef __MAPBOARD_H__
#define __MAPBOARD_H__

//We need to pack the stucts to 1 so they read/write correctly.
#pragma pack(1)

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

typedef class ExplorMap {
	public:
		ExplorMap();
		~ExplorMap();
	private:
		USHORT * tiles;
		USHORT * prop;
		MAPHEADER fileHeader;
		unsigned short tbase(int tx, int ty)const;
	public:
		int saveMap(char openmap[_MAX_PATH]);
		int resetBoard(void);
		int openMap(char openmap[_MAX_PATH]);
		int boardEdit(int x, int y, unsigned int propnum, unsigned int newvalue);
		int boardEdit(int x, int y);
		char boardname[_MAX_PATH];
		USHORT getTileStat(int x, int y, int propnum)const;
		USHORT getTileStat(int x, int y)const;
		unsigned short getMapWidth(void)const;
		unsigned short getMapHeight(void)const;
		unsigned short getNumProperty(void)const;
} EXPLORMAP;

#endif
