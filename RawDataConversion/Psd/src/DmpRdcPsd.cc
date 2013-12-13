
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtPsdRaw.hh"
#include "DmpDcdParameterPsd.hh"

using namespace DmpDcdParameter::Psd;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorPsd(){
  std::cout<<"\n\tSetup connector:\tPsd"<<std::endl;
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionPsd(){
  std::cout<<"\t\t\tEvent Conversion:\tPsd"<<std::endl;
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
  return true;
}


