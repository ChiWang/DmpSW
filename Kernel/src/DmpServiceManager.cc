/*
 *  $Id: DmpServiceManager.cc, 2014-04-30 23:18:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#include "DmpServiceManager.h"

//-------------------------------------------------------------------
DmpServiceManager::DmpServiceManager()
 :DmpElementManager<DmpVSvc>("Service Manager")
{
  std::cout<<"\t\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
DmpServiceManager::~DmpServiceManager(){
  std::cout<<"DMPSW Kernerl: deleting "<<Name();
}

