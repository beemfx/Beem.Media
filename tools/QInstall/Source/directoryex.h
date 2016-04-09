/*
	Directory.h - Header for directory functions

	Copyright (c) 2003, Blaine Myers
*/
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__
#include <windows.h>

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

HRESULT CopyDirectory(LPCTSTR szSource, LPCTSTR szDest, DWORD dwFileAttributes);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__DIRECTORY_H__