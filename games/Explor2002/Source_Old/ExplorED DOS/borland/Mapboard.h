#define NUMTILES 225
#define MAXPROPNUM 10
#define FNAMELEN 256

#define TBASE tbase(x, y)

typedef unsigned short BIT;

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
	private:
		BIT tiles[NUMTILES];
		BIT prop[MAXPROPNUM][NUMTILES];
		MAPHEADER fileHeader;
		unsigned short tbase(int tx, int ty)const;
	public:
		int saveMap(char openmap[FNAMELEN]);
		int resetBoard(void);
		int openMap(char openmap[FNAMELEN]);
		int boardEdit(int x, int y, unsigned int propedit, unsigned int newvalue);
		int boardEdit(int x, int y);
		char boardname[FNAMELEN];
		int getTileStat(int x, int y, int propnum)const;
		int getTileStat(int x, int y)const;
		unsigned short getMapWidth(void)const;
		unsigned short getMapHeight(void)const;
} EXPLORMAP;




