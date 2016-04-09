#define NUMTILES 225
#define MAXPROPNUM 10
#define FNAMELEN 13

#define TBASE tbase(x, y)

typedef unsigned short int BIT;

typedef struct eMapHeader {
	unsigned int mapType;
	unsigned int mapVersion;
	unsigned long mapFileSize;
	unsigned int mapReserved1;
	unsigned int mapReserved2;
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned long mapDataSize;
	unsigned long mapTileDataSize;
	unsigned long mapPropertyDataSize;
	unsigned int mapNumProperty;
} MAPHEADER;

typedef class ExplorMap {
	private:
		BIT tiles[NUMTILES];
		BIT prop[MAXPROPNUM][NUMTILES];
		MAPHEADER fileHeader;
		unsigned short tbase(int tx, int ty);
	public:
		int saveMap(char openmap[FNAMELEN]);
		int resetBoard(void);
		int openMap(char openmap[FNAMELEN]);
		int boardEdit(int x, int y, unsigned int propedit, unsigned int newvalue);
		int boardEdit(int x, int y);
		char boardname[FNAMELEN];
		int getTileStat(int x, int y, int propnum);
		int getTileStat(int x, int y);
} EXPLORMAP;




