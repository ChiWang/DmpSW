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
  std::cout<<"\n*********************************************************"<<std::endl;
  std::cout<<"*  DAMPE software: Setup kernel of Raw Data Conversion  *"<<std::endl;
  std::cout<<"*********************************************************"<<std::endl;
  headerAlg = new DmpRdcAlgHeader();
  psdAlg = new DmpRdcAlgPsd();
  stkAlg = new DmpRdcAlgStk();
  bgoAlg = new DmpRdcAlgBgo();
  nudAlg = new DmpRdcAlgNud();
  psdAlg->SetupConnector();
  stkAlg->SetupConnector();
  bgoAlg->SetupConnector();
  nudAlg->SetupConnector();
  dataMgr = DmpRdcDataManager::GetInstance();
  std::cout<<"\n*********************************************************\n"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  delete headerAlg;
  delete psdAlg;
  delete stkAlg;
  delete bgoAlg;
  delete nudAlg;
  std::cout<<"\n***************************************************"<<std::endl;
  std::cout<<"*             Delete Raw Data Conversion          *"<<std::endl;
  std::cout<<"***************************************************"<<std::endl;
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
    if(not headerAlg->Convert())    continue;
    dataMgr->GetRawEvent()->Reset();
    if(not nudAlg->Convert())   continue;       // in hex data, nud first
    if(not psdAlg->Convert())   continue;
    if(not bgoAlg->Convert())   continue;
    if(not stkAlg->Convert())   continue;
    if(dataMgr->TriggerMatch(level)) dataMgr->FillEvent();
  }
  dataMgr->SaveOutput();

  // reset
  inputData.close();
}


