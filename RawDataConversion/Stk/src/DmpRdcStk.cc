
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
#ifdef Dmp_DEBUG
std::cerr<<"\t\t-->Stk from "<<fHexData->tellg();
#endif
  Short_t tmp=0;

#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<fHexData->tellg()<<std::endl;
#endif
  return true;
}

