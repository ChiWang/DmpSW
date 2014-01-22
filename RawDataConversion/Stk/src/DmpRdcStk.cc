
#include <iostream>

#include "DmpRdcManager.h"
#include "DmpEvtStkRaw.h"
#include "DmpParameterStk.h"

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
std::cerr<<"\t\t-->Stk from "<<std::dec<<fHexData->tellg();
#endif
  Short_t tmp=0;

#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
#endif
  return true;
}

