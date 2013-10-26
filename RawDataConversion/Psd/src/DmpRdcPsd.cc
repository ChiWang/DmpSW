
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpDcdParameterPsd.hh"
#include "DmpEvtPsd.hh"

using namespace DmpDcdParameter::Psd;

void DmpRdcManager::ConstructorPsd(){
  fEvtPsd   = new DmpEvtPsdRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpRdcManager::DestructorPsd(){
  delete fEvtPsd;
}

Bool_t DmpRdcManager::SetConnectorPsd(){
  std::cout<<"\n\tSetup connector:\tPsd"<<std::endl;
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//  need real data to implement this part
Bool_t DmpRdcManager::ConversionPsd(ifstream *HexData){
  std::cout<<"\t\t\tEvent Conversion:\tPsd"<<std::endl;
  Short_t tmp=0;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    std::cout<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    std::cout<<"\t\t\t\t----> 0x90 wrong"<<std::endl;
    return false;
  }
  for (Short_t i=0;i<22;++i)
  HexData->read((char*)(&tmp),1);
  return true;
}


