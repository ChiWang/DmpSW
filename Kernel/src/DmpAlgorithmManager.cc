/*
 *  $Id: DmpAlgorithmManager.cc, 2014-03-25 13:39:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/03/2014
*/

#include <iostream>
#include "DmpAlgorithmManager.h"
#include "DmpVAlgorithm.h"

//-------------------------------------------------------------------
DmpAlgorithmManager::~DmpAlgorithmManager(){
  for(std::map<std::string,DmpVAlgorithm*>::iterator it=fAlgMap.begin();it != fAlgMap.end();++it){
    std::cout<<"delete algorithm: "<<it->first<<std::endl;;
    delete it->second;
  }
  std::cout<<"Delete DmpAlgorithmManager"<<std::endl;
}

//-------------------------------------------------------------------
DmpAlgorithmManager::DmpAlgorithmManager(){
  std::cout<<"\tSetup DmpAlgorithmManager...    Done"<<std::endl;
  std::cout<<"*********************************************************\n"<<std::endl;
}

//-------------------------------------------------------------------
void DmpAlgorithmManager::AppendAlgorithm(DmpVAlgorithm *aAlg){
  std::string name = aAlg->GetName();
  if(fAlgMap.find(name) != fAlgMap.end()){  // exist
    DmpVAlgorithm *tmp = fAlgMap[name];
    delete tmp;
    fAlgMap[name] = aAlg;
  }else{    // no exist
    fAlgMap.insert(std::pair<std::string,DmpVAlgorithm*>(name,aAlg));
  }
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Initialize(){
// *
// *  TODO: order not right?!!?
//          AppendAlgorithm() is Header, Nud, Psd, Stk, Bgo
// *
  for(std::map<std::string,DmpVAlgorithm*>::iterator it=fAlgMap.begin();it != fAlgMap.end();++it){
    it->second->Initialize();
  }
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Process(){
  for(std::map<std::string,DmpVAlgorithm*>::iterator it=fAlgMap.begin();it != fAlgMap.end();++it){
    if(not it->second->ProcessThisEvent())  return false;
  }
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Finialize(){
// *
// *  TODO: finialize() right??
// *
  for(std::map<std::string,DmpVAlgorithm*>::iterator it=fAlgMap.begin();it != fAlgMap.end();++it){
    it->second->Finialize();
  }
}

//-------------------------------------------------------------------
void DmpAlgorithmManager::ListAllAlgorithm(){
  std::cout<<"There are "<<fAlgMap.size()<<" algorithm(s):"<<std::endl;
  for(std::map<std::string,DmpVAlgorithm*>::iterator it=fAlgMap.begin();it!=fAlgMap.end();++it){
    std::cout<<"name : "<<it->first<<std::endl;
  }
}

//-------------------------------------------------------------------
DmpAlgorithmManager *gAlgMgr = DmpAlgorithmManager::GetInstance();

