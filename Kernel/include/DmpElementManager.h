/*
 *  $Id: DmpElementManager.h, 2014-04-10 19:59:09 chi $
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
  void Replace(DmpElement*);
  void Append(DmpElement*);
  void ListAllElements();
  bool Initialize();
  bool Finalize();
  //DmpElement* Get(const std::string&) const;

protected:
  std::string Name() const {return fName;}

protected:
  std::list<DmpElement*>    fElements;
  std::string               fName;
  typename std::list<DmpElement*>::iterator    fIterator;

};


// define as below
//-------------------------------------------------------------------
#include <iostream>
template<typename DmpElement>
DmpElementManager<DmpElement>::DmpElementManager(const std::string &n)
 :fName(n)
{
  std::cout<<"---> Setting DMPSW Kernel: "<<fName;
}

//-------------------------------------------------------------------
template<typename DmpElement>
DmpElementManager<DmpElement>::~DmpElementManager(){
        /*
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"\tdelete "<<(*fIterator)->Name()<<std::endl;;
    delete (*fIterator);
  }
  */
  std::cout<<"\t\tDone\n"<<std::endl;
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
void DmpElementManager<DmpElement>::Append(DmpElement *aEle){
  std::cout<<"Append Algorithm: "<<aEle->Name();
  fElements.push_back(aEle);
  std::cout<<"\t\tSucc."<<std::endl;
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::ListAllElements(){
  std::cout<<"There are "<<fElements.size()<<"elements in "<<fName<<std::endl;
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"\t\tname : "<<(*fIterator)->Name()<<std::endl;
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Initialize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if(not (*fIterator)->Initialize()) return false;
  }
  return true;
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Finalize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if(not (*fIterator)->Finalize()) return false;
  }
  return true;
}


#endif

