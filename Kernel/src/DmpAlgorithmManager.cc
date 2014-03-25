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
DmpAlgorithmManager *gAlgorithmMgr = DmpAlgorithmManager::GetInstance();

