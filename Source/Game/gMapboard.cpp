#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "gmapboard.h"
#include "defines.h"

//About ADJUSTMENT.  It was necessary to add this as when compling
//under microsoft the program was reading 2 bytes more for the file
//header than it should have.
#define ADJUSTMENT sizeof(unsigned short)

#define DEFWALL 10 //a definition of the default wall

CGameMap::CGameMap()
{
	for(int i=0;i<256;i++)
		m_nType[i]=WALL;
	mapLoaded=FALSE;
	tiles=new USHORT;
	prop=new USHORT;
}
CGameMap::~CGameMap()
{
	tiles = NULL;
	delete []tiles;
	prop=NULL;
	delete []prop;
}
void CGameMap::SetTileType(int index, TileType newType){
	m_nType[index]=newType;
}
TileType CGameMap::GetTileType(int index){
	return m_nType[index];
}
BOOL CGameMap::generateTFront(USHORT tfront[25], const Direction FaceDirection, const int xloc, const int yloc)
{
	if(!mapLoaded)return FALSE;
	if(xloc<1||xloc>getMapWidth())return FALSE;
	if(yloc<1||yloc>getMapHeight())return FALSE;

	switch(FaceDirection){
		case NORTH:{
			//row behind
			tfront[0]=getTileStat(xloc, yloc+1);
			//row on
			tfront[1]=getTileStat(xloc-1, yloc);
			tfront[2]=getTileStat(xloc, yloc);
			tfront[3]=getTileStat(xloc+1, yloc);
			//row in front
			tfront[4]=getTileStat(xloc-2, yloc-1);
			tfront[5]=getTileStat(xloc-1, yloc-1);
			tfront[6]=getTileStat(xloc, yloc-1);
			tfront[7]=getTileStat(xloc+1, yloc-1);
			tfront[8]=getTileStat(xloc+2, yloc-1);
			//2 rows in front
			tfront[9]=getTileStat(xloc-3, yloc-2);
			tfront[10]=getTileStat(xloc-2, yloc-2);
			tfront[11]=getTileStat(xloc-1, yloc-2);
			tfront[12]=getTileStat(xloc, yloc-2);
			tfront[13]=getTileStat(xloc+1, yloc-2);
			tfront[14]=getTileStat(xloc+2, yloc-2);
			tfront[15]=getTileStat(xloc+3, yloc-2);
			//3 rows in front
			tfront[16]=getTileStat(xloc-4, yloc-3);
			tfront[17]=getTileStat(xloc-3, yloc-3);
			tfront[18]=getTileStat(xloc-2, yloc-3);
			tfront[19]=getTileStat(xloc-1, yloc-3);
			tfront[20]=getTileStat(xloc, yloc-3);
			tfront[21]=getTileStat(xloc+1, yloc-3);
			tfront[22]=getTileStat(xloc+2, yloc-3);
			tfront[23]=getTileStat(xloc+3, yloc-3);
			tfront[24]=getTileStat(xloc+4, yloc-3);
			break;}
		case EAST:{
			//row behind
			tfront[0]=getTileStat(xloc-1, yloc);
			//row on
			tfront[1]=getTileStat(xloc, yloc-1);
			tfront[2]=getTileStat(xloc, yloc);
			tfront[3]=getTileStat(xloc, yloc+1);
			//row in front
			tfront[4]=getTileStat(xloc+1, yloc-2);
			tfront[5]=getTileStat(xloc+1, yloc-1);
			tfront[6]=getTileStat(xloc+1, yloc);
			tfront[7]=getTileStat(xloc+1, yloc+1);
			tfront[8]=getTileStat(xloc+1, yloc+2);
			//2 rows in front
			tfront[9]=getTileStat(xloc+2, yloc-3);
			tfront[10]=getTileStat(xloc+2, yloc-2);
			tfront[11]=getTileStat(xloc+2, yloc-1);
			tfront[12]=getTileStat(xloc+2, yloc);
			tfront[13]=getTileStat(xloc+2, yloc+1);
			tfront[14]=getTileStat(xloc+2, yloc+2);
			tfront[15]=getTileStat(xloc+2, yloc+3);
			//3 rows in front
			tfront[16]=getTileStat(xloc+3, yloc-4);
			tfront[17]=getTileStat(xloc+3, yloc-3);
			tfront[18]=getTileStat(xloc+3, yloc-2);
			tfront[19]=getTileStat(xloc+3, yloc-1);
			tfront[20]=getTileStat(xloc+3, yloc);
			tfront[21]=getTileStat(xloc+3, yloc+1);
			tfront[22]=getTileStat(xloc+3, yloc+2);
			tfront[23]=getTileStat(xloc+3, yloc+3);
			tfront[24]=getTileStat(xloc+3, yloc+4);
			break;}
		case SOUTH:{
			//row behind
			tfront[0]=getTileStat(xloc, yloc-1);
			//row on
			tfront[1]=getTileStat(xloc+1, yloc);
			tfront[2]=getTileStat(xloc, yloc);
			tfront[3]=getTileStat(xloc-1, yloc);
			//row in front
			tfront[4]=getTileStat(xloc+2, yloc+1);
			tfront[5]=getTileStat(xloc+1, yloc+1);
			tfront[6]=getTileStat(xloc, yloc+1);
			tfront[7]=getTileStat(xloc-1, yloc+1);
			tfront[8]=getTileStat(xloc-2, yloc+1);
			//2 rows in front
			tfront[9]=getTileStat(xloc+3, yloc+2);
			tfront[10]=getTileStat(xloc+2, yloc+2);
			tfront[11]=getTileStat(xloc+1, yloc+2);
			tfront[12]=getTileStat(xloc, yloc+2);
			tfront[13]=getTileStat(xloc-1, yloc+2);
			tfront[14]=getTileStat(xloc-2, yloc+2);
			tfront[15]=getTileStat(xloc-3, yloc+2);
			//3 rows in front
			tfront[16]=getTileStat(xloc+4, yloc+3);
			tfront[17]=getTileStat(xloc+3, yloc+3);
			tfront[18]=getTileStat(xloc+2, yloc+3);
			tfront[19]=getTileStat(xloc+1, yloc+3);
			tfront[20]=getTileStat(xloc, yloc+3);
			tfront[21]=getTileStat(xloc-1, yloc+3);
			tfront[22]=getTileStat(xloc-2, yloc+3);
			tfront[23]=getTileStat(xloc-3, yloc+3);
			tfront[24]=getTileStat(xloc-4, yloc+3);
			break;}
		case WEST:{
			//row behind
			tfront[0]=getTileStat(xloc+1, yloc);
			//row on
			tfront[1]=getTileStat(xloc, yloc+1);
			tfront[2]=getTileStat(xloc, yloc);
			tfront[3]=getTileStat(xloc, yloc-1);
			//row in front
			tfront[4]=getTileStat(xloc-1, yloc+2);
			tfront[5]=getTileStat(xloc-1, yloc+1);
			tfront[6]=getTileStat(xloc-1, yloc);
			tfront[7]=getTileStat(xloc-1, yloc-1);
			tfront[8]=getTileStat(xloc-1, yloc-2);
			//2 rows in front
			tfront[9]=getTileStat(xloc-2, yloc+3);
			tfront[10]=getTileStat(xloc-2, yloc+2);
			tfront[11]=getTileStat(xloc-2, yloc+1);
			tfront[12]=getTileStat(xloc-2, yloc);
			tfront[13]=getTileStat(xloc-2, yloc-1);
			tfront[14]=getTileStat(xloc-2, yloc-2);
			tfront[15]=getTileStat(xloc-2, yloc-3);
			//3 rows in front
			tfront[16]=getTileStat(xloc-3, yloc+4);
			tfront[17]=getTileStat(xloc-3, yloc+3);
			tfront[18]=getTileStat(xloc-3, yloc+2);
			tfront[19]=getTileStat(xloc-3, yloc+1);
			tfront[20]=getTileStat(xloc-3, yloc);
			tfront[21]=getTileStat(xloc-3, yloc-1);
			tfront[22]=getTileStat(xloc-3, yloc-2);
			tfront[23]=getTileStat(xloc-3, yloc-3);
			tfront[24]=getTileStat(xloc-3, yloc-4);
			break;}
	}	
	return TRUE;
}

