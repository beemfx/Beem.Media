#include <map>
#pragma hdrstop
#include <oedbx/dbxFileHeader.h>                
#include <oedbx/dbxTree.h>
#include <oedbx/dbxFolderInfo.h>
#include <oedbx/dbxMessageInfo.h>
#include <oedbx/dbxMessage.h>

#include "Ex1.h"                                 
//***************************************************************************************
void ExtractAllMessages(const char * fileName, const char * logFile)    
{ // I presume that fileName stores the name of a message dbx file
  // The dbx file has to be opened in binary mode.
  std::ifstream ins(fileName, std::ios::binary);
  std::ofstream outf(logFile, std::ios::binary);

  DbxFileHeader fileHeader(ins);

  // Some const values like fhTreeRootNodePtr or fhEntries are defined
  // to allow easy access to the values stored in the DbxFileHeader
  int4 address = fileHeader.GetValue(fhTreeRootNodePtr),
       entries = fileHeader.GetValue(fhEntries        );

  if(address && entries) // if everything is OK
     { // The tree in the message dbx file stores the pointers to
       // all message infos objects
       // Read in the tree with all pointers
       DbxTree tree(ins,address,entries);

       // cycle through all values
       for(int4 j=0; j<entries; ++j)
         { // Get the address of the folder info
           address = tree.GetValue(j);
           // Read in the message info
           DbxMessageInfo messageInfo(ins,address);

           // Which indexes are used in the message info object
           int4 indexes = messageInfo.GetIndexes();

           if(indexes&(1<<miiMessageAddress)) // Only if a message is stored
             { // Get the address of the message
               int4 messageAddress = messageInfo.GetValue(miiMessageAddress);
               // Extract the message
               DbxMessage message(ins, messageAddress);

               // output the result
               outf << "___Message___ : " << j << ((char)0x0d) << ((char)0x0a);
               outf << message.GetText();
             }
         }
     }

  ins.close();
  outf.close();
}

//***************************************************************************************
typedef std::map<std::string, int> Histogramm;

std::string GetDomain(const char * str)
{ std::string id(str), result;
  std::string::size_type pos = id.find_last_of("@");
  if(pos==std::string::npos) result = "";
        else result = id.substr(pos, id.size()-pos-1);  // only between @...>
  return result;
}

void ShowAllDomains(const char * fileName, const char * logFile)        
{ Histogramm histo;

  // I presume that fileName stores the name of a message dbx file
  // The dbx file has to be opened in binary mode.
  std::ifstream ins(fileName, std::ios::binary);
  std::ofstream outf(logFile);

  DbxFileHeader fileHeader(ins);

  // Some const values like fhTreeRootNodePtr or fhEntries are defined
  // to allow easy access to the values stored in the DbxFileHeader
  int4 address = fileHeader.GetValue(fhTreeRootNodePtr),
       entries = fileHeader.GetValue(fhEntries        );

  if(address && entries) // if everything is OK
     { // The tree in the message dbx file stores the pointers to
       // all message infos objects
       // Read in the tree with all pointers
       DbxTree tree(ins,address,entries);

       // cycle through all values
       for(int4 j=0; j<entries; ++j)
         { // Get the address of the folder info
           address = tree.GetValue(j);
           // Read in the message info
           DbxMessageInfo messageInfo(ins,address);

           // Which indexes are used in the message info object
           int4 indexes = messageInfo.GetIndexes();

           if(indexes&(1<<0x07)) // Only if the message id is stored
             { // To store the length of the stored data.
               // This value is used if binary data is stored.
               int4 length;
               // To store the address of the stored data
               int1 * pointer;
               pointer = messageInfo.GetValue(0x07, &length);

               histo[GetDomain((char *)pointer)]++;
               //outf << pointer << std::endl; // Log the result
             }
         }
     }

  ins.close();

  Histogramm::iterator pos = histo.begin(), end = histo.end();
  while(pos!=end)
   { outf << std::setw(8) << (pos->second) << " : " << (pos->first) << std::endl;
     ++pos;
   }

  outf.close();
}
//***************************************************************************************
void ShowAllLocaleFolders(const char * fileName, const char * logFile)  
{
  // I presume that fileName stores the name of a folders.dbx file
  // The dbx file has to be opened in binary mode.
  std::ifstream ins(fileName, std::ios::binary);
  std::ofstream outf(logFile);

  DbxFileHeader fileHeader(ins);

  // The third tree in the folders.dbx stores the pointers to
  // all folder infos of all subfolders of Outlook Express
  const int4 treeNumber=2;
  // Some const values like fhTreeRootNodePtr or fhEntries are defined
  // to allow easy access to the values stored in the DbxFileHeader
  int4 address = fileHeader.GetValue(fhTreeRootNodePtr+treeNumber),
       entries = fileHeader.GetValue(fhEntries        +treeNumber);

  if(address && entries) // if everything is OK
     { // Read in the tree with all pointers
       DbxTree tree(ins,address,entries);

       outf << "Index   Parent  Name" << std::endl;
       // cycle through all values
       for(int4 j=0; j<entries; ++j)
         { // Get the address of the folder info
           address = tree.GetValue(j);
           // Read in the folder info
           DbxFolderInfo fInfo(ins,address);

           // Which indexes are used in the folder info object
           int4 indexes = fInfo.GetIndexes();

           if(indexes&(1<<fiiName)) // Only if the name is stored
             { outf<< std::left<< std::setw(8)<< (fInfo.GetValue(fiiIndex))
                   << std::left<< std::setw(8)<< (fInfo.GetValue(fiiParentIndex))
                                              << fInfo.GetString(fiiName)
                   << std::endl;
             }
         }
     }

  ins.close();
  outf.close();
}

