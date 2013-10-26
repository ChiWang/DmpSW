
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpDcdParameterStk.hh"
#include "DmpEvtStk.hh"

using namespace DmpDcdParameter::Stk;

void DmpRdcManager::ConstructorStk(){
  fEvtStk   = new DmpEvtStkRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpRdcManager::DestructorStk(){
  delete fEvtStk;
}

Bool_t DmpRdcManager::SetConnectorStk(){
  std::cout<<"\n\tSetup connector:\tStk"<<std::endl;
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//  need real data to implement this part
Bool_t DmpRdcManager::ConversionStk(ifstream *HexData){
  std::cout<<"\t\t\tEvent Conversion:\tStk"<<std::endl;
  Short_t tmp=0;
  return true;
}

