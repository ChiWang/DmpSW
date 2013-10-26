
#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpDcdParameterNud.hh"
#include "DmpEvtNud.hh"

using namespace DmpDcdParameter::Nud;

void DmpRdcManager::ConstructorNud(){
  fEvtNud   = new DmpEvtNudRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpRdcManager::DestructorNud(){
  delete fEvtNud;
}

Bool_t DmpRdcManager::SetConnectorNud(){
  std::cout<<"\n\tSetup connector:\tNud"<<std::endl;

  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//  need real data to implement this part
Bool_t DmpRdcManager::ConversionNud(ifstream *HexData){
  std::cout<<"\t\t\tEvent Conversion:\tNud"<<std::endl;
  Short_t tmp=0;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    std::cout<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    std::cout<<"\t\t\t\t----> 0xeb wrong"<<std::endl;
    return false;
  }
  for (Short_t i=0;i<8;++i)
  HexData->read((char*)(&tmp),1);
  
  return true;
}


