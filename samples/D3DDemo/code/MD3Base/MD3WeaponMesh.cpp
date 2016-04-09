#define D3D_MD3
#include <d3dx9.h>
#include <stdio.h>
#include "defines.h"
#include "functions.h"
#include "md3.h"

CMD3WeaponMesh::CMD3WeaponMesh()
{
	m_lpFlashTex=NULL;
	m_lpWeaponTex=NULL;
	m_lpBarrelTex=NULL;

	m_bBarrel=FALSE;

	m_nTagWeapon=m_nTagBarrel=m_nTagFlash=0;

	m_bLoaded=FALSE;
}


CMD3WeaponMesh::~CMD3WeaponMesh()
{
	Clear();
}

HRESULT CMD3WeaponMesh::Clear()
{
	DWORD i=0, j=0;
	LONG lNumMesh=0;

	if(!m_bLoaded)
		return S_FALSE;

	m_TexDB.ClearDB();

	//Delete the weapon.
	m_meshWeapon.GetNumMeshes(&lNumMesh);
	for(i=0; i<(DWORD)lNumMesh; i++){
		SAFE_RELEASE(m_lpWeaponTex[i]);
	}
	SAFE_FREE(m_lpWeaponTex);
	m_meshWeapon.ClearMD3();

	//Delete the barrel.
	if(m_bBarrel){
		m_meshBarrel.GetNumMeshes(&lNumMesh);
		for(i=0; i<(DWORD)lNumMesh; i++){
			SAFE_RELEASE(m_lpBarrelTex[i]);
		}
		SAFE_FREE(m_lpBarrelTex);
		m_meshBarrel.ClearMD3();
	}

	//Delete the flash.
	m_meshFlash.GetNumMeshes(&lNumMesh);
	for(i=0; i<(DWORD)lNumMesh; i++){
		SAFE_RELEASE(m_lpFlashTex[i]);
	}
	SAFE_FREE(m_lpFlashTex);
	m_meshFlash.ClearMD3();

	//Delete the hand.
	m_meshHand.ClearMD3();

	m_bLoaded=FALSE;

	m_bBarrel=FALSE;

	m_nTagWeapon=m_nTagBarrel=m_nTagFlash=0;

	SAFE_RELEASE(m_lpDevice);
	return S_OK;
}

