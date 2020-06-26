//***************************************************************************************
#ifndef dbxFolderListH
#define dbxFolderListH

#include <oedbx/dbxCommon.h>                    
//***************************************************************************************
const int1 DbxFolderListSize    = 0x68,            
           DbxFolderListEntries = DbxFolderListSize >> 2;
const int1 flFolderInfo         = 0x15,
           flNextFolderListNode = 0x17, flPreviousFolderListNode = 0x18;

class AS_EXPORT DbxFolderList   
{ public  : 
            DbxFolderList(InStream ins, int4 address);   

            int4 GetValue(int1 index) const { if(index>=DbxFolderListEntries)            
                                                    throw DbxException("Index to big !");
                                              return Buffer[index];
                                            }
            void ShowResults(OutStream outs) const;              

  private : 
            void readFolderList(InStream ins);

            //data
            int4 Address;
            int4 Buffer[DbxFolderListEntries];
};
//***********************************************  
#endif dbxFolderListH 




