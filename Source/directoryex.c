/*
	Directory.c - CopyDirectory Commands.

	Copyright (c) 2003, Blaine Myers
*/

#include <stdio.h>
#include "directoryex.h"

HRESULT CopyDirectory(LPCTSTR szSource, LPCTSTR szDest, DWORD dwFileAttributes)
{
	TCHAR strCommand[MAX_PATH*2 + 100];
	STARTUPINFO SI;
	PROCESS_INFORMATION PI;
	BOOL bSuccess;

	sprintf(strCommand, TEXT("xcopy /Y /E /I /H \"%s\" \"%s\""), szSource, szDest);

	memset(&SI, 0, sizeof(SI));
	memset(&PI, 0, sizeof(PI));

	SI.dwFlags = STARTF_USESHOWWINDOW;
	SI.wShowWindow = SW_HIDE;
	bSuccess = CreateProcess(NULL, strCommand, NULL, NULL, FALSE, 0, NULL, NULL, &SI, &PI);

	WaitForSingleObject(PI.hProcess, INFINITE);

	return S_OK;
}
