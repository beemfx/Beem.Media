//***************************************************************************************
#ifndef dbxMessageInfoH
#define dbxMessageInfoH
//***************************************************************************************
#include <oedbx/dbxIndexedInfo.h>                  
//***************************************************************************************
const int1 miiIndex = 0x00, miiFlags = 0x01, miiMessageAddress = 0x04,   
           miiSubject = 0x08;

class AS_EXPORT DbxMessageInfo : public DbxIndexedInfo   
{ public  : 
            DbxMessageInfo(InStream ins, int4 address) : DbxIndexedInfo(ins, address) { } 

            const char *        GetIndexText    (int1 index) const;  
            IndexedInfoDataType GetIndexDataType(int1 index) const;  
};
//***********************************************  
#endif  dbxMessageInfoH




