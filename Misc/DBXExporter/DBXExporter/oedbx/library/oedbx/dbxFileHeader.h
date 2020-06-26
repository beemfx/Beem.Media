//***************************************************************************************
#ifndef DbxFileHeaderH
#define DbxFileHeaderH
//***************************************************************************************
#include <oedbx/dbxCommon.h>   
//***************************************************************************************
const int4 FileHeaderSize    = 0x24bc;
const int4 FileHeaderEntries = FileHeaderSize>>2;

const int4 fhFileInfoLength       = 0x07,                              
           fhFirstFolderListNode  = 0x1b, fhLastFolderListNode  = 0x1c,
           fhMessageConditionsPtr = 0x22, fhFolderConditionsPtr = 0x23,
           fhEntries              = 0x31, fhTreeRootNodePtr     = 0x39 ;

class AS_EXPORT DbxFileHeader   
{ public  : 
            DbxFileHeader(InStream ins);        

            int4 GetValue(int4 index) const{return Buffer[index];    }  

            bool isFolders() const { return (Buffer && (Buffer[1]==0x6f74fdc6)); }  

            void ShowResults(OutStream outs) const;              

  private : 
            // this function is called from the constructor
            void readFileHeader(InStream ins);

            // stores the data
            int4 Buffer[FileHeaderEntries];
};
//***********************************************  
#endif DbxFileHeaderH 





