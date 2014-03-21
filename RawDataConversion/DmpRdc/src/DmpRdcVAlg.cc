/*
 *  $Id: DmpRdcVAlg.cc, 2014-03-21 00:01:42 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpRdcVAlg.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"

std::ifstream*  DmpRdcVAlg::fFile = 0;
DmpEvtHeader*   DmpRdcVAlg::fHeader = 0;

DmpRdcVAlg::DmpRdcVAlg(){
  fHeader = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetEventHeader();
}

//-------------------------------------------------------------------
DmpRdcVAlg::~DmpRdcVAlg(){
}

//-------------------------------------------------------------------
void DmpRdcVAlg::StatusLog(short x)const {
  static bool prepareForFirstIn = true;
  if(x == 0 && prepareForFirstIn){     // in convert function
    std::cout<<"\tfrom "<<fFile->tellg();
    prepareForFirstIn = false;
  }else if(x == 1){     // out convert function, not output data length
    std::cout<<" to "<<fFile->tellg()<<std::endl;
    prepareForFirstIn = true;
  }else if(x > 1){      // out convert function, output data length
    std::cout<<" to "<<fFile->tellg()<<"\t---> "<<x<<std::endl;
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
    fFile->read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  fHeader->PrintTime();
}



