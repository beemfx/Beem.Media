#include <string.h>
#include <ctype.h>
#include "fs_sys2.h"

/***************************************************
	Pathname getting functions, retrieve filename
	path, or short filename from a full path
***************************************************/
fs_str8 FS_GetFileNameFromPathA(fs_str8 szFileName, fs_cstr8 szFullPath)
{
	fs_dword dwLen=strlen(szFullPath);
	fs_dword i=0, j=0;
	
	for(i=dwLen; i>0; i--)
	{
		if(szFullPath[i]=='\\' || szFullPath[i]=='/')
		{
			i++;
			break;
		}
	}
	for(j=0 ;i<dwLen+1; i++, j++)
	{
		szFileName[j]=szFullPath[i];
	}
	return szFileName;
}

fs_str16 FS_GetFileNameFromPathW(fs_str16 szFileName, fs_cstr16 szFullPath)
{
	fs_dword dwLen=wcslen(szFullPath);
	fs_dword i=0, j=0;
	
	for(i=dwLen; i>0; i--)
	{
		if(szFullPath[i]=='\\' || szFullPath[i]=='/')
		{
			i++;
			break;
		}
	}
	for(j=0 ;i<dwLen+1; i++, j++)
	{
		szFileName[j]=szFullPath[i];
	}
	return szFileName;
}

fs_str8 FS_GetDirFromPathA(fs_str8 szDir, fs_cstr8 szFullPath)
{
	fs_dword dwLen=strlen(szFullPath);
	fs_long i=0;
	for(i=(fs_long)dwLen-1; i>=0; i--)
	{
		if(szFullPath[i]=='\\' || szFullPath[i]=='/')
			break;
	}
	strncpy(szDir, szFullPath, i+1);
	szDir[i+1]=0;
	return szDir;
}

fs_str16 FS_GetDirFromPathW(fs_str16 szDir, fs_cstr16 szFullPath)
{
	fs_dword dwLen=wcslen(szFullPath);
	fs_long i=0;
	for(i=(fs_long)dwLen-1; i>=0; i--)
	{
		if(szFullPath[i]=='\\' || szFullPath[i]=='/')
			break;
	}
	wcsncpy(szDir, szFullPath, i+1);
	szDir[i+1]=0;
	return szDir;
}

void FS_SYS2_EXPORTS FS_FixCaseA(fs_pathA szOut, fs_cstr8 szFullPath)
{
	fs_long i = 0;
	for(i=0; i<FS_MAX_PATH; i++)
	{
		szOut[i] = tolower(szFullPath[i]);
		if(0 == szOut[i])break;
	}
	szOut[FS_MAX_PATH] = 0;
}

void FS_SYS2_EXPORTS FS_FixCaseW(fs_pathW szOut, fs_cstr16 szFullPath)
{
	fs_long i = 0;
	for(i=0; i<FS_MAX_PATH; i++)
	{
		szOut[i] = tolower(szFullPath[i]);
		if(0 == szOut[i])break;
	}
	szOut[FS_MAX_PATH] = 0;
}