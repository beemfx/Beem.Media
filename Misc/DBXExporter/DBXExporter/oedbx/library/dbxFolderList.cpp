//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxFolderList.h>
//***************************************************************************************
DbxFolderList::DbxFolderList(InStream ins, int4 address)
{ Address = address;

  readFolderList(ins);
}

void DbxFolderList::readFolderList(InStream ins)
{ ins.seekg(Address);
  ins.read((char *)Buffer, DbxFolderListSize);
  if(!ins) throw DbxException("Error reading object from input stream !");
  if(Address!=Buffer[0]) throw DbxException("Wrong object marker !");
}
//***************************************************************************************
void DbxFolderList::ShowResults(OutStream outs) const
{ outs << std::endl << "FolderList : " << std::endl
       << " Address : 0x" << std::hex << Address << std::endl;
  rows2File(outs,Address,(int1 *)Buffer, DbxFolderListSize);
}
//***************************************************************************************