USHORT CGameMap::getNumProperty(void)const{
	if(!mapLoaded)return 0;
	return fileHeader.mapNumProperty;
}

USHORT CGameMap::getMapWidth(void)const{
	if(!mapLoaded)return 0;
	return fileHeader.mapWidth;
}
USHORT CGameMap::getMapHeight(void)const{
	if(!mapLoaded)return 0;
	return fileHeader.mapHeight;
}
USHORT CGameMap::tbase(int tx, int ty)const{
	if(!mapLoaded)return 0;
	return tx + fileHeader.mapWidth*(ty-1)-1;
}

USHORT CGameMap::getTileStat(int x, int y, int propnum)const{
	if(!mapLoaded)return 0;
	if(x<1||x>fileHeader.mapWidth)return 0;
	if(y<1||y>fileHeader.mapHeight)return 0;
	if(propnum<1||propnum>fileHeader.mapNumProperty)return 0;
	return prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)];
}

USHORT CGameMap::getTileStat(int x, int y)const{
	if(!mapLoaded)return 0;
	if(x<1||x>getMapWidth())return DEFWALL;
	if(y<1||y>getMapWidth())return DEFWALL;
	return tiles[tbase(x, y)];
}
/*
int CGameMap::boardEdit(int x, int y, unsigned int propnum, unsigned int newvalue)
{
	if(propnum>fileHeader.mapNumProperty)
		return 210;
	prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]=newvalue;
	if((prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]<0))
		prop[fileHeader.mapWidth*fileHeader.mapHeight*(propnum-1)+tbase(x, y)]=0; //reset if value is less than zero
	return 0;
}
*/
/*
int CGameMap::boardEdit(int x, int y)
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
*/
/*
int CGameMap::resetBoard(void)
{
	ZeroMemory(tiles, fileHeader.mapTileDataSize);
	ZeroMemory(prop, fileHeader.mapTileDataSize*fileHeader.mapNumProperty);
	return 0;
}
*/

