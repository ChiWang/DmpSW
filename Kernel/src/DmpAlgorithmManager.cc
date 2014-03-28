/*
 *  $Id: DmpAlgorithmManager.cc, 2014-03-25 13:39:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/03/2014
*/

#include <iostream>
#include "DmpVAlgorithm.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
DmpAlgorithmManager::~DmpAlgorithmManager(){
  std::cout<<"Deleting "<<Name()<<std::endl;
}

//-------------------------------------------------------------------
DmpAlgorithmManager::DmpAlgorithmManager()
 :DmpElementManager<DmpVAlgorithm>("Algorithm Manager")
{
  std::cout<<"\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
bool DmpAlgorithmManager::Process(){
  for(std::list<DmpVAlgorithm*>::iterator it = fElements.begin();it != fElements.end();++it){
    if(not (*it)->ProcessThisEvent())  return false;
  }
  return true;
}

//-------------------------------------------------------------------
DmpAlgorithmManager *gAlgMgr = DmpAlgorithmManager::GetInstance();

