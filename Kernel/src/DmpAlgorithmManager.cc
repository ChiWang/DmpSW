/*
 *  $Id: DmpAlgorithmManager.cc, 2014-04-08 10:27:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/03/2014
*/

#include <iostream>
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
DmpAlgorithmManager::DmpAlgorithmManager()
{
  std::cout<<"---> DmpSW Kernel: Creating Algorithm Manager "<<"\t\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
DmpAlgorithmManager::~DmpAlgorithmManager(){
  std::cout<<"Deleting Algorithm Manager"<<std::endl;
  /*
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"\tdelete "<<(*fIterator)->Name()<<std::endl;;
    delete (*fIterator);
  }
  */
  std::cout<<"Done\n"<<std::endl;
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Initialize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if(not (*fIterator)->Initialize()) return false;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Process(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if(not (*fIterator)->ProcessThisEvent())  return false;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Finalize(){
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if(not (*fIterator)->Finalize()) return false;
  }
  return true;
}

//-------------------------------------------------------------------
void DmpAlgorithmManager::Append(DmpVAlg *aEle){
  std::cout<<"Append Algorithm: "<<aEle->Name();
  fElements.push_back(aEle);
  std::cout<<"\t\tSucc."<<std::endl;
}

//-------------------------------------------------------------------
void DmpAlgorithmManager::Replace(DmpVAlg *aEle){
  std::string name = aEle->Name();
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    if((*fIterator)->Name() == name){
      delete (*fIterator);
      (*fIterator) = aEle;
    }
  }
}

//-------------------------------------------------------------------
void DmpAlgorithmManager::ListAllElements(){
  std::cout<<"There are "<<fElements.size()<<" elements in Algorithm Manager"<<std::endl;
  for(fIterator = fElements.begin();fIterator != fElements.end();++fIterator){
    std::cout<<"\t\tname : "<<(*fIterator)->Name()<<std::endl;
  }
}

//-------------------------------------------------------------------
DmpAlgorithmManager *gDmpAlgMgr = DmpAlgorithmManager::GetInstance();

