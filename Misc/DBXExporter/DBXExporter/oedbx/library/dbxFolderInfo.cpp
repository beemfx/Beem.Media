//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxFolderInfo.h>
//***************************************************************************************
const char * DbxFolderInfo::GetIndexText(int1 index) const
{ const char * text[MaxIndex] = {
     "folder index"                  , "index of the parent folder"              ,
     "folder name (newsgroup name)"  , "dbx file name"                           ,
     "id 04"                         , "registry key of the account"             ,
     "flags"                         , "messages in the folder"                  ,
     "unread messages in the folder" , "index for subfolders of 'local folders'" ,
     "local folder value"            , "id 0b"                                   ,
     "id 0c"                         , "max message index on server"             ,
     "min message index on server"   , "id 0f"                                   ,
     "max message index local"       , "min message index local"                 ,
     "messages to download"          , "id 13"                                   ,
     "id 14"                         , "id 15"                                   ,
     "id 16"                         , "id 17"                                   ,
     "id 18"                         , "id 19"                                   ,
     "id 1a"                         , "id 1b"                                   ,
     "watched messages"              , "id 1d"                                   ,
     "id 1e"                         , "id 1f"                                    };
  if(index<MaxIndex) return text[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************
IndexedInfoDataType DbxFolderInfo::GetIndexDataType(int1 index) const
{ IndexedInfoDataType dataType[MaxIndex] = {
      dtInt4 , dtInt4 , dtString,dtString,dtInt4 , dtString,dtInt4 , dtInt4 ,
      dtInt4 , dtInt4 , dtInt4 , dtNone , dtNone , dtInt4 , dtInt4 , dtInt4 ,
      dtInt4 , dtInt4 , dtInt4 , dtData , dtNone , dtData , dtNone , dtNone ,
      dtNone , dtNone , dtInt4 , dtNone , dtInt4 , dtNone , dtNone , dtNone  };
  if(index<MaxIndex) return dataType[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************

