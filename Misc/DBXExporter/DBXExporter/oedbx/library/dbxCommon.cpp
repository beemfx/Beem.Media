//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxCommon.h>

#include <windows.h>
#include <strstream>
//***************************************************************************************
std::string FileTime2String(int1 * str)
{ FILETIME * filetimeSrc = (FILETIME *)str, filetimeLocal;
  SYSTEMTIME systime;

  if(!FileTimeToLocalFileTime( filetimeSrc, &filetimeLocal))
         { return "Error converting to local time !"; }
    else { if(!FileTimeToSystemTime(&filetimeLocal, &systime))
              return "Error converting to system time !";
         }

  std::ostrstream ostr;
  ostr << std::setw(4) << std::setfill('0') << systime.wYear   << "/"
       << std::setw(2) << std::setfill('0') << systime.wMonth  << "/"
       << std::setw(2) << std::setfill('0') << systime.wDay    << " "
       << std::setw(2) << std::setfill('0') << systime.wHour   << ":"
       << std::setw(2) << std::setfill('0') << systime.wMinute << ":"
       << std::setw(2) << std::setfill('0') << systime.wSecond << std::ends;
  return ostr.str();
}

OutStream rows2File(OutStream outs,int4 address, int1 * values, int4 length)
{ for(int4 i=0;i<length;i+=16)
    { std::ostrstream strStr;
      std::string       str;
      bool isUsed = false, isLong = false;
      for(int4 j=0;(i+j<length) && (j<0x10);++j)
        { if((j&0x3) == 0) { strStr << " ";
                             if(*((int4 *)(values+i+j))!=0)
                                 { isLong = true; isUsed = true; }
                               else { isLong = false;
                                      strStr << "        ";
                                      str += "    ";
                                    }
                           }
          if(isLong)
            { int1 value = values[i+j];
              strStr << std::setw(2) << std::hex << std::setfill('0') << ((int)value);
              if((value<0x20)||(value>0x7f)) str += '.';
                                        else str += value;
            }
        }
      strStr << std::ends;
      if(isUsed) outs << std::right << std::setw(8) << std::hex << (address+i) << " :"
                      << std::left  << std::setw(38) << (strStr.str())
                      << str << std::endl;
    }
  return outs;
}
