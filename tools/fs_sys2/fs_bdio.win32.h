/* NOTE: The bdio functions should be altered according to the operating
	system that the fs_sys2 library is being compiled for, this file
	is designed for windows operating systems (in all practicality the
	fopen, fclose, etc stdc functions could have been used, but the
	windows methods prove more stable for windows computers.
*/

#include <windows.h>
#include "fs_bdio.h"

/* Basic DIO stuff, should only be used internally only. */

BDIO_FILE BDIO_OpenA(fs_cstr8 szFilename, LF_CREATE_MODE nMode, fs_dword nAccess)
{
	HANDLE hFile=INVALID_HANDLE_VALUE;
	fs_dword dwDesiredAccess=0;
	fs_dword dwCreateDisposition=0;
	fs_dword dwFlagsAndAttributes=0;

	if(sizeof(BDIO_FILE) != sizeof(HANDLE))
	{
		__debugbreak();
		return 0;
	}

	dwDesiredAccess|=FS_CheckFlag(nAccess, LF_ACCESS_READ)?GENERIC_READ:0;
	dwDesiredAccess|=FS_CheckFlag(nAccess, LF_ACCESS_WRITE)?GENERIC_WRITE:0;
		
	switch(nMode)
	{
	case LF_CREATE_ALWAYS:
		dwCreateDisposition=CREATE_ALWAYS;
		break;
	case LF_CREATE_NEW:
		dwCreateDisposition=CREATE_NEW;
		break;
	case LF_OPEN_ALWAYS:
		dwCreateDisposition=OPEN_ALWAYS;
		break;
	case LF_OPEN_EXISTING:
		dwCreateDisposition=OPEN_EXISTING;
		break;
	}
	
	dwFlagsAndAttributes=FILE_ATTRIBUTE_NORMAL;
	if(FS_CheckFlag(nAccess, LF_ACCESS_BDIO_TEMP))
	{
		dwFlagsAndAttributes=FILE_FLAG_DELETE_ON_CLOSE|FILE_ATTRIBUTE_TEMPORARY;
	}
	
	hFile=CreateFileA(
		szFilename, 
		dwDesiredAccess,
		FILE_SHARE_READ,
		NULL,
		dwCreateDisposition,
		dwFlagsAndAttributes,
		NULL);
		
	if(hFile==INVALID_HANDLE_VALUE)
	{
		hFile = 0;
	}
	return (BDIO_FILE)(hFile);
}
BDIO_FILE BDIO_OpenW(fs_cstr16 szFilename, LF_CREATE_MODE nMode, fs_dword nAccess)
{
	HANDLE hFile=INVALID_HANDLE_VALUE;
	fs_dword dwDesiredAccess=0;
	fs_dword dwCreateDisposition=0;
	fs_dword dwFlagsAndAttributes=0;

	if(sizeof(BDIO_FILE) != sizeof(HANDLE))
	{
		__debugbreak();
		return 0;
	}

	dwDesiredAccess|=FS_CheckFlag(nAccess, LF_ACCESS_READ)?GENERIC_READ:0;
	dwDesiredAccess|=FS_CheckFlag(nAccess, LF_ACCESS_WRITE)?GENERIC_WRITE:0;
	
	switch(nMode)
	{
	case LF_CREATE_ALWAYS:
		dwCreateDisposition=CREATE_ALWAYS;
		break;
	case LF_CREATE_NEW:
		dwCreateDisposition=CREATE_NEW;
		break;
	case LF_OPEN_ALWAYS:
		dwCreateDisposition=OPEN_ALWAYS;
		break;
	case LF_OPEN_EXISTING:
		dwCreateDisposition=OPEN_EXISTING;
		break;
	}
	
	dwFlagsAndAttributes=FILE_ATTRIBUTE_NORMAL;
	if(FS_CheckFlag(nAccess, LF_ACCESS_BDIO_TEMP))
	{
		dwFlagsAndAttributes=FILE_FLAG_DELETE_ON_CLOSE|FILE_ATTRIBUTE_TEMPORARY;
	}
	
	hFile=CreateFileW(
		szFilename, 
		dwDesiredAccess,
		FILE_SHARE_READ,
		NULL,
		dwCreateDisposition,
		dwFlagsAndAttributes,
		NULL);
		
	if(hFile==INVALID_HANDLE_VALUE)
	{
		hFile = 0;
	}
	return (BDIO_FILE)(hFile);
}
fs_bool BDIO_Close(BDIO_FILE File)
{
	HANDLE hFile=(HANDLE)(File);
	fs_bool bResult=CloseHandle(hFile);
	return bResult;
}