int CGameMap::openMap(char openmap[_MAX_PATH])
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
	ReadFile(openfile, &fileHeader, sizeof(fileHeader)-ADJUSTMENT, &bytesread, NULL);
	
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
		tiles = NULL;
		delete [] tiles;
		tiles = new USHORT[fileHeader.mapHeight*fileHeader.mapWidth];
	}
	ReadFile(openfile, tiles, fileHeader.mapTileDataSize, &bytesread, NULL);
	{
		prop = NULL;
		delete [] prop;
		prop = new USHORT[fileHeader.mapHeight*fileHeader.mapWidth*fileHeader.mapNumProperty];
	}
	ReadFile(openfile, prop, fileHeader.mapPropertyDataSize, &bytesread, NULL);
	CloseHandle(openfile);
	mapLoaded=TRUE;
	return 0;

}
/*
int CGameMap::saveMap(char openmap[_MAX_PATH])
{
	FILE *savefile;

	if((savefile = fopen(openmap, "wb"))==NULL)
		return 101;
	
	fileHeader.mapTileDataSize = fileHeader.mapWidth*fileHeader.mapHeight*sizeof(USHORT);
	fileHeader.mapPropertyDataSize=fileHeader.mapTileDataSize*fileHeader.mapNumProperty;
	fileHeader.mapDataSize = fileHeader.mapTileDataSize
						 + fileHeader.mapPropertyDataSize;
	fileHeader.mapFileSize = fileHeader.mapDataSize + sizeof(fileHeader);

	
	
	fwrite(&fileHeader, sizeof(fileHeader)-ADJUSTMENT, (size_t)1, savefile);
	
	
	fwrite(tiles, fileHeader.mapTileDataSize, (size_t)1, savefile);
	
	fwrite(prop, fileHeader.mapPropertyDataSize, (size_t)1, savefile);

	fclose(savefile);

	return 0;
}
*/