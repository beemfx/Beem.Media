//***************************************************************************************
#ifndef dbxFileInfoH
#define dbxFileInfoH
//***************************************************************************************
#include <oedbx/dbxCommon.h>            
//***************************************************************************************
class AS_EXPORT DbxFileInfo   
{ public  : 
            DbxFileInfo(InStream ins, int4 address, int4 length);   
            ~DbxFileInfo();

            const char * GetFolderName()   const;                   
            std::string  GetFileInfoTime() const;                   

            void ShowResults(OutStream outs) const;                 

  private : 
            void init();
            void readFileInfo(InStream ins);

            //data
            int4 Address, Length;
            int1 * buffer;
} ;
//***********************************************  
#endif dbxFileInfoH    





