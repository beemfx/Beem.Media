#include "fs_sys2.h"

#if defined( __cplusplus )
extern "C" {
#endif

void* FS_Malloc(fs_size_t size, LF_ALLOC_REASON reason, const fs_char8*const type, const fs_char8*const file, const fs_uint line);
void  FS_Free(void* p, LF_ALLOC_REASON reason);

/* Path name parsing functions. */
fs_str8  FS_GetDirFromPathA(fs_str8 szDir, fs_cstr8 szFullPath);
fs_str16 FS_GetDirFromPathW(fs_str16 szDir, fs_cstr16 szFullPath);
void FS_FixCaseA(fs_pathA szOut, fs_cstr8 szFullPath);
void FS_FixCaseW(fs_pathW szOut, fs_cstr16 szFullPath);
void FS_ErrPrintW(fs_cstr16 szFormat, FS_ERR_LEVEL nErrLevel, ...);
void FS_ErrPrintA(fs_cstr8 szFormat, FS_ERR_LEVEL nErrLevel, ...);

#if defined( __cplusplus )
} //extern "C"
#endif

#if defined( __cplusplus )
class IFsMemObj
{
public:
	void* operator new(fs_size_t Size);
	void operator delete(void*);
};
#endif
