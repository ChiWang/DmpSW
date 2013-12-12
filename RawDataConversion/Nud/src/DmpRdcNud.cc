
#include <iostream>

#include "DmpRdc.hh"
#include "DmpEvtNudRaw.hh"
#include "DmpDcdParameterNud.hh"

using namespace DmpDcdParameter::Nud;

//------------------------------------------------------------------------------
Bool_t DmpRdc::SetConnectorNud(){
  std::cout<<"\n\tSetup connector:\tNud"<<std::endl;
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdc::ConversionNud(){
  std::cout<<"\t\t\tEvent Conversion:\tNud"<<std::endl;
  Short_t tmp=0;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    std::cout<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    std::cout<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  for (Short_t i=0;i<8;++i)
  fHexData->read((char*)(&tmp),1);
  
  return true;
}


