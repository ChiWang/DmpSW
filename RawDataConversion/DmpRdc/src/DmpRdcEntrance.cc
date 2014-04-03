/*
 *  $Id: DmpRdcEntrance.cc, 2014-03-20 16:02:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"
#include "DmpRdcEntrance.h"
#include "DmpRdcDataManager.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  gAlgMgr->Append(new DmpRdcAlgHeader("RdcAlgHeader"));
  gAlgMgr->Append(new DmpRdcAlgNud("RdcAlgNud"));
  gAlgMgr->Append(new DmpRdcAlgPsd("RdcAlgPsd"));
  gAlgMgr->Append(new DmpRdcAlgBgo("RdcAlgBgo"));
  gAlgMgr->Append(new DmpRdcAlgStk("RdcAlgStk"));
  gAlgMgr->Initialize();
  std::cout<<"\nRdc initialized"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName){
  gDataMgr->SetInDataName(dataName);
  // open file
  std::ifstream inputData(dataName.c_str(),std::ios::in|std::ios::binary);
  if (inputData.good()) {
    gDataMgr->gInFile = &inputData;
  }else{
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    inputData.close();
    return;
  }

  // convert and save output
  gDataMgr->Initialize();
  gDataMgr->BookBranch();
  for(long i=0;!inputData.eof();++i){
    if(not gAlgMgr->Process())  continue;
    gDataMgr->FillEvent();
  }
  gDataMgr->SaveOutput();

  // reset
  inputData.close();
}


