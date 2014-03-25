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
#include "DmpEventRaw.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader *headerAlg = 0;
DmpRdcAlgPsd    *psdAlg = 0;
DmpRdcAlgStk    *stkAlg = 0;
DmpRdcAlgBgo    *bgoAlg = 0;
DmpRdcAlgNud    *nudAlg = 0;
DmpRdcDataManager *dataMgr = 0;

//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  headerAlg = new DmpRdcAlgHeader("RdcAglHeader");
  psdAlg = new DmpRdcAlgPsd("RdcAlgPsd");
  stkAlg = new DmpRdcAlgStk("RdcAlgStk");
  bgoAlg = new DmpRdcAlgBgo("RdcAlgBgo");
  nudAlg = new DmpRdcAlgNud("RdcAlgNud");
  psdAlg->Initialize();
  stkAlg->Initialize();
  bgoAlg->Initialize();
  nudAlg->Initialize();
  dataMgr = DmpRdcDataManager::GetInstance();
  std::cout<<"\nRdc initialized"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  delete headerAlg;
  delete psdAlg;
  delete stkAlg;
  delete bgoAlg;
  delete nudAlg;
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName,const short &level){
  dataMgr->SetInDataName(dataName);
  // open file
  std::ifstream inputData(dataName.c_str(),std::ios::in|std::ios::binary);
  if (inputData.good()) {
    DmpRdcVAlg::SetFileStream(&inputData);
  }else{
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    inputData.close();
    return;
  }

  // convert and save output
  dataMgr->Initialize();
  dataMgr->BookBranch();
  for(long i=0;!inputData.eof();++i){
    if(not headerAlg->ProcessThisEvent())    continue;
    dataMgr->GetRawEvent()->Reset();
    if(not nudAlg->ProcessThisEvent())   continue;       // in hex data, nud first
    if(not psdAlg->ProcessThisEvent())   continue;
    if(not bgoAlg->ProcessThisEvent())   continue;
    if(not stkAlg->ProcessThisEvent())   continue;
    dataMgr->FillEvent();
  }
  dataMgr->SaveOutput();

  // reset
  inputData.close();
}


