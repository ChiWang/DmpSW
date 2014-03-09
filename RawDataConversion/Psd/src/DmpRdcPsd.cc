
#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpEvtPsdHit.h"
using namespace DmpParameter::Psd;

//------------------------------------------------------------------------------
bool DmpRdcDataManager::SetConnectorPsd(){
  std::cout<<"\nSetup connector:\tPsd"<<"\t\tSuccess"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
bool DmpRdcDataManager::ConversionPsd(){
#ifdef Dmp_DEBUG
std::cerr<<"\t\t-->Psd from "<<std::dec<<fHexData->tellg();
#endif

/*
  Short_t tmp=0;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    std::cerr<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    std::cerr<<"\t\t\t\t----> 0x90 wrong"<<std::endl;
    return false;
  }
  for (Short_t i=0;i<22;++i)
  fHexData->read((char*)(&tmp),1);
*/

#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
#endif
  return true;
}


