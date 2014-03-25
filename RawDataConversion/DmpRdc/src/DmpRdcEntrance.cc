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
DmpRdcDataManager *dataMgr = 0;

//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  gAlgMgr->AppendAlgorithm(new DmpRdcAlgHeader("RdcAlg1Header"));
  gAlgMgr->AppendAlgorithm(new DmpRdcAlgNud("RdcAlg2Nud"));
  gAlgMgr->AppendAlgorithm(new DmpRdcAlgPsd("RdcAlg3Psd"));
  gAlgMgr->AppendAlgorithm(new DmpRdcAlgBgo("RdcAlg4Bgo"));
  gAlgMgr->AppendAlgorithm(new DmpRdcAlgStk("RdcAlg5Stk"));
  gAlgMgr->Initialize();
  dataMgr = DmpRdcDataManager::GetInstance();
  std::cout<<"\nRdc initialized"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
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
    if(not gAlgMgr->Process())  continue;
    dataMgr->FillEvent();
  }
  dataMgr->SaveOutput();

  // reset
  inputData.close();
}