HRESULT CMD3WeaponMesh::Load(LPDIRECT3DDEVICE9 lpDevice, char szDir[], MD3DETAIL nDetail)
{
	char szPath[MAX_PATH];
	char szWeaponName[MAX_QPATH];
	char szWeaponPath[MAX_PATH];
	char szBarrelPath[MAX_PATH];
	char szFlashPath[MAX_PATH];
	char szHandPath[MAX_PATH];
	char szDetailLevel[3];

	char szShaderName[MAX_QPATH];
	char szTexName[MAX_PATH];
	LONG lNumMesh=0;
	DWORD i=0;

	DWORD dwLen=0;

	HRESULT hr=0;

	Clear();

	m_lpDevice=lpDevice;
	m_lpDevice->AddRef();

	//Get the weapon's name.
	strcpy(szPath, szDir);
	dwLen=strlen(szPath);
	if(szPath[dwLen-1]!='\\'){
		szPath[dwLen]='\\';
		szPath[dwLen+1]=0;
	}

	strcpy(szWeaponName, szPath);
	dwLen=strlen(szWeaponName);
	szWeaponName[dwLen-1]=0;
	RemoveDirectoryFromStringA(szWeaponName, szWeaponName);
	
	//Prepare each of the path names.

	//Set the detail level.
	if(nDetail==DETAIL_LOW)
		strcpy(szDetailLevel, "_2");
	else if(nDetail==DETAIL_MEDIUM)
		strcpy(szDetailLevel, "_1");
	else
		strcpy(szDetailLevel, "");
	
	//The weapon path.
	sprintf(szWeaponPath, "%s%s%s.md3", szPath, szWeaponName, szDetailLevel);
	//The barrel path.
	sprintf(szBarrelPath, "%s%s_barrel%s.md3", szPath, szWeaponName, szDetailLevel);
	//The flash path.
	sprintf(szFlashPath, "%s%s_flash.md3", szPath, szWeaponName);
	//The hand path.
	sprintf(szHandPath, "%s%s_hand.md3", szPath, szWeaponName);
	
	//Attempt to load the weapon mesh.
	hr=m_meshWeapon.LoadMD3A(szWeaponPath, NULL, lpDevice, D3DPOOL_DEFAULT);
	
	if(FAILED(hr)){
		if(nDetail!=DETAIL_HIGH)
		{
			SAFE_RELEASE(m_lpDevice);
			return Load(lpDevice, szDir, DETAIL_HIGH);
		}
		SAFE_RELEASE(m_lpDevice);
		return E_FAIL;
	}
	
	//Load the hand and flash meshes.
	hr=m_meshHand.LoadMD3A(szHandPath, NULL, lpDevice, D3DPOOL_DEFAULT);
	hr|=m_meshFlash.LoadMD3A(szFlashPath, NULL, lpDevice, D3DPOOL_DEFAULT);

	if(FAILED(hr)){
		m_meshHand.ClearMD3();
		m_meshFlash.ClearMD3();
		m_meshWeapon.ClearMD3();
		SAFE_RELEASE(m_lpDevice);
		return E_FAIL;
	}

	//Load the barrel, if success then we set barrel to true.
	hr=m_meshBarrel.LoadMD3A(szBarrelPath, NULL, lpDevice, D3DPOOL_DEFAULT);

	if(SUCCEEDED(hr)){
		m_bBarrel=TRUE;
	}
	//Load the textures.
	m_meshWeapon.GetNumMeshes(&lNumMesh);
	m_lpWeaponTex=(LPDIRECT3DTEXTURE9*)malloc(lNumMesh*sizeof(LPDIRECT3DTEXTURE9));
	if(m_lpWeaponTex==NULL){
		m_meshHand.ClearMD3();
		m_meshFlash.ClearMD3();
		m_meshWeapon.ClearMD3();
		m_meshBarrel.ClearMD3();
		SAFE_RELEASE(m_lpDevice);
		return E_FAIL;
	}
	if(m_bBarrel){
		m_meshBarrel.GetNumMeshes(&lNumMesh);
		m_lpBarrelTex=(LPDIRECT3DTEXTURE9*)malloc(lNumMesh*sizeof(LPDIRECT3DTEXTURE9));
		if(m_lpBarrelTex==NULL){
			SAFE_DELETE_ARRAY(m_lpWeaponTex);
			m_meshHand.ClearMD3();
			m_meshFlash.ClearMD3();
			m_meshWeapon.ClearMD3();
			m_meshBarrel.ClearMD3();
			SAFE_RELEASE(m_lpDevice);
			return E_FAIL;
		}
	}
	m_meshFlash.GetNumMeshes(&lNumMesh);
	m_lpFlashTex=(LPDIRECT3DTEXTURE9*)malloc(lNumMesh*sizeof(LPDIRECT3DTEXTURE9));
	if(m_lpFlashTex==NULL){
		SAFE_DELETE_ARRAY(m_lpWeaponTex);
		if(m_bBarrel){
			SAFE_DELETE_ARRAY(m_lpBarrelTex);
		}
		m_meshHand.ClearMD3();
		m_meshFlash.ClearMD3();
		m_meshWeapon.ClearMD3();
		m_meshBarrel.ClearMD3();
		SAFE_RELEASE(m_lpDevice);
		return E_FAIL;
	}

	//Get the weapon textures.
	m_meshWeapon.GetNumMeshes(&lNumMesh);
	for(i=0; i<(DWORD)lNumMesh; i++){
		m_meshWeapon.GetShader(i+1, 1, szShaderName, NULL);
		RemoveDirectoryFromStringA(szShaderName, szShaderName);
		sprintf(szTexName, "%s%s", szPath, szShaderName);
		if(SUCCEEDED(TextureExtension(szTexName))){
			m_TexDB.GetTexture(szTexName, &m_lpWeaponTex[i]);
		}else{
			m_lpWeaponTex[i]=NULL;
		}
	}
	//Get the barrel textures if it exists.
	if(m_bBarrel){
		m_meshBarrel.GetNumMeshes(&lNumMesh);
		for(i=0; i<(DWORD)lNumMesh; i++){
			m_meshBarrel.GetShader(i+1, 1, szShaderName, NULL);
			RemoveDirectoryFromStringA(szShaderName, szShaderName);
			sprintf(szTexName, "%s%s", szPath, szShaderName);
			if(SUCCEEDED(TextureExtension(szTexName))){
				m_TexDB.GetTexture(szTexName, &m_lpBarrelTex[i]);
			}else{
				m_lpBarrelTex[i]=NULL;
			}
		}
	}
	//Get the flash textures.
	m_meshFlash.GetNumMeshes(&lNumMesh);
	for(i=0; i<(DWORD)lNumMesh; i++){
		m_meshFlash.GetShader(i+1, 1, szShaderName, NULL);
		RemoveDirectoryFromStringA(szShaderName, szShaderName);
		sprintf(szTexName, "%s%s", szPath, szShaderName);
		if(SUCCEEDED(TextureExtension(szTexName))){
			m_TexDB.GetTexture(szTexName, &m_lpFlashTex[i]);
		}else{
			m_lpFlashTex[i]=NULL;
		}
	}
	//Get the tags.
	GetLink(&m_meshWeapon, "tag_weapon", &m_nTagWeapon);
	GetLink(&m_meshWeapon, "tag_barrel", &m_nTagBarrel);
	GetLink(&m_meshWeapon, "tag_flash", &m_nTagFlash);

	m_bLoaded=TRUE;

	return S_OK;
}

