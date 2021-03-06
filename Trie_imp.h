#ifndef TRIE_IMP
#define TRIE_IMP
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <sstream>
#include <locale>
//Trie + lookahead (=Aho-Corasick ?)

struct Node
{
 Node()=default;
  Node(bool e):end(e){};

 bool end;
  char sign;
   std::map<char,std::shared_ptr<Node>> edges;
};
struct Trie
{
std::shared_ptr<Node> head =(std::make_shared<Node>(false));
 std::shared_ptr<Node> current=(head);
  unsigned int lexemMaxLenght=0;//for lookahead operator;
   std::vector<std::string> lexems;

 void insert(std::string);
  bool search(std::string);
   void lookahead(std::string);
};

 void Trie::insert(std::string newKey)
 {
   for(auto i:newKey)
   {
    if(newKey.size()>lexemMaxLenght)
        lexemMaxLenght=newKey.size();

     if(current->edges[i]==nullptr)
     {
      current->edges[i]=std::make_unique<Node>();
      current->edges[i]->sign=i;
     }
    current=current->edges[i];
   }
   current->end=true;
   current=head;
 }
 bool Trie::search(std::string keyCheck)
 {
  current=head;
   for(auto i:keyCheck)
   {
    if(current->edges[i]!=nullptr)
       current=current->edges[i];
    else
       return false;
   }
  return true;
 }
 void Trie::lookahead(std::string searchstring)
 {
  std::locale loc;
  auto first=searchstring.begin();
  std::string::iterator second;

  searchstring.size()>=lexemMaxLenght ?
   (second=first)                     :
   (second=searchstring.end()-1);
/////////////////////////////////////////////////
 while(second<=searchstring.end()-1)
 {
  if(std::isalpha(*first,loc))
  {
    while(std::isalpha(*second,loc)||std::isdigit(*second,loc))
    {
        second++;
    }
   lexems.emplace_back(std::string(first,second));
   first=second;
  }
 else
  {
   if(second+lexemMaxLenght<=searchstring.end())
   {
    second+=lexemMaxLenght;
     while(!search(std::string(first,second)))
     {
      second--;
     }
       lexems.emplace_back(first,second);
       first=second;
   }
   else
   {
    second=searchstring.end();
     while(!search(std::string(first,second)))
     {
      second--;
     }
       lexems.emplace_back(first,second);
    }
   }
  }
 }

#endif // TRIE_IMP_
