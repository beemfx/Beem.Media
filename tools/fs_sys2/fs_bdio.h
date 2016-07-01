#ifndef _FS_BDIO_H__
#define _FS_BDIO_H__
#include "fs_sys2.h"

#ifdef __cplusplus
extern "C"{
#endif __cplusplus

/* Basic DIO stuff, should only be used internally only. */
static fs_bool FS_CheckFlag(fs_dword flag, fs_dword var){ return ((flag&var) != 0); }

static const fs_dword LF_ACCESS_BDIO_TEMP = (1 << 5);

typedef fs_intptr_t BDIO_FILE;
BDIO_FILE BDIO_OpenA(fs_cstr8 szFilename, LF_CREATE_MODE nMode, fs_dword nAccess);
BDIO_FILE BDIO_OpenW(fs_cstr16 szFilename, LF_CREATE_MODE nMode, fs_dword nAccess);

fs_bool   BDIO_Close(BDIO_FILE File);
fs_dword  BDIO_Read(BDIO_FILE File, fs_dword nSize, void* pOutBuffer);
fs_dword  BDIO_Write(BDIO_FILE File, fs_dword nSize, const void* pInBuffer);
fs_dword  BDIO_Tell(BDIO_FILE File);
fs_dword  BDIO_Seek(BDIO_FILE File, fs_long nOffset, LF_SEEK_TYPE nOrigin);
fs_dword  BDIO_GetSize(BDIO_FILE File);
			 
fs_dword  BDIO_WriteCompressed(BDIO_FILE File, fs_dword nSize, void* pInBuffer);
fs_dword  BDIO_ReadCompressed(BDIO_FILE File, fs_dword nSize, void* pOutBuffer);
			 
fs_bool   BDIO_ChangeDirA(fs_cstr8 szDir);
fs_bool   BDIO_ChangeDirW(fs_cstr16 szDir);
fs_dword  BDIO_GetCurrentDirA(fs_str8 szDir, fs_dword nSize);
fs_dword  BDIO_GetCurrentDirW(fs_str16 szDir, fs_dword nSize);

BDIO_FILE BDIO_OpenTempFileA(LF_CREATE_MODE nMode, fs_dword nAccess);
BDIO_FILE BDIO_OpenTempFileW(LF_CREATE_MODE nMode, fs_dword nAccess);

fs_dword  BDIO_CopyData(BDIO_FILE DestFile, BDIO_FILE SourceFile, fs_dword nSize);

fs_dword  BDIO_GetFullPathNameW(fs_pathW szPath, const fs_pathW szFilename);
fs_dword  BDIO_GetFullPathNameA(fs_pathA szPath, const fs_pathA szFilename);

typedef void* BDIO_FIND;

typedef struct _BDIO_FIND_DATAW{
	fs_bool bDirectory;
	fs_bool bReadOnly;
	fs_bool bHidden;
	fs_bool bNormal;
	fs_large_integer nFileSize;
	fs_pathW szFilename;
}BDIO_FIND_DATAW;

typedef struct _BDIO_FIND_DATAA{
	fs_bool bDirectory;
	fs_bool bReadOnly;
	fs_bool bHidden;
	fs_bool bNormal;
	fs_large_integer nFileSize;
	fs_pathA szFilename;
}BDIO_FIND_DATAA;

BDIO_FIND BDIO_FindFirstFileW(fs_cstr16 szFilename, BDIO_FIND_DATAW* pFindData);
fs_bool   BDIO_FindNextFileW(BDIO_FIND hFindFile, BDIO_FIND_DATAW* pFindData);
BDIO_FIND BDIO_FindFirstFileA(fs_cstr8 szFilename, BDIO_FIND_DATAA* pFindData);
fs_bool   BDIO_FindNextFileA(BDIO_FIND hFindFile, BDIO_FIND_DATAA* pFindData);
fs_bool   BDIO_FindClose(BDIO_FIND hFindFile);

fs_char8 BDIO_GetOsPathSeparator();

#ifdef __cplusplus
}
#endif __cplusplus

#endif _FS_BDIO_H__