fs_dword BDIO_Read(BDIO_FILE File, fs_dword nSize, void* pOutBuffer)
{
	HANDLE hFile=(HANDLE)(File);
	fs_dword dwRead=0;
	if(ReadFile(hFile, pOutBuffer, nSize, &dwRead, NULL))
		return dwRead;
	else
		return 0;
}


fs_dword BDIO_Write(BDIO_FILE File, fs_dword nSize, const void* pInBuffer)
{
	HANDLE hFile=(HANDLE)(File);
	fs_dword dwWrote=0;
	if(WriteFile(hFile, pInBuffer, nSize, &dwWrote, NULL))
		return dwWrote;
	else
		return 0;
}

fs_dword BDIO_Tell(BDIO_FILE File)
{
	HANDLE hFile=(HANDLE)(File);
	return SetFilePointer(
		hFile,
		0,
		NULL,
		FILE_CURRENT);
}

fs_dword BDIO_Seek(BDIO_FILE File, fs_long nOffset, LF_SEEK_TYPE nOrigin)
{
	HANDLE hFile=(HANDLE)(File);
	fs_dword dwMoveMethod=0;
	switch(nOrigin)
	{
	case LF_SEEK_BEGIN:
		dwMoveMethod=FILE_BEGIN;
		break;
	case LF_SEEK_CURRENT:
		dwMoveMethod=FILE_CURRENT;
		break;
	case LF_SEEK_END:
		dwMoveMethod=FILE_END;
		break;
	}
	return SetFilePointer(hFile,nOffset,NULL,dwMoveMethod);
}

fs_dword BDIO_GetSize(BDIO_FILE File)
{
	HANDLE hFile=(HANDLE)(File);
	fs_large_integer nFileSize={0,0};
	nFileSize.dwLowPart=GetFileSize(hFile, &nFileSize.dwHighPart);
	if(nFileSize.dwHighPart)
		return 0xFFFFFFFF;
	else
		return nFileSize.dwLowPart;
}

BDIO_FILE BDIO_OpenTempFileA(LF_CREATE_MODE nMode, fs_dword nAccess)
{
	fs_pathA szTempPath, szTempFile;
	GetTempPathA(FS_MAX_PATH, szTempPath);
	GetTempFileNameA(szTempPath, "BDIO", 0, szTempFile);
	return BDIO_OpenA(szTempFile, nMode, nAccess|LF_ACCESS_BDIO_TEMP);
}
BDIO_FILE BDIO_OpenTempFileW(LF_CREATE_MODE nMode, fs_dword nAccess)
{
	fs_pathW szTempPath, szTempFile;
	GetTempPathW(FS_MAX_PATH, szTempPath);
	GetTempFileNameW(szTempPath, L"BDIO", 0, szTempFile);
	return BDIO_OpenW(szTempFile, nMode, nAccess|LF_ACCESS_BDIO_TEMP);
}

/* Directory manipulation...*/

fs_bool BDIO_ChangeDirA(fs_cstr8 szDir)
{
	return SetCurrentDirectoryA(szDir);
}
fs_bool BDIO_ChangeDirW(fs_cstr16 szDir)
{
	return SetCurrentDirectoryW(szDir);
}

fs_dword BDIO_GetCurrentDirA(fs_str8 szDir, fs_dword nSize)
{
	return GetCurrentDirectoryA(nSize, szDir);
}
fs_dword BDIO_GetCurrentDirW(fs_str16 szDir, fs_dword nSize)
{
	return GetCurrentDirectoryW(nSize, szDir);
}

