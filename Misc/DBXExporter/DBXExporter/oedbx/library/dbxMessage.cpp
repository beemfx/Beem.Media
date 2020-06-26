//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxMessage.h>
//***************************************************************************************
DbxMessage::DbxMessage(InStream ins, int4 address)
{ Address  = address;
  init();

  try { readMessageText(ins); }
  catch(const DbxException & E)
     { delete[] Text;
       throw;
     }
}

DbxMessage::~DbxMessage()
{ delete[] Text; }

void DbxMessage::init()
{ Length     = 0;
  Text       = 0;
}

void DbxMessage::readMessageText(InStream ins)
{ int4 address = Address, header[4];
  char * pos;

  while(address)
    { ins.seekg(address);
      ins.read((char *)header, 0x10);
      if(!ins) throw DbxException("Error reading from input stream !");
      if(address!=header[0]) throw DbxException("Wrong object marker !");
      Length += header[2];
      address = header[3];
    }
  if(Length==0) throw DbxException("No text found !");
  pos = Text = new char[Length+1];    // +1 to terminate the text with 0x00
  address = Address;
  while(address)
    { ins.seekg(address);
      ins.read((char *)header, 0x10);
      ins.read(pos, header[2]);
      if(!ins) throw DbxException("Error reading from input stream !");
      address = header[3];
      pos += header[2];
    }
  *pos = 0;                           // terminate the text with 0x00
}

void DbxMessage::Convert()
{ int4 i=0, j=0;
  for(;i<=Length;++i) { if(Text[i]!='\r') Text[j++] = Text[i]; }
  if(j) --j;
  Length = j;
}
//***************************************************************************************
void DbxMessage::ShowResults(OutStream outs) const
{ int4 headerLines, bodyLines;
  Analyze(headerLines, bodyLines);
  outs << std::endl << "message  at    : 0x"   << std::hex << Address     << std::endl
                    << "  length       : 0x"   << std::hex << Length      << std::endl
                    << "  header lines : 0x"   << std::hex << headerLines << std::endl
                    << "  body lines   : 0x"   << std::hex << bodyLines   << std::endl
       << std::endl;

  rows2File(outs,0,(int1 *)Text,Length);
  //outs << "..." << std::endl << Text << std::endl << "..." << std::endl;
}

void DbxMessage::Analyze(int4 & headerLines, int4 & bodyLines) const
{ headerLines = bodyLines = 0;

  if(Length==0) return;

  bool isHeader = true;
  char * pos = Text, * to = Text + Length;
  headerLines = 1;
  while(pos!=to)
    { if(*pos == 0x0a)
        { if(isHeader) if(pos-Text>=2) if(*(pos-2)==0x0a) isHeader = false;
          if(isHeader) ++headerLines;
                  else ++bodyLines;
        }
      ++pos;
    }
}
//***************************************************************************************

