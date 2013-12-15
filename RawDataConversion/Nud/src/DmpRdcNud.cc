
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtNudRaw.hh"
#include "DmpParameterNud.hh"

using namespace DmpParameter::Nud;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorNud(){
  std::cout<<"\nSetup connector:\tNud"<<std::endl;
  std::cout<<"-----------------------"<<std::endl;
  std::cout<<"\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionNud(){
  std::cout<<"\t\t\tEvent Conversion:\tNud"<<std::endl;
  Short_t tmp=0;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    std::cerr<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    std::cerr<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  for (Short_t i=0;i<8;++i)
  fHexData->read((char*)(&tmp),1);
  
  return true;
}


