#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include "Trie_imp.h"
#include <string>
#include<fstream>


void split_the_string(std::string input)
{
 Trie trie;
 std::ifstream setFile;
 std::ifstream inputFile;
 std::string SF;
 std::string IF;
 bool escape;


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
///////////////////////////////////////////////////
 ByteOrderMark=true;
  std::string buff;
   std::string skip;
   std::vector<std::string> Found;

  inputFile.open(input);
   while(std::getline(inputFile,buff))
   {
    if(ByteOrderMark)
    {
     buff.erase(0,3);
      ByteOrderMark=false;
    }


       for(size_t i=0;i<buff.size()-1;i++)
       {
         if(escape)
         {
          if(buff[i]=='*'&&buff[i+1]=='/')
          {
           i++;
           escape=false;
            continue;
          }
          else continue;
         }

        if(buff[i]!=' ')
        {
              if(buff[i]=='/'&&buff[i+1]=='/') break;
         else if(buff[i]=='/'&&buff[i+1]=='*')
              {
               escape=true;
               if(!skip.empty())
               {
                Found.emplace_back(skip);
                 skip.clear();
               }
              }
           else
              {
                  skip+=buff[i];
              }
        }
        else if(buff[i]==' '&&!skip.empty())
        {
         Found.emplace_back(skip);
          skip.clear();
        }

       }
     if(!skip.empty())
     {
      Found.emplace_back(skip);
      skip.clear();
     }
   }

   for(auto i:Found)
   {
      trie.lookahead(i);
   }

  inputFile.close();
}



#endif // LEXICAL_ANALYZER_H
