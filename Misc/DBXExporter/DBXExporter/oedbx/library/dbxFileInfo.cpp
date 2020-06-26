//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxFileInfo.h>
//***************************************************************************************
DbxFileInfo::DbxFileInfo(InStream ins, int4 address, int4 length)
{ init();
  Address = address;
  Length  = length;

  try { if(Length) readFileInfo(ins); }
  catch(const DbxException & E)
     { delete[] buffer;
       throw;
     }
}

DbxFileInfo::~DbxFileInfo()
{ delete[] buffer; }

void DbxFileInfo::init()
{ Address = Length = 0;
  buffer  = 0;
}
//***************************************************************************************
void DbxFileInfo::readFileInfo(InStream ins)
{ buffer = new int1[Length];
  ins.seekg(Address);
  ins.read((char *)buffer, Length);

  if(!ins) throw DbxException("Error reading object from input stream !");
}
//***************************************************************************************
const char * DbxFileInfo::GetFolderName() const
{ if(buffer && Length==0x618) return (char *)(buffer+0x105);
  return 0;
}

std::string DbxFileInfo::GetFileInfoTime() const
{ if(buffer && Length==0x108) return FileTime2String(buffer);
  return "";
}
//***************************************************************************************
void DbxFileInfo::ShowResults(OutStream outs) const
{ outs << std::endl << "File info : " << std::endl
       << " Address : 0x" << std::hex << Address  << std::endl
       << " Length  : 0x" << std::hex << Length   << std::endl;
  if(buffer)
    if(Length==0x618)        outs << " Folder name : " << GetFolderName()   << std::endl;
      else if(Length==0x108) outs << " File time : "   << GetFileInfoTime() << std::endl;

  rows2File(outs,0,buffer,Length);
}
