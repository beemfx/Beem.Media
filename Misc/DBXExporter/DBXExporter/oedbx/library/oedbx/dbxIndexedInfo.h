//***************************************************************************************
#ifndef dbxIndexedInfoH
#define dbxIndexedInfoH
//***************************************************************************************
#include <oedbx/dbxCommon.h>                         
//***************************************************************************************
const int1 MaxIndex = 0x20; // I only found indexes from 0x00 to 0x1c. But to be sure
                            // that everything is ok, indexes up to 0x1f are allowed.
    // !!!
    // !!! This is not right. In the message dbx file for a Hotmail Http eMail
    // !!! account the index 0x23 is used. This source code is not changed yet
    // !!! and throws a exception if the index is >= MaxIndex.
    // !!!
                                                                                
// The data types I found stored in the indexed info objects
enum IndexedInfoDataType { dtNone=0, dtInt4=1, dtDateTime=2, dtString=4, dtData=8 };  
//***************************************************************************************
class AS_EXPORT DbxIndexedInfo   
{ public  : 
            DbxIndexedInfo(InStream ins, int4 address);          
            ~DbxIndexedInfo();

            int4 GetAddress()    const { return Address;    }    
            int4 GetBodyLength() const { return BodyLength; }    
            int1 GetEntries()    const { return Entries;    }    
            int1 GetCounter()    const { return Counter;    }    
            int4 GetIndexes()    const { return Indexes;    }    
            bool IsIndexed(int1 index) const { return Indexes&(1<<index); }  

            virtual const char * GetIndexText(int1 index) const   
                       { return 0;      }
            virtual IndexedInfoDataType GetIndexDataType(int1 index) const   
                       { return dtNone; }

            int1 * GetValue(int1 index, int4 * length) const;    
            const char * GetString(int1 index)         const;    
            int4 GetValue(int1 index)                  const;    

            void ShowResults(OutStream outs)           const;    

  private : 
            void init();
            void readIndexedInfo(InStream ins);

            void SetIndex(int1 index, int1 * begin, int4 length=0);
            void SetEnd(int1 index, int1 * end);

            // message info data
            int4 Address, BodyLength;
            int2 ObjectLength;
            int1 Entries, Counter, * Buffer;

            int4 Indexes;            // Bit field for the used indexes (MaxIndexe bits)

            int1 * Begin[MaxIndex];
            int4 Length[MaxIndex];
};
//***********************************************  
#endif  dbxIndexedInfoH














