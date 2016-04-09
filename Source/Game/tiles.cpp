#include <ddraw.h>
#include "defines.h"
#include "tiles.h"

extern LPDIRECTDRAW lpDirectDrawObject;
extern DWORD g_dwTransparentColor;

CTileObject::CTileObject(int width, int height){
	m_nWidth=width;
	m_nHeight=height;
	m_lpTileImage=NULL;

	m_rectSource.top=m_rectSource.left=0;
	m_rectSource.right=m_nWidth;
	m_rectSource.bottom=m_nHeight;

	CreateSurface();
}

CTileObject::~CTileObject(){
	SAFE_DELETE(m_lpTileImage);
	/*
	m_lpTileImage=NULL;
	delete[]m_lpTileImage;
	*/
}

BOOL CTileObject::load(CBitmapReader *buffer, int x, int y, int w, int h){
	return buffer->draw(m_lpTileImage, m_nWidth, m_nHeight, w, h, x, y);	
}

void CTileObject::Release(){
	SAFE_RELEASE(m_lpTileImage);
	/*
	if(m_lpTileImage!=NULL)
		m_lpTileImage->Release();
	*/
}

BOOL CTileObject::Restore(){
	if(m_lpTileImage)
	if(SUCCEEDED(m_lpTileImage->Restore()))return TRUE;
	return FALSE;
}

void CTileObject::draw(LPDIRECTDRAWSURFACE dest, int x, int y, int w, int h){
	RECT rectDest;
	rectDest.left=x-w/2;
	rectDest.right=rectDest.left+w;
	rectDest.top=y-h/2;
	rectDest.bottom=rectDest.top+h;

	dest->Blt(&rectDest,m_lpTileImage,&m_rectSource,
    DDBLT_KEYSRC|DDBLT_WAIT,NULL);
}

void CTileObject::CreateSurface(){
	DDSURFACEDESC ddsd;
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight=m_nHeight;
	ddsd.dwWidth=m_nWidth;

	DDCOLORKEY ddck;
	ddck.dwColorSpaceLowValue=ddck.dwColorSpaceHighValue=g_dwTransparentColor;
	
	if(FAILED(lpDirectDrawObject->CreateSurface(&ddsd, &m_lpTileImage, NULL))){
		m_lpTileImage=NULL;
	}
	m_lpTileImage->SetColorKey(DDCKEY_SRCBLT, &ddck);
}
