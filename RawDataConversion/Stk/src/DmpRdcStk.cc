
#include <iostream>

#include "DmpEvtStkHit.h"
#include "DmpRdcDataManager.h"
#include "DmpParameterStk.h"
using namespace DmpParameter::Stk;

//------------------------------------------------------------------------------
bool DmpRdcDataManager::SetConnectorStk(){
  std::cout<<"\nSetup connector:\tStk"<<"\t\tSuccess"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
bool DmpRdcDataManager::ConversionStk(){
#ifdef Dmp_DEBUG
std::cerr<<"\t\t-->Stk from "<<std::dec<<fHexData->tellg();
#endif
  Short_t tmp=0;

#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
#endif
  return true;
}

