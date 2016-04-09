#include "mapboard.h"
#include <stdio.h>

unsigned short ExplorMap::tbase(int tx, int ty)
{
	return tx + fileHeader.mapWidth*(ty-1)-1;
}

int ExplorMap::getTileStat(int x, int y, int propnum)
{
	return prop[propnum][TBASE];
}

int ExplorMap::getTileStat(int x, int y)
{
	return tiles[TBASE];
}

int ExplorMap::boardEdit(int x, int y, unsigned int propedit, unsigned int newvalue)
{
	if(propedit>fileHeader.mapNumProperty)
		return 210;
	prop[propedit][TBASE] = newvalue;
	if((prop[propedit][TBASE] < 0) || ((prop[propedit][TBASE] < 0)))
		prop[propedit][TBASE] = 0;//reset if value less than 0
	return 0;
}

int ExplorMap::boardEdit(int x, int y)
{
		char buffer[80];

		switch (tiles[TBASE]){
			case 0:
				tiles[TBASE] = 10;
				return 10;
			case 10:
				tiles[TBASE] = 20;
				return 20;
			case 20:
				tiles[TBASE] = 0;
				return 0;
			default:
				//In case the current tile was not valid it is reset to zero
				tiles[TBASE] = 0;
				return 201;
		}
}

int ExplorMap::resetBoard(void)
{
	int i;
	int j;

	for(i=0; i<NUMTILES; i++){
		tiles[i]=0;
		for(j=0;j<fileHeader.mapNumProperty; j++)
			prop[j][i]=0;
	}
	return 0;
}

int ExplorMap::openMap(char openmap[FNAMELEN])
{

	FILE *openfile;
	int i;

	if((openfile = fopen(openmap, "rb"))==NULL)
		return 101;

	fread(&fileHeader, sizeof(fileHeader), (size_t)1, openfile);

	//Check Map statistics to make sure it is valid
	//  if not return error code.
	if(fileHeader.mapType != 19781){
		fclose(openfile);
		return 110;
	}
	if(fileHeader.mapVersion != 3){
		fclose(openfile);
		return 115;
	}

	fread(&tiles, fileHeader.mapTileDataSize, (size_t)1, openfile);
	for (i=0; i<fileHeader.mapNumProperty; i++){
		fread(&prop[i], fileHeader.mapPropertyDataSize, (size_t)1, openfile);
	}
	fclose(openfile);

}

int ExplorMap::saveMap(char openmap[FNAMELEN])
{
	FILE *savefile;
	int i;

	if((savefile = fopen(openmap, "wb"))==NULL)
		return 101;

	fileHeader.mapPropertyDataSize = sizeof(prop[0])*fileHeader.mapNumProperty;
	fileHeader.mapTileDataSize = sizeof(tiles);
	fileHeader.mapDataSize = fileHeader.mapTileDataSize
						 + fileHeader.mapPropertyDataSize*fileHeader.mapNumProperty;
	fileHeader.mapFileSize = fileHeader.mapDataSize + sizeof(fileHeader);

	fwrite(&fileHeader, sizeof(fileHeader), (size_t)1, savefile);
	fwrite(&tiles, fileHeader.mapTileDataSize, (size_t)1, savefile);
	for(i=0; i<fileHeader.mapNumProperty; i++)
		fwrite(&prop[i], fileHeader.mapTileDataSize, (size_t)1, savefile);

	fclose(savefile);

	return 0;
}