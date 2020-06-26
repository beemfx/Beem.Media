//***************************************************************************************
#ifndef dbxConditionsH
#define dbxConditionsH
//***************************************************************************************
#include <oedbx/dbxCommon.h>           
//***************************************************************************************
class AS_EXPORT DbxConditions   
{ public  : 
            DbxConditions(InStream ins, int4 address);           
            ~DbxConditions();
            
            const char * GetText() const { return Text; }        
            
            void ShowResults(OutStream outs) const;              

  private : 
            void init();
            void readConditions(InStream ins);

            //data
            int4 Address, Length;
            char * Text;
};
//***********************************************  
#endif dbxConditionsH




