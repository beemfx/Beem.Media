//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxIndexedInfo.h>
//***************************************************************************************
DbxIndexedInfo::DbxIndexedInfo(InStream ins, int4 address)
{ init();
  Address  = address;
  try { readIndexedInfo(ins); }
  catch(const DbxException & E)
      { delete[] Buffer;
        throw;
      }
}

DbxIndexedInfo::~DbxIndexedInfo()
{ delete[] Buffer; }

void DbxIndexedInfo::init()
{ BodyLength   = 0;
  ObjectLength = 0;
  Entries      = Counter = 0;
  Buffer       = 0;
  Indexes      = 0;
  for(int1 i=0;i<MaxIndex;++i) { Begin[i] = 0; Length[i] = 0; }
}

void DbxIndexedInfo::readIndexedInfo(InStream ins)
{ int4 temp[3];
  ins.seekg(Address);
  ins.read((char *)temp, 12);
  if(!ins) throw DbxException("Error reading from input stream !");

  if(Address != temp[0]) throw DbxException("Wrong object marker !");

  BodyLength   = temp[1];
  ObjectLength = *( (int2 *)(temp+2)   );       //temp[2]& 0xffff;
  Entries      = *(((int1 *)(temp+2))+2);       //(temp[2]>>16) & 0xff;
  Counter      = *(((int1 *)(temp+2))+3);       //(temp[2]>>24) & 0xff;

  Buffer = new int1[BodyLength];
  ins.read((char *)Buffer, BodyLength);
  if(!ins) throw DbxException("Error reading from input stream !");

  bool isIndirect = false;
  int1 lastIndirect = 0;
  int1 * data   = Buffer + (Entries<<2);

  for(int1 i = 0; i<Entries; ++i)
     { int4 value    = ((int4 *)Buffer)[i];
       bool isDirect = value & 0x80;            // Data stored direct
       int1 index    = (int1) (value & 0x7f);   // Low byte is the index
       value >>= 8 ;                            // Value the rest
       if(index>=MaxIndex) throw DbxException("Index to big !");
       if(isDirect) SetIndex(index, Buffer+(i<<2)+1, 3);
             else { SetIndex(index, data+value);
                    if(isIndirect) SetEnd(lastIndirect, data+value);
                    isIndirect   = true;
                    lastIndirect = index;
                  }
       Indexes |= 1<<index;
     }
  if(isIndirect)SetEnd(lastIndirect, Buffer+BodyLength);
}
//***************************************************************************************
void DbxIndexedInfo::SetIndex(int1 index, int1 * begin, int4 length)
{ if(index<MaxIndex) { Begin[index] = begin; Length[index] = length; } }

void DbxIndexedInfo::SetEnd(int1 index, int1 * end)
{ if(index<MaxIndex) Length[index] = end - Begin[index]; }
//***************************************************************************************
int1 * DbxIndexedInfo::GetValue(int1 index, int4 * length) const
{ if(index>=MaxIndex) throw DbxException("Index to big !");
  *length = Length[index];
  return Begin[index];
}
//***************************************************************************************
const char * DbxIndexedInfo::GetString(int1 index) const
{ if(index>=MaxIndex) throw DbxException("Index to big !");
  return (char *)Begin[index];
}
//***************************************************************************************
int4 DbxIndexedInfo::GetValue(int1 index) const
{ if(index>=MaxIndex) throw DbxException("Index to big !");
  int4 length = Length[index], value = 0;
  int1 * data = Begin[index];
  if(data) { value = *((int4 *)data);                  // length>4 ignored
             if(length<4) value &= (1<<(length<<3))-1;
           }
  return value;
}
//***************************************************************************************
void DbxIndexedInfo::ShowResults(OutStream outs) const
{ outs << std::endl
       << "indexed info at : 0x"                << std::hex<< Address       << std::endl;
  outs << " Length of the index data field : 0x"<< std::hex<< BodyLength    << std::endl;
  outs << " Entries in the index field     : 0x"<< std::hex<< ((int)Entries)<< std::endl;
  outs << " Counter                        : 0x"<< std::hex<< ((int)Counter)<< std::endl;
  outs << " Indexes                        : 0x"<< std::hex<< Indexes       << std::endl;

  for(int1 i = 0; i<MaxIndex;++i) if(Indexes & (1<<i))
    { int4 length = 0;
      int1 * data = GetValue(i, &length);
      outs << std::left << std::setw(40)
           << GetIndexText(i) << " : ";

      if(data)
       switch (GetIndexDataType(i))
         { case dtString   : outs << data;                             break;
           case dtDateTime : outs << FileTime2String(data);            break;
           case dtInt4     : outs << "0x" << std::hex << GetValue(i);  break;
           default         : outs << "0x" << length << std::endl;
                             rows2File(outs,0,data,length);
         }
      outs << std::endl;
    }
}




