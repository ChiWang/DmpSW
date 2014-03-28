/*
 *  $Id: DmpElementManager.h, 2014-03-26 17:08:16 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/03/2014
*/

#ifndef DmpElementManager_H
#define DmpElementManager_H

#include <list>
#include <string>

template<typename DmpElement>       // DmpElement: DmpVAlgorithm, DmpVService

class DmpElementManager{
public:
  DmpElementManager(const std::string&);
  virtual ~DmpElementManager();

public:
  bool Initialize();
  bool Finialize();
  void ListAllElements();
  void Append(DmpElement *aEle) {fElements.push_back(aEle);}
  void Replace(DmpElement*);
  DmpElement* Get(const std::string&) const;

public:
  std::string Name() const {return fName;}

protected:
  std::list<DmpElement*>    fElements;
  std::string               fName;

private:
  typename std::list<DmpElement*>::iterator    fIterator;

};


// define as below
//-------------------------------------------------------------------
#include <iostream>
template<typename DmpElement>
DmpElementManager<DmpElement>::DmpElementManager(const std::string &n)
 :fName(n)
{
  std::cout<<"---> Setting Kernel "<<fName;
}

//-------------------------------------------------------------------
template<typename DmpElement>
DmpElementManager<DmpElement>::~DmpElementManager(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"\tdelete "<<(*fIterator)->Name()<<std::endl;;
    delete (*fIterator);
  }
  std::cout<<"Done\n"<<std::endl;
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Initialize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    (*fIterator)->Initialize();
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Finialize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    (*fIterator)->Finialize();
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::ListAllElements(){
  std::cout<<"There are "<<fElements.size()<<" in "<<fName<<std::endl;
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"name : "<<(*fIterator)->Name()<<std::endl;
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::Replace(DmpElement *aEle){
  std::string name = aEle->Name();
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if((*fIterator)->Name() == name){
      delete (*fIterator);
      (*fIterator) = aEle;
    }
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
DmpElement* DmpElementManager<DmpElement>::Get(const std::string &n)const{
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if((*fIterator)->Name() == n) return (*fIterator);
  }
  return (DmpElement*)0;
}


#endif