HRESULT CMD3WeaponMesh::TextureExtension(char szShader[MAX_PATH])
{
	DWORD dwLen=0, i=0, j=0;
	char szTemp[MAX_PATH];
	HRESULT hr=0;

	//First attempt to load the name provided.
	hr=m_TexDB.AddTexture(m_lpDevice, szShader);
	if(SUCCEEDED(hr)){
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	dwLen=strlen(szShader);
	for(i=0, j=0; i<dwLen; i++, j++){
		if(szShader[i]=='.'){
			szTemp[j]=szShader[i];
			szTemp[j+1]=0;	
			break;
		}
		szTemp[j]=szShader[i];		
	}

	//Attempt to replace the extension till we successfully load.
	strcpy(szShader, szTemp);

	strcpy(szTemp, szShader);
	strcat(szTemp, "JPG");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	
	strcpy(szTemp, szShader);
	strcat(szTemp, "BMP");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	strcpy(szTemp, szShader);
	strcat(szTemp, "PNG");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	strcpy(szTemp, szShader);
	strcat(szTemp, "DIB");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	strcpy(szTemp, szShader);
	strcat(szTemp, "DDS");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	strcpy(szTemp, szShader);
	strcat(szTemp, "TGA");
	hr=m_TexDB.AddTexture(m_lpDevice, szTemp);
	if(SUCCEEDED(hr)){
		strcpy(szShader, szTemp);
		RemoveDirectoryFromStringA(szShader, szShader);
		return S_OK;
	}

	return E_FAIL;
}

HRESULT CMD3WeaponMesh::GetLink(CMD3Mesh * lpFirst, char szTagName[], WORD * lpTagRef)
{
	LONG i=0;
	LONG lNumTags=0;
	char szTemp[MAX_QPATH];

	lpFirst->GetNumTags(&lNumTags);

	for(i=1; i<=lNumTags; i++){
		lpFirst->GetTagName(i, szTemp);
		if(_strnicmp(szTemp, szTagName, strlen(szTagName))==0){
			*lpTagRef=(WORD)i;
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT CMD3WeaponMesh::Invalidate()
{
	if(!m_bLoaded)
		return S_FALSE;

	m_meshFlash.Invalidate();
	m_meshHand.Invalidate();
	m_meshWeapon.Invalidate();
	if(m_bBarrel){
		m_meshBarrel.Invalidate();
	}
	return S_OK;
}

HRESULT CMD3WeaponMesh::Validate()
{
	if(!m_bLoaded)
		return S_FALSE;

	m_meshFlash.Validate();
	m_meshHand.Validate();
	m_meshWeapon.Validate();
	if(m_bBarrel){
		m_meshBarrel.Validate();
	}
	return S_OK;
}

HRESULT CMD3WeaponMesh::Render(BOOL bFlash, const D3DMATRIX& SavedWorldMatrix)
{
	DWORD i=0, j=0;
	LONG lNumMesh=0;
	D3DXMATRIX WorldMatrix, Translation, Orientation, Temp;


	if(!m_bLoaded)
		return S_FALSE;

	D3DXMatrixIdentity(&WorldMatrix);
	D3DXMatrixIdentity(&Orientation);


	D3DXMatrixRotationX(&Translation, 1.5f*D3DX_PI);
	Orientation*=Translation;
	D3DXMatrixRotationY(&Translation, 0.5f*D3DX_PI);
	Orientation*=Translation;

	Orientation*=SavedWorldMatrix;
	WorldMatrix*=Orientation;

	m_lpDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);

	//Render the weapon first.
	Temp=WorldMatrix;
	m_meshWeapon.GetTagTranslation(m_nTagWeapon, 0.0f, 0, 0, &Translation);
	WorldMatrix=Translation*WorldMatrix;
	m_lpDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
	m_meshWeapon.GetNumMeshes(&lNumMesh);
	for(i=0; i<(DWORD)lNumMesh; i++){
		m_meshWeapon.RenderWithTexture(
			m_lpWeaponTex[i],
			i+1,
			0.0f,
			0,
			0,
			0);
	}
	WorldMatrix=Temp;

	//Render the barrel if there is one.
	if(m_bBarrel){
		Temp=WorldMatrix;
		m_meshWeapon.GetTagTranslation(m_nTagBarrel, 0.0f, 0, 0, &Translation);
		WorldMatrix=Translation*WorldMatrix;
		m_lpDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
		m_meshBarrel.GetNumMeshes(&lNumMesh);
		for(i=0; i<(DWORD)lNumMesh; i++){
			m_meshBarrel.RenderWithTexture(
				m_lpBarrelTex[i],
				i+1,
				0.0f,
				0,
				0,
				0);
		}
		WorldMatrix=Temp;
	}

	if(bFlash){
		Temp=WorldMatrix;
		m_meshWeapon.GetTagTranslation(m_nTagFlash, 0.0f, 0, 0, &Translation);
		WorldMatrix=Translation*WorldMatrix;
		m_lpDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
		m_meshFlash.GetNumMeshes(&lNumMesh);
		//////////////////////////////////////////
		//NOTICE: Should enable alpha blending.///
		//////////////////////////////////////////
		for(i=0; i<(DWORD)lNumMesh; i++){
			m_meshFlash.RenderWithTexture(
				m_lpFlashTex[i],
				i+1,
				0.0f,
				0,
				0,
				MD3TEXRENDER_NOCULL);
		}
		//Should restore alpha blending values.
		WorldMatrix=Temp;
	}
	
	m_lpDevice->SetTransform(D3DTS_WORLD, &SavedWorldMatrix);
	
	return S_OK;
}