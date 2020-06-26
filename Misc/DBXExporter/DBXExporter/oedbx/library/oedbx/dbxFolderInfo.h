//***************************************************************************************
#ifndef dbxFolderInfoH
#define dbxFolderInfoH
//***************************************************************************************
#include <oedbx/dbxIndexedInfo.h>           
//***************************************************************************************
const int1 fiiIndex = 0x00, fiiParentIndex = 0x01, fiiName = 0x02, fiiFlags = 0x06; 

class AS_EXPORT DbxFolderInfo : public DbxIndexedInfo   
{ public  : 
            DbxFolderInfo(InStream ins, int4 address) : DbxIndexedInfo(ins, address) { }  

            const char * GetIndexText(int1 index) const;             
            IndexedInfoDataType GetIndexDataType(int1 index) const;  
};
//***********************************************  
#endif  dbxFolderInfoH   




