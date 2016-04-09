#include "mapboard.h"
#include <stdio.h>
#include <windows.h>

//The following definition should be removed once I get the map files to
//load into ram correctly.
//#define NOTLOADING

unsigned short ExplorMap::getMapWidth(void)const
{
	return fileHeader.mapWidth;
}
unsigned short ExplorMap::getMapHeight(void)const
{
	return fileHeader.mapHeight;
}
unsigned short ExplorMap::tbase(int tx, int ty)const
{
	return tx + fileHeader.mapWidth*(ty-1)-1;
}

int ExplorMap::getTileStat(int x, int y, int propnum)const
{
	return prop[propnum][TBASE];
}

int ExplorMap::getTileStat(int x, int y)const
{
	return tiles[tbase(x, y)];
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
		switch (tiles[tbase(x, y)]){
			case 0:
				tiles[tbase(x, y)] = 10;
				return 10;
			case 10:
				tiles[tbase(x, y)] = 20;
				return 20;
			case 20:
				tiles[tbase(x, y)] = 0;
				return 0;
			default:
				tiles[tbase(x, y)] = 0;
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
	//char buf[100];
	int i;

	if((openfile = fopen(openmap, "rb"))==NULL)
		return 101;

	fread(&fileHeader, sizeof(fileHeader),1,openfile);

	//Check Map statistics to make sure it is valid
	//  if not return error code.
	if(!strcmp("EM", fileHeader.mapType)){
		fclose(openfile);
		return 110;
	}
	if(fileHeader.mapVersion != 3){
		fclose(openfile);
		return 115;
	}
	fread(&tiles, fileHeader.mapTileDataSize, 1, openfile);
	//sprintf(buf, "Number of properties is: %i", fileHeader.mapNumProperty);
	//MessageBox(NULL, buf, "Notice", MB_OK);
	for (i=0; i<fileHeader.mapNumProperty; i++){
		fread(&prop[i], fileHeader.mapPropertyDataSize, 1, openfile);
	}
	//MessageBox(NULL, "All Done", "Done", MB_OK);
	fclose(openfile);
	return 0;
}

int ExplorMap::saveMap(char openmap[FNAMELEN])
{
	FILE *savefile;
	int i;

	if((savefile = fopen(openmap, "wb"))==NULL)
		return 101;
	
	//strcpy(fileHeader.mapType, "EM");
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