//***************************************************************************************
#ifndef dbxCommonH
#define dbxCommonH
//***************************************************************************************
#include <string>
#include <fstream>
#include <iomanip>
//***************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)      
        #define AS_WIN32     
    #else 
        #error "This code is made for windows."
#endif
//#define AS_OEDBX_DLL                                             
#if defined(AS_WIN32) && defined(AS_OEDBX_DLL)                   
    #if defined(AS_OE_IMPLEMENTATION)
         #define AS_EXPORT __declspec(dllexport)
    #else
         #define AS_EXPORT __declspec(dllimport)
    #endif
#else
         #define AS_EXPORT
#endif                             
typedef unsigned char   int1;
typedef unsigned short  int2;
typedef unsigned long   int4;
typedef std::istream & InStream;
typedef std::ostream & OutStream;
class AS_EXPORT DbxException
{ public  : DbxException(const std::string text) { Error = text; }
            const char * what() const { return Error.c_str(); }
  private : std::string Error;
};
std::string AS_EXPORT FileTime2String(int1 * str);                
OutStream AS_EXPORT rows2File(OutStream out,int4 address, int1 * values, int4 length);
//***********************************************  
#endif dbxCommonH
