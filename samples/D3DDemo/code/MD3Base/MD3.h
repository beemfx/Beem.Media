/*
	MD3.h - Header for MD3 File Format

	Copyright (c) 2003 Blaine Myers
	Portions Copyright (c) 1999 ID Software
*/

#ifndef __MD3_H__
#define __MD3_H__

#ifdef __cplusplus 
extern "C" {
#endif /* __cplusplus */

#define MD3BASE_EXPORTS

#include "md3file.h"

#ifdef D3D_MD3
#include <d3d9.h>
#include "md3texdb.h"
#endif /* D3D_MD3 */

#if (defined(WIN32) || defined(WIN64))

#include <windows.h>

#else /* (defined(WIN32) || defined(WIN64))*/

typedef float           FLOAT;
typedef int             BOOL;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef signed short    SHORT;
typedef signed long     LONG;

#define FALSE  0
#define TRUE   1

#endif /* (defined(WIN32) || defined(WIN64)) */

/* 
	Skin file structures.
*/
typedef struct tagMD3SKIN{
	char szMeshName[MAX_QPATH];
	char szSkinPath[MAX_PATH];
}MD3SKIN, *LPMD3SKIN;

/*
	Animation definitions types and structures.
*/
typedef enum tagMD3SEX{
	MD3SEX_MALE=0x00000000l,
	MD3SEX_FEMALE,
	MD3SEX_MACHINE,
	MD3SEX_OTHER,
	MD3SEX_DEFAULT
}MD3SEX;

typedef enum tagMD3FOOTSTEP{
	MD3FOOTSTEP_BOOT=0x00000000l,
	MD3FOOTSTEP_ENERGY,
	MD3FOOTSTEP_OTHER,
	MD3FOOTSTEP_DEFAULT
}MD3FOOTSTEP;

typedef struct tagMD3ANIMATION{
	LONG lFirstFrame;
	LONG lNumFrames;
	LONG lLoopingFrames;
	LONG lFramesPerSecond;
}MD3ANIMATION;

/* Animation definitions. */
#define BOTH_DEATH1   0
#define BOTH_DEAD1    1
#define BOTH_DEATH2   2
#define BOTH_DEAD2    3
#define BOTH_DEATH3   4
#define BOTH_DEAD3    5

#define TORSO_GESTURE 6
#define TORSO_ATTACK  7
#define TORSO_ATTACK2 8
#define TORSO_DROP    9
#define TORSO_RAISE   10
#define TORSO_STAND   11
#define TORSO_STAND2  12

#define LEGS_WALKCR   13
#define LEGS_WALK     14
#define LEGS_RUN      15
#define LEGS_BACK     16
#define LEGS_SWIM     17
#define LEGS_JUMP     18
#define LEGS_LAND     19
#define LEGS_JUMPB    20
#define LEGS_LANDB    21
#define LEGS_IDLE     22
#define LEGS_IDLECR   23
#define LEGS_TURN     24

/* The number of MD3 animations (Quake 3 Arena specific). */
#define MD3_NUM_ANIMS 25


/* 
	The following is MD3 implimentation for Direct3D.
*/
#ifdef D3D_MD3

#ifdef __cplusplus
class MD3BASE_EXPORTS CMD3Mesh;
class MD3BASE_EXPORTS CMD3TextureDB;
class MD3BASE_EXPORTS CMD3SkinFile;
class MD3BASE_EXPORTS CMD3ObjectMesh;
class MD3BASE_EXPORTS CMD3WeaponMesh;
#endif /* __cplusplus */

/*
	The MD3 vertex format.
*/
#define D3DMD3VERTEX_TYPE (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

typedef struct tagD3DMD3VERTEX{
	D3DVECTOR Postion; /* Position of vertex. */
	D3DVECTOR Normal; /* The normal of the vertex. */
	FLOAT tu, tv; /* Texture coordinates. */
}D3DMD3VERTEX, *LPD3DMD3VERTEX;


/*
	The Direct3DMD3 functionality.
*/

#ifdef __cplusplus

#ifdef UNICODE
#define LoadMD3 LoadMD3W
#else /* UNICODE */
#define LoadMD3 LoadMD3A
#endif /* UNICODE */

#define MD3TEXRENDER_NOCULL 0x00000001l

class MD3BASE_EXPORTS CMD3Mesh
{
protected:
	MD3FILE m_md3File;

	LPDIRECT3DVERTEXBUFFER9 * m_lppVB;
	D3DMD3VERTEX * m_lpVertices;
	LPDIRECT3DINDEXBUFFER9 * m_lppIB;

	LPDIRECT3DDEVICE9 m_lpDevice;

	MD3VECTOR ** m_lppNormals;

	BOOL m_bMD3Loaded; /* Whether or not MD3 is loaded. */
	BOOL m_bValid; /* Whether or not the MD3 is valid for D3D usage. */
	DWORD m_dwNumSkins; /* Total number of skins in the mesh. */
	D3DPOOL m_Pool; /* The Pool Direct3D objects should be created in. */

	HRESULT CreateVB();
	HRESULT DeleteVB();

	HRESULT CreateIB();
	HRESULT DeleteIB();

	HRESULT CreateNormals();

	HRESULT CreateModel();
	HRESULT DeleteModel();

public:
	CMD3Mesh();
	~CMD3Mesh();

	HRESULT LoadMD3A(
		char szFilename[MAX_PATH], 
		LPDWORD lpBytesRead, 
		LPDIRECT3DDEVICE9 lpDevice,
		D3DPOOL Pool);
	HRESULT LoadMD3W(
		WCHAR szFilename[MAX_PATH], 
		LPDWORD lpBytesRead, 
		LPDIRECT3DDEVICE9 lpDevice,
		D3DPOOL Pool);

	HRESULT ClearMD3();

	HRESULT Render(
		CMD3SkinFile * lpSkin,
		FLOAT fTime,
		LONG lFirstFrame,
		LONG lNextFrame,
		DWORD dwFlags);

	HRESULT RenderWithTexture(
		LPDIRECT3DTEXTURE9 lpTexture,
		LONG lMesh,
		FLOAT fTime,
		LONG lFirstFrame,
		LONG lNextFrame,
		DWORD dwFlags);

	HRESULT Invalidate();
	HRESULT Validate();

	HRESULT SetSkinRefs(
		CMD3SkinFile * lpSkin);

	HRESULT GetTagTranslation(
		DWORD dwTagRef,
		FLOAT fTime,
		LONG dwFirstFrame,
		LONG dwSecondFrame,
		D3DMATRIX * Translation);

	HRESULT GetNumTags(
		LONG * lpNumTags);
	HRESULT GetTagName(
		LONG lRef,
		char szTagName[MAX_QPATH]);
	HRESULT GetShader(
		LONG lMesh,
		LONG lShader,
		char szShaderName[MAX_QPATH],
		LONG * lpShaderNum);

	HRESULT GetNumMeshes(
		LONG * lpNumMeshes);

	HRESULT DumpDebug();

};

#endif /* __cplusplus */



/*
	The texture database functionality.
*/

#ifdef __cplusplus

/* CMD3TextureDB is not UNICODE compatible. */
class MD3BASE_EXPORTS CMD3TextureDB
{
protected:
	CMD3Texture * m_lpFirst;
	DWORD m_dwNumTextures;
public:
	CMD3TextureDB();
	~CMD3TextureDB();

	HRESULT GetNumTextures(DWORD * dwNumTex);

	HRESULT AddTexture(LPDIRECT3DDEVICE9 lpDevice, char szTexName[]);
	HRESULT AddTexture(LPDIRECT3DTEXTURE9 lpTexture, char szTexName[]);
	
	HRESULT GetTexture(DWORD dwRef, LPDIRECT3DTEXTURE9 * lppTexture);
	HRESULT GetTexture(char szTexName[], LPDIRECT3DTEXTURE9 * lppTexture);
	
	HRESULT SetRenderTexture(DWORD dwRef, DWORD dwStage, LPDIRECT3DDEVICE9 lpDevice);
	HRESULT SetRenderTexture(LPSTR szTexName, DWORD dwStage, LPDIRECT3DDEVICE9 lpDevice);
	
	HRESULT DeleteTexture(DWORD dwRef);
	HRESULT DeleteTexture(LPSTR szTexName);

	HRESULT ClearDB();
};

#endif /* __cplusplus */

/*
	The MD3 Skin file functionality.
*/
#ifdef __cplusplus

#ifdef UNICODE
#define LoadSkin LoadSkinW
#else /* UNICODE */
#define LoadSkin LoadSkinA
#endif /* UNICODE */

#define MD3SKINCREATE_REMOVEDIR    0x00000001l
#define MD3SKINCREATE_STATICTEXDB  0x00000002l
#define MD3SKINCREATE_DYNAMICTEXDB 0x00000004l

#define S_SKINNULL 0x00000002l

class MD3BASE_EXPORTS CMD3SkinFile
{
public:
	CMD3SkinFile();
	~CMD3SkinFile();

	HRESULT LoadSkinA(
		LPDIRECT3DDEVICE9 lpDevice,
		char szFilename[MAX_PATH],
		DWORD dwFlags,
		LPVOID lpTexDB);

	HRESULT LoadSkinW(
		LPDIRECT3DDEVICE9 lpDevice,
		WCHAR szFilename[MAX_PATH],
		DWORD dwFlags,
		LPVOID lpTexDB);

	HRESULT GetTexturePointer(
		DWORD dwRef,
		LPDIRECT3DTEXTURE9 * lppTexture);

	HRESULT SetRenderTexture(
		DWORD dwRef, 
		LPDIRECT3DDEVICE9 lpDevice);

	HRESULT UnloadSkin();

	HRESULT SetSkin(
		LPDIRECT3DDEVICE9 lpDevice, 
		DWORD dwRef);

	HRESULT SetSkinRef(
		char szName[], 
		DWORD dwRef);

	static HRESULT ClearTexDB();
protected:
	HRESULT CreateSkinFile(DWORD dwNumSkins);
	HRESULT DeleteSkinFile();

	HRESULT ObtainTextures(LPDIRECT3DDEVICE9 lpDevice, char szTexPath[], DWORD dwFlags, LPVOID lpTexDB);
	
	HRESULT ReadSkins(HANDLE hFile, DWORD dwNumSkinsToRead, DWORD * dwNumSkinsRead, DWORD dwFlags);

	BOOL ParseLine(MD3SKIN *, LPSTR);

	/* Member variables. */

	MD3SKIN * m_lpSkins; /* The MD3 skins. */
	DWORD * m_lpSkinRef; /* Which skin is which reference. */
	BOOL m_bRefsSet; /* Whether or not references are set. */
	DWORD m_dwNumSkins; /* Number of skins in this file. */
	BOOL m_bLoaded; /* Whether or not a skin file is loaded. */

	BOOL m_bUseStaticDB; /* Whether or not to use static texture DB. */
	static CMD3TextureDB m_md3TexDB; /* The MD3 skin texture database. */

	LPDIRECT3DTEXTURE9 * m_lppTextures; /* Pointers to the textures used by this file. */
};

#endif /* __cplusplus */

/*
	The animation class.  Methodes for compiling and
	obtaining info from animation.cfg files for MD3.
*/
#ifdef __cplusplus


#ifdef UNICODE 
#define LoadAnimation LoadAnimationW
#else /* UNICODE */
#define LoadAnimation LoadAnimationA
#endif /* UNICODE */

#define MD3ANIM_ADJUST 0x00000001l

class MD3BASE_EXPORTS CMD3Animation
{
protected:
	MD3SEX m_nSex;
	MD3FOOTSTEP m_nFootStep;
	SHORT m_nHeadOffset[3];
	LONG m_lLegOffset;
	MD3ANIMATION m_Animations[MD3_NUM_ANIMS];

	HRESULT ReadAnimations(HANDLE hFile, DWORD dwNumLines);
	HRESULT ParseLine(LPVOID lpDataOut, LPSTR szLineIn, DWORD * lpAnimRef);

public:
	CMD3Animation();
	~CMD3Animation();

	HRESULT LoadAnimationA(char szFilename[]);
	HRESULT LoadAnimationW(WCHAR szFilename[]);

	HRESULT GetAnimation(DWORD dwRef, MD3ANIMATION * lpAnimation, DWORD dwFlags);
};

#endif /* __cplusplus */


/* The player mesh functionality. */

#ifdef __cplusplus

typedef enum tagMD3DETAIL{
	DETAIL_HIGH=0x00000000l,
	DETAIL_MEDIUM,
	DETAIL_LOW
}MD3DETAIL;

#define SKIN_DEFAULT 0

class MD3BASE_EXPORTS CMD3PlayerMesh
{
protected:
	CMD3Mesh m_meshHead;
	CMD3SkinFile * m_skinHead;

	CMD3Mesh m_meshUpper;
	CMD3SkinFile * m_skinUpper;

	CMD3Mesh m_meshLower;
	CMD3SkinFile * m_skinLower;

	CMD3Animation m_Animation;

	CMD3TextureDB m_TexDB;

	WORD m_nLowerUpperTag;
	WORD m_nUpperHeadTag;
	WORD m_nUpperWeaponTag;

	DWORD m_dwNumSkins;
	DWORD m_dwDefaultSkin;
	char ** m_szSkinName;

	LPDIRECT3DDEVICE9 m_lpDevice;

	BOOL m_bLoaded;

	HRESULT GetLink(CMD3Mesh * lpFirst, char szTagName[], WORD * lpTagRef);

	HRESULT GetSkinsA(char szDir[]);
	HRESULT GetSkinsW(WCHAR szDir[]);
public:
	CMD3PlayerMesh();
	~CMD3PlayerMesh();

	HRESULT GetAnimation(DWORD dwAnimRef, MD3ANIMATION * lpAnimation);

	HRESULT GetSkinRef(DWORD * lpRef, char szSkinName[]);


	HRESULT Render(
		LONG lUpperFirstFrame, 
		LONG lUpperSecondFrame, 
		FLOAT fUpperTime,
		LONG lLowerFirstFrame,
		LONG lLowerSecondFrame,
		FLOAT fLowerTime,
		DWORD dwSkinRef,
		CMD3WeaponMesh * lpWeapon,
		const D3DMATRIX& SavedWorldMatrix);

	HRESULT LoadA(LPDIRECT3DDEVICE9 lpDevice, char szDir[], MD3DETAIL nDetail);
	HRESULT LoadW(LPDIRECT3DDEVICE9 lpDevice, WCHAR szDir[], MD3DETAIL nDetail);

	HRESULT Clear();

	HRESULT Invalidate();
	HRESULT Validate();
};
#endif /* __cplusplus */

/*
	The player object manages animations.
*/
#ifdef __cplusplus
/* The flags for the SetAnimation function. */
#define MD3SETANIM_WAIT      0x00000010l /* Wait for the current animation to finish. */
#define MD3SETANIM_FRAME     0x00000020l /* Wait for the next key-frame. */
#define MD3SETANIM_FORCELOOP 0x00000040l

typedef enum tagFRAMETRANSITIONTYPE{
	TRANSITION_NONE=0x00000000l,
	TRANSITION_WAITFORANIMATION,
	TRANSITION_WAITFORKEYFRAME,
	TRANSITION_FRAMETRANSITION,
}FRAMETRANSITIONTYPE;


#define MD3APPLYANIM_UPPER 0x00000001l
#define MD3APPLYANIM_LOWER 0x00000002l

class MD3BASE_EXPORTS CMD3PlayerObject
{
protected:
	CMD3PlayerMesh * m_lpPlayerMesh; /* Pointer to the player mesh. */
	DWORD m_dwLastCycleTimeLower; /* The last time the lower cycle was completed. */
	DWORD m_dwLastCycleTimeUpper; /* The last time the upper cycle was completed. */

	FLOAT m_fFPSUpper; /* Speed adjust for the upper animation. */
	FLOAT m_fFPSLower; /* Speed adjust for the lower animation. */

	DWORD m_dwSkinRef; /* The current skin reference. */

	DWORD m_dwUpperAnim; /* The reference for the torso animation. */
	MD3ANIMATION m_AnimationUpper; /* The data for the torso animation. */
	DWORD m_dwLowerAnim; /* The reference for the legs animation. */
	MD3ANIMATION m_AnimationLower; /* The data for the legs animation. */

	CMD3WeaponMesh * m_lpWeapon;

	FRAMETRANSITIONTYPE m_LowerTransition;
	FRAMETRANSITIONTYPE m_UpperTransition;

	LONG m_lPrevFrameUpper;
	LONG m_lPrevFrameLower;

	DWORD m_dwAnimNextLower;
	DWORD m_dwAnimNextUpper;

	DWORD m_dwAnimPrevLower;
	DWORD m_dwAnimPrevUpper;

	FLOAT m_fAnimSpeedNextLower;
	FLOAT m_fAnimSpeedNextUpper;

	LONG m_lCurrentFrameLower;
	LONG m_lCurrentFrameUpper;

	LONG m_lLastSecondFrameLower;
	LONG m_lLastSecondFrameUpper;

	DWORD m_dwTransitionCycle;

	__inline HRESULT FrameTransitionAdjust(
		FRAMETRANSITIONTYPE * lpTransition,
		MD3ANIMATION * lpAnimation,
		LONG * lpFirstFrame,
		LONG * lpSecondFrame,
		FLOAT * lpTime,
		LONG * lpPrevFrame,
		DWORD * dwLastCycleTime,
		DWORD dwCycleTime,
		DWORD dwFirstAnim,
		DWORD dwSecondAnim,
		FLOAT fSpeed,
		BOOL bDone,
		DWORD dwFlags);


	HRESULT GetFrames(
		LONG * lpFirstFrame, 
		LONG * lpSecondFrame,
		FLOAT * lpTime,
		DWORD dwTimeElapsed,
		DWORD dwFrameTime,
		const MD3ANIMATION Animation); /* Gets the correct frame and time data for animation. */

	HRESULT ApplyAnimation(
		DWORD dwAnimRef,
		FLOAT fSpeed,
		DWORD dwFlags);
public:
	CMD3PlayerObject(); /* Constructor. */
	~CMD3PlayerObject(); /* Destructor. */

	HRESULT SetAnimation(DWORD dwAnimRef, DWORD dwFlags, FLOAT fSpeed); /* Sets the current animation. */
	HRESULT GetAnimation(DWORD * lpUpper, DWORD * lpLower); /* Gets the animation. */

	HRESULT SetPlayerMesh(CMD3PlayerMesh * lpPlayerMesh); /* Sets the current player mesh. */

	/* Should remove weapon from render and have a setweapon option. */
	HRESULT Render( const D3DMATRIX& WorldMatrix ); /* Renders the mesh with appropriate animation. */

	HRESULT SetSkinByRef(DWORD dwSkinRef); /* Sets the skin. */
	HRESULT SetSkinByName(char szSkinName[MAX_QPATH]); /* Sets the skin based on it's name. */

	HRESULT SetWeapon(CMD3WeaponMesh * lpWeapon);
};
#endif /* __cplusplus */

/*
	The Weapon Mesh Class.
*/

#ifdef __cplusplus
class MD3BASE_EXPORTS CMD3WeaponMesh
{
protected:
	CMD3Mesh m_meshWeapon;
	CMD3Mesh m_meshBarrel;
	CMD3Mesh m_meshFlash;
	CMD3Mesh m_meshHand;

	CMD3TextureDB m_TexDB;

	LPDIRECT3DTEXTURE9 * m_lpFlashTex;
	LPDIRECT3DTEXTURE9 * m_lpWeaponTex;
	LPDIRECT3DTEXTURE9 * m_lpBarrelTex;

	LPDIRECT3DDEVICE9 m_lpDevice;

	BOOL m_bBarrel;

	WORD m_nTagWeapon;
	WORD m_nTagBarrel;
	WORD m_nTagFlash;

	BOOL m_bLoaded;

	HRESULT GetLink(CMD3Mesh * lpFirst, char szTagName[], WORD * lpTagRef);
	HRESULT TextureExtension(char szShader[MAX_PATH]);

public:
	CMD3WeaponMesh();
	~CMD3WeaponMesh();

	HRESULT Clear();

	HRESULT Render(BOOL bFlash, const D3DMATRIX& WorldMatrix);

	HRESULT Load(LPDIRECT3DDEVICE9 lpDevice, char szDir[], MD3DETAIL nDetail);
	HRESULT Invalidate();
	HRESULT Validate();
};
#endif /* __cplusplus */





/*
	The Custom Mesh class.
*/
#ifdef __cplusplus

class MD3BASE_EXPORTS CMD3ObjectMesh
{
protected:
	CMD3Mesh m_meshObject;
	CMD3TextureDB m_TexDB;
	LPDIRECT3DTEXTURE9 * m_lppObjTex;

	BOOL m_bLoaded;

	HRESULT TextureExtension(LPDIRECT3DDEVICE9 lpDevice, char szShader[MAX_PATH]);
public:
	CMD3ObjectMesh();
	~CMD3ObjectMesh();

	HRESULT Render(LPDIRECT3DDEVICE9 lpDevice , const D3DMATRIX& WorldMatrix );

	HRESULT Load(LPDIRECT3DDEVICE9 lpDevice, char szFile[], MD3DETAIL nDetail);

	HRESULT Clear();

	HRESULT Invalidate();
	HRESULT Validate(LPDIRECT3DDEVICE9 lpDevice);
};
#endif /* __cplusplus */

#endif /* D3D_MD3 */

#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif /* __MD3_H__ */
