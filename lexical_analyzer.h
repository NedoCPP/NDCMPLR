#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include "Trie_imp.h"
#include <string>
#include <locale>
#include<fstream>
#include <algorithm>

void split_the_string(std::string input)
{
 Trie trie;
 std::ifstream setFile;
 std::ifstream inputFile;
 std::string SF;
 std::string IF;
 bool escape;
 std::locale locale;

 setFile.open("set.txt");
  bool ByteOrderMark=true;
  while(std::getline(setFile,SF))
  {
   if(ByteOrderMark)
   {
   trie.insert(std::string(SF.begin()+3,SF.end()));
    ByteOrderMark=false;
   continue;
   }
   else
    trie.insert(std::string(SF.begin(),SF.end()));
  }
 setFile.close();

ByteOrderMark=true;
 inputFile.open(input);
  while(std::getline(inputFile,IF))
  {
   std::string str;
    if(ByteOrderMark)
    {
      str=IF.substr(3,IF.size()-3);
      ByteOrderMark=false;
    }
    else
     str=IF.substr(0,IF.size());
///////////////////////////////////////////////
  str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   auto found=str.find('/');


  if(!escape)
  {
   if(found<str.size()-1&&str[found+1]=='/')
   {
    trie.lookahead(std::string(str.begin(),str.begin()+found));
    continue;
   }
   else if(found<str.size()-1&&str[found+1]=='*')
   {
    trie.lookahead(std::string(str.begin(),str.begin()+found));
    escape=true;
     continue;
   }
  }
  else
  {
     if(found<=str.size()-1&&found>=1&&str[found-1]=='*')
     {
      escape=false;
       trie.lookahead(std::string(str.begin()+found+1,str.end()));//???
     }

  }
 }
}




#endif // LEXICAL_ANALYZER_H
