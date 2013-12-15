
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtPsdRaw.hh"
#include "DmpParameterPsd.hh"

using namespace DmpParameter::Psd;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorPsd(){
  std::cout<<"\nSetup connector:\tPsd"<<std::endl;
  std::cout<<"-----------------------"<<std::endl;
  std::cout<<"\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionPsd(){
#ifdef Dmp_DEBUG
std::cerr<<"\t\t-->Psd from "<<fHexData->tellg();
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
std::cerr<<"\tto "<<fHexData->tellg()<<std::endl;
#endif
  return true;
}


