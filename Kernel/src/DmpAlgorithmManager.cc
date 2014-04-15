/*
 *  $Id: DmpAlgorithmManager.cc, 2014-04-08 10:27:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/03/2014
*/

#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
DmpAlgorithmManager::DmpAlgorithmManager()
 :DmpElementManager<DmpVAlg>("Algorithm Manager")
{
  std::cout<<"\t\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
DmpAlgorithmManager::~DmpAlgorithmManager(){
  std::cout<<"DMPSW Kernerl: deleting "<<Name();
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Process(){
  for(std::list<DmpVAlg*>::iterator it = fElements.begin();it != fElements.end();++it){
    if(not (*it)->ProcessThisEvent())  return false;
  }
  return true;
}

//-------------------------------------------------------------------
DmpAlgorithmManager *gDmpAlgMgr = DmpAlgorithmManager::GetInstance();

