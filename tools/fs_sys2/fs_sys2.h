/******************************************************************************
File: fs_sys2.h
Purpose: The Legacy File System. A file system for use in video games. This is
the second version of this system. While the underlying code is in C++ the
API is compatible with C and C++.

(c) 2008 Blaine Myers.
******************************************************************************/
#ifndef __FS_SYS2_H__
#define __FS_SYS2_H__

/********************************
	Disable some of VCs warnings
*********************************/
#pragma warning(disable: 4267)
#pragma warning(disable: 4996)

#if defined(FS_DLL)

#ifdef FS_SYS2_EXPORTS
#undef FS_SYS2_EXPORTS
#define FS_SYS2_EXPORTS __declspec(dllexport)
#else
#define FS_SYS2_EXPORTS __declspec(dllimport)
#endif

#else

#ifdef FS_SYS2_EXPORTS
#undef FS_SYS2_EXPORTS
#endif

#define FS_SYS2_EXPORTS

#endif

#ifdef __cplusplus
extern "C"{
#endif __cplusplus

/* File System Types */
typedef unsigned int fs_uint;
typedef unsigned char fs_byte;
typedef unsigned long fs_dword, fs_ulong;
typedef signed long fs_long;
typedef float fs_float;
#if defined( __WIN32__ )
typedef __int32 fs_intptr_t;
typedef unsigned __int32 fs_size_t;
#elif defined( __WIN64__ )
typedef __int64 fs_intptr_t;
typedef unsigned __int64 fs_size_t;
#else
#error Platform not set.
#endif

typedef char fs_char8;
typedef fs_char8 *fs_str8;
typedef const char *fs_cstr8;

#ifdef __cplusplus
typedef wchar_t fs_char16;
#else !__cplusplus
typedef unsigned short fs_char16;
#endif __cplusplus
typedef fs_char16 *fs_str16;
typedef const fs_char16 *fs_cstr16;

typedef struct _fs_large_integer
{
	fs_dword dwLowPart;
	fs_long dwHighPart;
}fs_large_integer, *fs_plarge_integer, *fs_lplarge_integer;

typedef int fs_bool;
#define FS_TRUE  (1)
#define FS_FALSE (0)

#ifdef __cplusplus
#define FS_NULL (0)
#else __cplusplus
#define FS_NULL ((void*)0)
#endif __cplusplus

#define FS_MAX_PATH 255
typedef fs_char8  fs_pathA[FS_MAX_PATH+1];
typedef fs_char16 fs_pathW[FS_MAX_PATH+1];

/********************************
Mouting options.
********************************/
static const fs_dword MOUNT_MOUNT_SUBDIRS         = (1 << 1);
static const fs_dword MOUNT_FILE_OVERWRITE        = (1 << 2);
static const fs_dword MOUNT_FILE_OVERWRITELPKONLY = (1 << 3);
/*********************************
	Definitions for file access.
*********************************/

typedef enum _LF_SEEK_TYPE
{
	LF_SEEK_BEGIN  =0,
	LF_SEEK_CURRENT=1,
	LF_SEEK_END    =2,
}LF_SEEK_TYPE;
	
typedef enum _LF_CREATE_MODE
{
	LF_CREATE_ALWAYS=1,
	LF_CREATE_NEW   =2,
	LF_OPEN_ALWAYS  =3,
	LF_OPEN_EXISTING=4,
}LF_CREATE_MODE;
	
/* File acces modes, more than one can be specified. */
/* Read privelages. */
static const fs_dword LF_ACCESS_READ   = (1 << 2); /* Readable */
static const fs_dword LF_ACCESS_WRITE  = (1 << 3); /* Writeable */
static const fs_dword LF_ACCESS_MEMORY = (1 << 4); /* Memory access (cannot use with LF_ACCESS_WRITE) */

/* Memory Functions */
typedef enum _LF_ALLOC_REASON
{
	LF_ALLOC_REASON_SYSTEM,
	LF_ALLOC_REASON_FILE,
	LF_ALLOC_REASON_SCRATCH,
} LF_ALLOC_REASON;
typedef void* ( * FS_ALLOC_FUNC)(fs_size_t size, LF_ALLOC_REASON Reason, const fs_char8*const type, const fs_char8*const file, const fs_uint line);
typedef void  ( * FS_FREE_FUNC)(void* p, LF_ALLOC_REASON Reason);

void  FS_SYS2_EXPORTS FS_SetMemFuncs(FS_ALLOC_FUNC pAlloc, FS_FREE_FUNC pFree);

typedef void ( * FS_ENUMERATE_FUNCA )( fs_cstr8 Filename , void* Data );
typedef void ( * FS_ENUMERATE_FUNCW )( fs_cstr16 Filename , void* Data );
void FS_SYS2_EXPORTS FS_EnumerateFilesOfTypeA( fs_cstr8 Ext , FS_ENUMERATE_FUNCA EnumerateFunc , void* Data );
void FS_SYS2_EXPORTS FS_EnumerateFilesOfTypeW( fs_cstr16 Ext , FS_ENUMERATE_FUNCW EnumerateFunc , void* Data );

/*************************
	Error Handling Stuff
*************************/
typedef enum _FS_ERR_LEVEL
{
	ERR_LEVEL_UNKNOWN=0, /* Messages are always printed. */
	ERR_LEVEL_SUPERDETAIL=1,
	ERR_LEVEL_DETAIL,
	ERR_LEVEL_NOTICE,
	ERR_LEVEL_WARNING,
	ERR_LEVEL_ERROR,
	ERR_LEVEL_ALWAYS /* Message is always printed. */
}FS_ERR_LEVEL;

void FS_SYS2_EXPORTS FS_SetErrLevel(FS_ERR_LEVEL nLevel);
void FS_SYS2_EXPORTS FS_SetErrPrintFn(void (__cdecl*pfn)(fs_cstr16 szFormat));

typedef void (__cdecl * FS_ERR_CALLBACK)(fs_cstr16);

/* File System Functions Mounting, etc. */
fs_bool  FS_SYS2_EXPORTS FS_Initialize(FS_ALLOC_FUNC pAlloc, FS_FREE_FUNC pFree);
fs_dword FS_SYS2_EXPORTS FS_MountBaseA(fs_cstr8 szOSPath);
fs_dword FS_SYS2_EXPORTS FS_MountBaseW(fs_cstr16 szOSPath);
fs_dword FS_SYS2_EXPORTS FS_MountA(fs_cstr8 szOSPath, fs_cstr8 szMountPath, fs_dword Flags);
fs_dword FS_SYS2_EXPORTS FS_MountW(fs_cstr16 szOSPath, fs_cstr16 szMountPath, fs_dword Flags);
fs_bool  FS_SYS2_EXPORTS FS_ExistsA(fs_cstr8 szFilename);
fs_bool  FS_SYS2_EXPORTS FS_ExistsW(fs_cstr16 szFilename);
fs_dword FS_SYS2_EXPORTS FS_MountLPKA(fs_cstr8 szMountedFile, fs_dword Flags);
fs_dword FS_SYS2_EXPORTS FS_MountLPKW(fs_cstr16 szMountedFile, fs_dword Flags);
fs_bool  FS_SYS2_EXPORTS FS_UnMountAll();
fs_bool  FS_SYS2_EXPORTS FS_Shutdown();

typedef enum _FS_PRINT_MOUNT_INFO_TYPE
{
	PRINT_MOUNT_INFO_FULL,
	PRINT_MOUNT_INFO_FILENAME,
} FS_PRINT_MOUNT_INFO_TYPE;

void     FS_SYS2_EXPORTS FS_PrintMountInfo(FS_PRINT_MOUNT_INFO_TYPE Type);

/* File Access Functions Opening, Closing, Reading, Writing, etc. */
typedef void* LF_FILE3;

LF_FILE3  FS_SYS2_EXPORTS LF_OpenA(fs_cstr8 szFilename, fs_dword Access, fs_dword CreateMode);
LF_FILE3  FS_SYS2_EXPORTS LF_OpenW(fs_cstr16 szFilename, fs_dword Access, fs_dword CreateMode);
fs_bool   FS_SYS2_EXPORTS LF_Close(LF_FILE3 File);
fs_dword  FS_SYS2_EXPORTS LF_Read(LF_FILE3 File, void* pOutBuffer, fs_dword nSize);
fs_dword  FS_SYS2_EXPORTS LF_Write(LF_FILE3 File, const void* pInBuffer, fs_dword nSize);
fs_dword  FS_SYS2_EXPORTS LF_Tell(LF_FILE3 File);
fs_dword  FS_SYS2_EXPORTS LF_Seek(LF_FILE3 File, LF_SEEK_TYPE nMode, fs_long nOffset);
fs_dword  FS_SYS2_EXPORTS LF_GetSize(LF_FILE3 File);
const void* FS_SYS2_EXPORTS LF_GetMemPointer(LF_FILE3 File);
fs_bool   FS_SYS2_EXPORTS LF_IsEOF(LF_FILE3 File);

//Helper functions:
fs_str8  FS_SYS2_EXPORTS FS_GetFileNameFromPathA(fs_str8 szFileName, fs_cstr8 szFullPath);
fs_str16 FS_SYS2_EXPORTS FS_GetFileNameFromPathW(fs_str16 szFileName, fs_cstr16 szFullPath);

#ifdef __cplusplus
} /* extern "C" */
#endif __cplusplus

#endif __FS_SYS2_H__
