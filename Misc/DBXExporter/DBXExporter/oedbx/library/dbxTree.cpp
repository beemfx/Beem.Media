//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxTree.h>
//***************************************************************************************
const int4 TreeNodeSize = 0x27c;

DbxTree::DbxTree(InStream ins, int4 address, int4 values)
{ Address = address;
  Values  = values;

  Array = new int4[Values];
  if(!Array) throw DbxException("Error allocating memory !");
  try { readValues(ins, 0, Address, 0, Values); }
  catch(const DbxException & E)
    { delete[] Array;
      throw;
    }
}

DbxTree::~DbxTree()
{ delete[] Array; }

void DbxTree::readValues(InStream ins, int4 parent,   int4 address,
                                       int4 position, int4 values)
{ int4 buffer[TreeNodeSize>>2], N = 0;

  if(position+values>Values) throw DbxException("To many values to read !");

  ins.seekg(address);
  ins.read((char *)buffer, TreeNodeSize);
  if(!ins) throw DbxException("Error reading node from input stream !");

  if(buffer[0]!=address) throw DbxException("Wrong object marker !");
  if(buffer[3]!=parent)  throw DbxException("Wrong parent !");

  int1 /* id = buffer[4]&0xff, */ entries = (int1)((buffer[4] >> 8)&0xff);
  if(entries>0x33) throw DbxException("Wrong value for entries !");

  if(buffer[2]!=0) { readValues(ins, address, buffer[2], position, buffer[5]);
                     N += buffer[5];
                   }
  for(int1 i=0;i<entries;++i)
    { int4 * pos = buffer + 6 + i * 3;
      if(pos[0]!=0)
        { int4 value = position + (++N);
          if(value>Values) throw DbxException("To many values !");
          Array[value-1] = pos[0];
        }
      if(pos[1]!=0) { readValues(ins, address, pos[1], position+N, pos[2]);
                      N+=pos[2];
                    }
    }
  if(N!=values) throw DbxException("Wrong number of values found!");
}
//***************************************************************************************
int4 DbxTree::GetValue(int4 index) const
{ if(index<Values) return Array[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************
void DbxTree::ShowResults(OutStream outs) const
{ outs << std::endl
       << "tree           : " << std::endl
       << "   address     : 0x" << std::hex << Address << std::endl
       << "   values read : 0x" << std::hex << Values  << std::endl;
}
//***************************************************************************************
