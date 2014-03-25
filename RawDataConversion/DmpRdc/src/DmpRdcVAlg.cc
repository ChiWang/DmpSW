/*
 *  $Id: DmpRdcVAlg.cc, 2014-03-25 19:30:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpRdcVAlg.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"

std::ifstream*  DmpRdcVAlg::sFile = 0;
DmpEvtHeader*   DmpRdcVAlg::sHeader = 0;

//-------------------------------------------------------------------
DmpRdcVAlg::DmpRdcVAlg(const std::string &name)
 :DmpVAlgorithm(name)
{
  sHeader = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetEventHeader();
}

//-------------------------------------------------------------------
DmpRdcVAlg::~DmpRdcVAlg(){
}

//-------------------------------------------------------------------
void DmpRdcVAlg::StatusLog(short x)const {
  static bool prepareForFirstIn = true;
  if(x == 0 && prepareForFirstIn){     // in convert function
    std::cout<<"\tfrom "<<sFile->tellg();
    prepareForFirstIn = false;
  }else if(x == 1){     // out convert function, not output data length
    std::cout<<" to "<<sFile->tellg()<<std::endl;
    prepareForFirstIn = true;
  }else if(x > 1){      // out convert function, output data length
    std::cout<<" to "<<sFile->tellg()<<"\t---> "<<x<<std::endl;
    prepareForFirstIn = true;
  }else if(x == -1){
    std::cout<<"\tError: not find 0xeb\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -2){
    std::cout<<"\tError: not find 0x90\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -3){
    std::cout<<"\tError: trigger not match\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -4){
    std::cout<<"\tError: run mode not match\t";
    PrintLocation();
    prepareForFirstIn = true;
  }
}

//-------------------------------------------------------------------
void DmpRdcVAlg::PrintLocation()const{
  static short tmp = 0;
  std::cout<<"Location: ";
  for(short i=0;i<5;++i){
    sFile->read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  sHeader->PrintTime();
}


