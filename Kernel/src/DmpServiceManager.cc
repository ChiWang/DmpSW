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
  std::cout<<"Deleting "<<Name()<<std::endl;
}

//-------------------------------------------------------------------
DmpServiceManager::DmpServiceManager()
 :DmpElementManager<DmpVService>("Service Manager")
{
  std::cout<<"\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
DmpServiceManager *gSvcMgr = DmpServiceManager::GetInstance();

//-------------------------------------------------------------------
/*
void DmpElementManager<DmpElement>::VersionNote()const{
  std::cout<<"\n*********************************************************"<<std::endl;
  std::cout<<"\t\tDAMPE software version 1.0"<<std::endl;
  std::cout<<"*********************************************************"<<std::endl;
  std::cout<<"Initalize core:"<<std::endl;
}
*/ 
