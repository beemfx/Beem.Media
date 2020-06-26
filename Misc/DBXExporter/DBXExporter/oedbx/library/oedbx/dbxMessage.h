//***************************************************************************************
#ifndef dbxMessageH
#define dbxMessageH
//***************************************************************************************
#include <oedbx/dbxCommon.h>                                           
//***************************************************************************************
class AS_EXPORT DbxMessage   
{ public  :
            DbxMessage(InStream ins, int4 address);                     
            ~DbxMessage();

            int4 GetLength() const { return Length; }                   

            // !!! OE stores the message text with 0x0d 0x0a at  !!!
            // !!! the end of each line                          !!!
            char * GetText() const { return Text; }                     
            void Convert();                                             

            void ShowResults(OutStream outs) const;                     
            void Analyze(int4 & headerLines, int4 & bodyLines) const;   

  private : 
            void init();
            void readMessageText(InStream ins);

            // Stores the address, the length and the text of the message
            int4 Address, Length;
            char * Text;
};
//***************************************************************************************
#endif  dbxMessageH   







