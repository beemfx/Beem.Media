//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxMessageInfo.h>
//***************************************************************************************
const char * DbxMessageInfo::GetIndexText(int1 index) const
{ const char * text[MaxIndex] = {
     "message index"                , "flags"                          ,
     "time message created/send"    , "body lines"                     ,
     "message address"              , "original subject"               ,
     "time message saved"           , "message id"                     ,
     "subject"                      , "sender eMail address and name"  ,
     "answered to message id"       , "server/newsgroup/message number",
     "server"                       , "sender name"                    ,
     "sender eMail address"         , "id 0f"                          ,
     "message priority"             , "message text length"            ,
     "time message created/received", "receiver name"                  ,
     "receiver eMail address"       , "id 15"                          ,
     "id 16"                        , "id 17"                          ,
     "id 18"                        , "id 19"                          ,
     "OE account name"              , "OE account registry key"        ,
     "message text structure"       , "id 1d"                          ,
     "id 1e"                        , "id 1f"                           };
  if(index<MaxIndex) return text[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************
IndexedInfoDataType DbxMessageInfo::GetIndexDataType(int1 index) const
{ IndexedInfoDataType dataType[MaxIndex] = {
      dtInt4  , dtInt4  , dtDateTime, dtInt4  , dtInt4  , dtString,dtDateTime, dtString,
      dtString, dtString, dtString  , dtString, dtString, dtString, dtString , dtNone  ,
      dtInt4  , dtInt4  , dtDateTime, dtString, dtString, dtNone  , dtInt4   , dtNone  ,
      dtInt4  , dtInt4  , dtString  , dtString, dtData  , dtNone  , dtNone   , dtNone  };
  if(index<MaxIndex) return dataType[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************

