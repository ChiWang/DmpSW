/*
 *  $Id: DmpServiceManager.cc, 2014-03-15 10:00:34 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#include <iostream>
#include "DmpServiceManager.h"
#include "DmpVService.h"

//-------------------------------------------------------------------
DmpServiceManager::~DmpServiceManager(){
  std::cout<<"Deleting DmpServiceManager"<<std::endl;
  for(std::list<DmpVService*>::iterator it=fSvcList.begin();it != fSvcList.end();++it){
    std::cout<<"\tdelete service: "<<(*it)->Name()<<std::endl;;
    delete (*it);
  }
  std::cout<<"Done\n"<<std::endl;
}

//-------------------------------------------------------------------
DmpVService* DmpServiceManager::GetService(const std::string &name, bool create){
// *
// *  TODO: ???  protect me ?
// *
  for(std::list<DmpVService*>::iterator it=fSvcList.begin();it != fSvcList.end();++it){
    if((*it)->Name() == name) return (*it);
  }
  return 0;
}

//-------------------------------------------------------------------
void DmpServiceManager::AppendService(DmpVService *aSvc){
  fSvcList.push_back(aSvc);
}

//-------------------------------------------------------------------
void DmpServiceManager::ReplaceService(DmpVService *aSvc){
  std::string name = aSvc->Name();
  for(std::list<DmpVService*>::iterator it=fSvcList.begin();it != fSvcList.end();++it){
    if((*it)->Name() == name){
      delete (*it);
      (*it) = aSvc;
    }
  }
}


//-------------------------------------------------------------------
void DmpServiceManager::ListAllService(){
  std::cout<<"There are "<<fSvcList.size()<<" service(s):"<<std::endl;
  for(std::list<DmpVService*>::iterator it=fSvcList.begin();it!=fSvcList.end();++it){
    std::cout<<"name : "<<(*it)->Name()<<std::endl;
  }
}

//-------------------------------------------------------------------
DmpServiceManager::DmpServiceManager(){
  std::cout<<"\n*********************************************************"<<std::endl;
  std::cout<<"\t\tDAMPE software version 1.0"<<std::endl;
  std::cout<<"*********************************************************"<<std::endl;
  std::cout<<"Initalize core:"<<std::endl;
  std::cout<<"\tSetup DmpServiceManager...    Done"<<std::endl;
  ListAllService();
}

//-------------------------------------------------------------------
DmpServiceManager *gSvcMgr = DmpServiceManager::GetInstance();
