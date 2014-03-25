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
  for(std::map<std::string,DmpVService*>::iterator it=fSvcMap.begin();it != fSvcMap.end();++it){
    std::cout<<"delete service: "<<it->first<<std::endl;;
    delete it->second;
  }
  std::cout<<"Delete DmpServiceManager"<<std::endl;
}

//-------------------------------------------------------------------
DmpVService* DmpServiceManager::GetService(const std::string &name, bool create){
// *
// *  TODO: ???  protect me ?
// *
  return fSvcMap[name];
}

//-------------------------------------------------------------------
void DmpServiceManager::AppendService(DmpVService *aSvc){
  std::string name = aSvc->GetName();
  if(fSvcMap.find(name) != fSvcMap.end()){  // exist
    DmpVService *tmp = fSvcMap[name];
    delete tmp;
    fSvcMap[name] = aSvc;
  }else{    // no exist
    fSvcMap.insert(std::pair<std::string,DmpVService*>(name,aSvc));
  }
}

//-------------------------------------------------------------------
void DmpServiceManager::ListAllService(){
  std::cout<<"There are "<<fSvcMap.size()<<" service(s):"<<std::endl;
  for(std::map<std::string,DmpVService*>::iterator it=fSvcMap.begin();it!=fSvcMap.end();++it){
    std::cout<<"name : "<<it->first<<std::endl;
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
