//Tile Manager
#include "tilemgr.h"
#include "tiles.h"
#include "bmp.h"

CTileSet::CTileSet(){
}

CTileSet::~CTileSet(){
}

BOOL CTileSet::draw(LPDIRECTDRAWSURFACE dest, int index, int x, int y){
	//m_cTiles[index]->draw(dest, x, y);
	switch (index){
		//Facing
		case 0:
			m_cTiles[0]->draw(dest, x, y, 320, 320);
			break;
		case 1:
			m_cTiles[0]->draw(dest, x, y, 160, 160);
			break;
		case 2:
			m_cTiles[0]->draw(dest, x, y, 80, 80);
			break;
		//At an angle to right
		case 3:
			m_cTiles[1]->draw(dest, x, y, 160, 640);
			break;
		case 4:
			m_cTiles[1]->draw(dest, x, y, 80, 320);
			break;
		case 5:
			m_cTiles[1]->draw(dest, x, y, 40, 160);
			break;
		case 6:
			m_cTiles[1]->draw(dest, x, y, 20, 80);
			break;
		//At an angle to right
		case 7:
			m_cTiles[2]->draw(dest, x, y, 160, 640);
			break;
		case 8:
			m_cTiles[2]->draw(dest, x, y, 80, 320);
			break;
		case 9:
			m_cTiles[2]->draw(dest, x, y, 40, 160);
			break;
		case 10:
			m_cTiles[2]->draw(dest, x, y, 20, 80);
			break;
		//at an angle 1 row to the left
		case 11:
			m_cTiles[1]->draw(dest, x, y, 160, 320);
			break;
		case 12:
			m_cTiles[1]->draw(dest, x, y, 120, 160);
			break;
		case 13:
			m_cTiles[1]->draw(dest, x, y, 60, 80);
			break;
		//at an angle 1 row to the right
		case 14:
			m_cTiles[2]->draw(dest, x, y, 160, 320);
			break;
		case 15:
			m_cTiles[2]->draw(dest, x, y, 120, 160);
			break;
		case 16:
			m_cTiles[2]->draw(dest, x, y, 60, 80);
			break;
		//at an angle 2 rows to the left
		case 17:
			m_cTiles[1]->draw(dest, x, y, 200,160);
			break;
		case 18:
			m_cTiles[1]->draw(dest, x, y, 100, 80);
			break;
		//at an angle 2 rows to the right
		case 19:
			m_cTiles[2]->draw(dest, x, y, 200, 160);
			break;
		case 20:
			m_cTiles[2]->draw(dest, x, y, 100, 80);
			break;
		//at an angle 3 rows to the left
		case 21:
			m_cTiles[1]->draw(dest, x, y, 140, 80);
			break;
		//at an angle 3 rows to the right
		case 22:
			m_cTiles[2]->draw(dest, x, y, 140, 80);
			break;
	}		
	return TRUE;
}

BOOL CTileSet::Restore(){
	BOOL result=TRUE;
	for(int i=0;i<NUM_TILES;i++){
		if(SUCCEEDED(m_cTiles[i]->Restore()))result=result&&TRUE;
	}
	return result;
}

BOOL CTileSet::Release(){
	for(int i=0; i<NUM_TILES;i++){
		m_cTiles[i]->Release();
	}
	return TRUE; 
}

BOOL CTileSet::GetImages(CBitmapReader *bitmap){
	m_cTiles[0]->load(bitmap, 0, 0, 160, 160);
	m_cTiles[1]->load(bitmap, 160, 0, 40, 160);
	m_cTiles[2]->load(bitmap, 200, 0, 40, 160);
	return TRUE;
}
/*
BOOL CTileSet::LoadImageFile(CBitmapReader *buffer){
	return buffer.load(filename);
}
*/
void CTileSet::InitTileObjects(){
	m_cTiles[0]=new CTileObject(160, 160);
	m_cTiles[1]=new CTileObject(40, 160);
	m_cTiles[2]=new CTileObject(40, 160);	
}
