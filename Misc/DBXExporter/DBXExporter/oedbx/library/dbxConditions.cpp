//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxConditions.h>
//***************************************************************************************
DbxConditions::DbxConditions(InStream ins, int4 address)
{ init();
  Address = address;

  try { readConditions(ins); }
  catch(const DbxException & E)
      { delete[] Text;
        throw;
      }
}
DbxConditions::~DbxConditions()
{ delete[] Text; }

void DbxConditions::init()
{ Length = 0;
  Text   = 0;
}

void DbxConditions::readConditions(InStream ins)
{ int4 head[2];
  ins.seekg(Address);
  ins.read((char *)head, 0x08);
  if(!ins) throw DbxException("Error reading object from input stream !");
  if(Address!=head[0]) throw DbxException("Wrong object marker !");
  Length = head[1];
  if(Length) { Text = new char[Length];
               ins.read(Text, Length);
               if(!ins) throw DbxException("Error reading object from input stream !");
             }
          else throw DbxException("No text found !");
}
//***************************************************************************************
void DbxConditions::ShowResults(OutStream outs) const
{ outs << std::endl << "Conditions : " << std::endl
       << " Position : 0x" << std::hex << Address << std::endl
       << " Length   : 0x" << std::hex << Length  << std::endl;
  if(Text) outs << Text << std::endl;
}
//***************************************************************************************

