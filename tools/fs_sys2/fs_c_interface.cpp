//fs_c_interface.cpp - Code for the C interface for the file system.
#include "fs_fs2.h"

CLFileSystem* g_pFS=FS_NULL;

//A testing function, this will not be the final directory listing function
extern "C" void FS_PrintMountInfo(FS_PRINT_MOUNT_INFO_TYPE Type)
{
	g_pFS->PrintMountInfo(Type);
}


//File system function (c-interface).

extern "C" fs_bool FS_Initialize(FS_ALLOC_FUNC pAlloc, FS_FREE_FUNC pFree)
{
	if(!pAlloc || !pFree)
		__debugbreak();

	if(pAlloc && pFree)
		FS_SetMemFuncs(pAlloc, pFree);
		
	g_pFS=new CLFileSystem;
	if(!g_pFS)
	{
		FS_ErrPrintW(L"FS_Initalize Error: Not enough memory.", ERR_LEVEL_ERROR);
		return FS_FALSE;
	}

	return FS_TRUE;
}

extern "C" fs_bool FS_Shutdown()
{
	if(!g_pFS) return FS_FALSE;
	
	fs_bool bResult=g_pFS->UnMountAll();
	delete g_pFS;
	g_pFS=FS_NULL;
	return bResult;
}

extern "C" fs_dword FS_MountBaseA(fs_cstr8 szOSPath)
{
	return g_pFS->MountBaseA(szOSPath);
}
extern "C" fs_dword FS_MountBaseW(fs_cstr16 szOSPath)
{
	return g_pFS->MountBaseW(szOSPath);
}

extern "C" fs_dword FS_MountA(fs_cstr8 szOSPath, fs_cstr8 szMountPath, fs_dword Flags)
{
	return g_pFS->MountA(szOSPath, szMountPath, Flags);
}

extern "C" fs_dword FS_MountW(fs_cstr16 szOSPath, fs_cstr16 szMountPath, fs_dword Flags)
{
	return g_pFS->MountW(szOSPath, szMountPath, Flags);
}

extern "C" fs_bool FS_ExistsA(fs_cstr8 szFilename)
{
	return g_pFS->ExistsA(szFilename);
}
extern "C" fs_bool FS_ExistsW(fs_cstr16 szFilename)
{
	return g_pFS->ExistsW(szFilename);
}


	
extern "C" fs_dword FS_MountLPKA(fs_cstr8 szMountedFile, fs_dword Flags)
{
	return g_pFS->MountLPKA(szMountedFile, Flags);
}

extern "C" fs_dword FS_MountLPKW(fs_cstr16 szMountedFile, fs_dword Flags)
{
	return g_pFS->MountLPKW(szMountedFile, Flags);
}

extern "C" fs_bool FS_UnMountAll()
{
	return g_pFS->UnMountAll();
}

//File access functions c-interface.
extern "C" LF_FILE3 LF_OpenA(fs_cstr8 szFilename, fs_dword Access, fs_dword CreateMode)
{
	return g_pFS->OpenFileA(szFilename, Access, CreateMode);
}

extern "C" LF_FILE3 LF_OpenW(fs_cstr16 szFilename, fs_dword Access, fs_dword CreateMode)
{
	return g_pFS->OpenFileW(szFilename, Access, CreateMode);
}

extern "C" fs_bool LF_Close(LF_FILE3 File)
{
	return g_pFS->CloseFile((CLFile*)File);
}

extern "C" fs_dword LF_Read(LF_FILE3 File, void* pOutBuffer, fs_dword nSize)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->Read(pOutBuffer, nSize);
}
extern "C" fs_dword LF_Write(LF_FILE3 File, const void* pInBuffer, fs_dword nSize)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->Write(pInBuffer, nSize);
}
extern "C" fs_dword LF_Tell(LF_FILE3 File)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->Tell();
}
extern "C" fs_dword LF_Seek(LF_FILE3 File, LF_SEEK_TYPE nMode, fs_long nOffset)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->Seek(nMode, nOffset);
}
extern "C" fs_dword LF_GetSize(LF_FILE3 File)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->GetSize();
}
extern "C" const void* LF_GetMemPointer(LF_FILE3 File)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->GetMemPointer();
}
extern "C" fs_bool LF_IsEOF(LF_FILE3 File)
{
	CLFile* pFile=(CLFile*)File;
	return pFile->IsEOF();
}

extern "C" void FS_EnumerateFilesOfTypeA( fs_cstr8 Ext , FS_ENUMERATE_FUNCA EnumerateFunc , void* Data )
{
	return g_pFS->EnumerateFilesOfTypeA( Ext , EnumerateFunc, Data );
}

extern "C" void FS_EnumerateFilesOfTypeW( fs_cstr16 Ext , FS_ENUMERATE_FUNCW EnumerateFunc , void* Data )
{
	return g_pFS->EnumerateFilesOfTypeW( Ext , EnumerateFunc, Data );
}