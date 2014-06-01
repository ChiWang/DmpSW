/*
 *  $Id: DmpAlgorithmManager.cc, 2014-04-30 23:19:30 DAMPE $
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
bool DmpAlgorithmManager::ProcessOneEvent(){
  for(std::list<DmpVAlg*>::iterator it = fElements.begin();it != fElements.end();++it){
    if(not (*it)->ProcessThisEvent())  return false;
  }
  return true;
}