/* BDIO_GetFullPathname converts a filename to it's full path according to the 
	current directory
*/
fs_dword BDIO_GetFullPathNameW(fs_pathW szPath, const fs_pathW szFilename)
{
	return GetFullPathNameW(szFilename, FS_MAX_PATH, szPath, NULL);
}
fs_dword BDIO_GetFullPathNameA(fs_pathA szPath, const fs_pathA szFilename)
{
	return GetFullPathNameA(szFilename, FS_MAX_PATH, szPath, NULL);;
}

//Find File functions for finding all files in a directory.
BDIO_FIND BDIO_FindFirstFileW(fs_cstr16 szFilename, BDIO_FIND_DATAW* pFindData)
{
	HANDLE hFindFile;
	WIN32_FIND_DATAW findData;
	
	hFindFile=FindFirstFileW(szFilename, &findData);
	if(INVALID_HANDLE_VALUE==hFindFile)
		return FS_NULL;
	
	pFindData->nFileSize.dwHighPart=findData.nFileSizeHigh;
	pFindData->nFileSize.dwLowPart=findData.nFileSizeLow;
	wcsncpy(pFindData->szFilename, findData.cFileName, FS_MAX_PATH);
	pFindData->bNormal=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_NORMAL);
	pFindData->bDirectory=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
	pFindData->bHidden=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_HIDDEN);
	pFindData->bReadOnly=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_READONLY);
	return hFindFile;
}
fs_bool BDIO_FindNextFileW(BDIO_FIND hFindFile, BDIO_FIND_DATAW* pFindData)
{
	WIN32_FIND_DATAW findData;
	fs_bool bResult=FindNextFileW((HANDLE)hFindFile, &findData);
	if(!bResult)
		return bResult;
	
	pFindData->nFileSize.dwHighPart=findData.nFileSizeHigh;
	pFindData->nFileSize.dwLowPart=findData.nFileSizeLow;
	wcsncpy(pFindData->szFilename, findData.cFileName, FS_MAX_PATH);
	pFindData->bNormal=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_NORMAL);
	pFindData->bDirectory=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
	pFindData->bHidden=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_HIDDEN);
	pFindData->bReadOnly=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_READONLY);
	return bResult;
}


BDIO_FIND BDIO_FindFirstFileA(fs_cstr8 szFilename, BDIO_FIND_DATAA* pFindData)
{
	HANDLE hFindFile;
	WIN32_FIND_DATAA findData;
	
	hFindFile=FindFirstFileA(szFilename, &findData);
	if(INVALID_HANDLE_VALUE==hFindFile)
		return FS_NULL;
	
	pFindData->nFileSize.dwHighPart=findData.nFileSizeHigh;
	pFindData->nFileSize.dwLowPart=findData.nFileSizeLow;
	strncpy(pFindData->szFilename, findData.cFileName, FS_MAX_PATH);
	pFindData->bNormal=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_NORMAL);
	pFindData->bDirectory=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
	pFindData->bHidden=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_HIDDEN);
	pFindData->bReadOnly=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_READONLY);
	return hFindFile;
}
fs_bool BDIO_FindNextFileA(BDIO_FIND hFindFile, BDIO_FIND_DATAA* pFindData)
{
	WIN32_FIND_DATAA findData;
	fs_bool bResult=FindNextFileA((HANDLE)hFindFile, &findData);
	if(!bResult)
		return bResult;
	
	pFindData->nFileSize.dwHighPart=findData.nFileSizeHigh;
	pFindData->nFileSize.dwLowPart=findData.nFileSizeLow;
	strncpy(pFindData->szFilename, findData.cFileName, FS_MAX_PATH);
	pFindData->bNormal=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_NORMAL);
	pFindData->bDirectory=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
	pFindData->bHidden=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_HIDDEN);
	pFindData->bReadOnly=FS_CheckFlag(findData.dwFileAttributes, FILE_ATTRIBUTE_READONLY);
	return bResult;
}

fs_bool BDIO_FindClose(BDIO_FIND hFindFile)
{
	return FindClose((HANDLE)hFindFile);
}

fs_char8 BDIO_GetOsPathSeparator()
{
	return '\\';
}