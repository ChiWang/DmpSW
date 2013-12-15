
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtStkRaw.hh"
#include "DmpParameterStk.hh"

using namespace DmpParameter::Stk;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorStk(){
  std::cout<<"\nSetup connector:\tStk"<<std::endl;
  std::cout<<"-----------------------"<<std::endl;
  std::cout<<"\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionStk(){
  std::cout<<"\t\t\tEvent Conversion:\tStk"<<std::endl;
  Short_t tmp=0;
  return true;
}

