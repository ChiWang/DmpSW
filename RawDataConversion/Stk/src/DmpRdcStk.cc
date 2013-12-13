
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtStkRaw.hh"
#include "DmpDcdParameterStk.hh"

using namespace DmpDcdParameter::Stk;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorStk(){
  std::cout<<"\n\tSetup connector:\tStk"<<std::endl;
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionStk(){
  std::cout<<"\t\t\tEvent Conversion:\tStk"<<std::endl;
  Short_t tmp=0;
  return true;
}

