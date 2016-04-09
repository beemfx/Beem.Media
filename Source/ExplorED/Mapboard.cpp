#include <stdlib.h>
#include <windows.h>
#include "mapboard.h"
#include <stdio.h>

//About ADJUSTMENT.  It was necessary to add this as when compling
//under microsoft the program was reading 2 bytes more for the file
//header than it should have.

ExplorMap::ExplorMap()
{
	tiles=new USHORT[1];
	prop=new USHORT[1];
}
ExplorMap::~ExplorMap()
{
	//MessageBox(NULL, "Destructor Called", "message", MB_OK);
	if(tiles){
		delete []tiles;
		tiles=NULL;
	}
	if(prop){
		delete []prop;
		prop=NULL;
	}
}

unsigned short ExplorMap::getNumProperty(void)const
{
	return fileHeader.mapNumProperty;
}

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

USHORT ExplorMap::getTileStat(int x, int y, int propnum)const
{
	if(x<1||x>fileHeader.mapWidth)return 0;
	if(y<1||y>fileHeader.mapHeight)return 0;
	if(propnum<1||propnum>fileHeader.mapNumProperty)return 0;
	return prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)];
}

USHORT ExplorMap::getTileStat(int x, int y)const
{
	if(x<1||x>fileHeader.mapWidth)return 0;
	if(y<1||y>fileHeader.mapHeight)return 0;
	return tiles[tbase(x, y)];
}

int ExplorMap::boardEdit(int x, int y, unsigned int propnum, unsigned int newvalue)
{
	if(propnum>fileHeader.mapNumProperty)
		return 210;
	prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]=newvalue;
	if((prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]<0))
		prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]=0; //reset if value is less than zero
	return 0;
}

int ExplorMap::boardEdit(int x, int y)
{
		if(x<1||x>fileHeader.mapWidth)return 0;
		if(y<1||y>fileHeader.mapHeight)return 0;

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
	//int i;
	//int j;
	ZeroMemory(tiles, fileHeader.mapTileDataSize);
	ZeroMemory(prop, fileHeader.mapTileDataSize*fileHeader.mapNumProperty);
	//for(i=0; i<NUMTILES; i++){
	//	tiles[i]=0;
	//	for(j=0;j<fileHeader.mapNumProperty; j++)
	//		prop[j][i]=0;
	//}
	return 0;
}

int ExplorMap::openMap(char openmap[_MAX_PATH])
{
	//Use createfile to open the map data from file
	HANDLE openfile;
	DWORD bytesread;
	if((openfile=CreateFile(openmap, 
						GENERIC_READ, 
						FILE_SHARE_READ, 
						(LPSECURITY_ATTRIBUTES)NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL, 
						(HANDLE)NULL))==INVALID_HANDLE_VALUE)return 101;
	ReadFile(openfile, &fileHeader, sizeof(fileHeader), &bytesread, NULL);
	
	//Check Map statistics to make sure it is valid
	//  if not return error code.
	if(!strcmp("EM", fileHeader.mapType)){
		CloseHandle(openfile);
		return 110;
	}
	if(fileHeader.mapVersion != 3){
		CloseHandle(openfile);
		return 115;
	}
	{
		if(tiles){
			delete [] tiles;
			tiles=NULL;
		}
		tiles = new USHORT[fileHeader.mapHeight*fileHeader.mapWidth];
	}
	ReadFile(openfile, tiles, fileHeader.mapTileDataSize, &bytesread, NULL);
	{
		if(prop){
			delete [] prop;
			prop=NULL;
		}
		prop = new USHORT[fileHeader.mapHeight*fileHeader.mapWidth*fileHeader.mapNumProperty];
	}
	ReadFile(openfile, prop, fileHeader.mapPropertyDataSize, &bytesread, NULL);
	CloseHandle(openfile);
	return 0;
}

int ExplorMap::saveMap(char openmap[_MAX_PATH])
{
	//Use createfile to save the tile data
	HANDLE savefile;
	DWORD byteswritten;

	if((savefile=CreateFile(openmap,
							GENERIC_WRITE,
							FILE_SHARE_WRITE,
							(LPSECURITY_ATTRIBUTES)NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							(HANDLE)NULL))==INVALID_HANDLE_VALUE)return 101;

	strcpy(fileHeader.mapType, "EM");
	fileHeader.mapVersion=3;
	fileHeader.mapTileDataSize=fileHeader.mapWidth*fileHeader.mapHeight*sizeof(USHORT);
	fileHeader.mapPropertyDataSize=fileHeader.mapTileDataSize*fileHeader.mapNumProperty;
	fileHeader.mapDataSize=fileHeader.mapTileDataSize+ fileHeader.mapPropertyDataSize;
	fileHeader.mapFileSize=fileHeader.mapDataSize+sizeof(fileHeader);

	WriteFile(savefile, &fileHeader, sizeof(fileHeader), &byteswritten, NULL);
	WriteFile(savefile, tiles, fileHeader.mapTileDataSize, &byteswritten, NULL);
	WriteFile(savefile, prop, fileHeader.mapPropertyDataSize, &byteswritten, NULL);

	CloseHandle(savefile);

	return 0;
}