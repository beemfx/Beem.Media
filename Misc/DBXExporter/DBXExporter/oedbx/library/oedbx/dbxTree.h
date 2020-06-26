//***************************************************************************************
#ifndef dbxTreeH
#define dbxTreeH
//***************************************************************************************
#include <oedbx/dbxCommon.h>                      
//***************************************************************************************
class AS_EXPORT DbxTree   
{ public  : 
            DbxTree(InStream ins, int4 address, int4 values);    
            ~DbxTree();

            int4 GetValue(int4 index) const;                     

            void ShowResults(OutStream outs) const;              

  private : 
            void readValues(InStream ins, int4 parent,   int4 address,  
                                          int4 position, int4 values);
            // data
            int4 Address;
            int4 Values, *Array;
};
//***********************************************  
#endif  dbxTreeH






