/*
 *  $Id: DmpRdcEntrance.cc, 2014-03-14 11:15:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"
#include "DmpRdcEntrance.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader *headerAlg = 0;
DmpRdcAlgPsd    *psdAlg = 0;
DmpRdcAlgStk    *stkAlg = 0;
DmpRdcAlgBgo    *bgoAlg = 0;
DmpRdcAlgNud    *nudAlg = 0;

//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
  headerAlg = new DmpRdcAlgHeader();
  psdAlg = new DmpRdcAlgPsd();
  stkAlg = new DmpRdcAlgStk();
  bgoAlg = new DmpRdcAlgBgo();
  nudAlg = new DmpRdcAlgNud();
  psdAlg->SetupConnector();
  stkAlg->SetupConnector();
  bgoAlg->SetupConnector();
  nudAlg->SetupConnector();
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  delete headerAlg;
  delete psdAlg;
  delete stkAlg;
  delete bgoAlg;
  delete nudAlg;
}

#include "DmpRdcDataManager.h"
//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName, long nEvt){
  // open file
  //using namespace std;
  std::ifstream *inputData = new std::ifstream(dataName.c_str(),std::ios::in|std::ios::binary);
  if (!inputData->good()) {
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    inputData->close();
    delete inputData;
    return;
  }else{
    headerAlg->SetFileStream(inputData);
    psdAlg->SetFileStream(inputData);
    stkAlg->SetFileStream(inputData);
    bgoAlg->SetFileStream(inputData);
    nudAlg->SetFileStream(inputData);
  }

  // convert and save output
  static DmpRdcDataManager *dataMgr = DmpRdcDataManager::GetInstance();
  dataMgr->BookBranch();
  for (long i=0;!inputData->eof();++i){
          /*
if (i < nEvt){
  if(nEvt%100 == 0)  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"nEvt = "<<i<<std::endl;
}else{
  break;
}
*/
    if(not headerAlg->Convert())    continue;
    if(not psdAlg->Convert())   continue;
    if(not stkAlg->Convert())   continue;
    if(not bgoAlg->Convert())   continue;
    if(not nudAlg->Convert())   continue;

    if(headerAlg->GetTrigger() == psdAlg->GetTrigger() &&
       headerAlg->GetTrigger() == bgoAlg->GetTrigger())
    {
        dataMgr->FillEvent();
    }
  }
  dataMgr->SetOutDataName(dataName);
  dataMgr->SaveOutput();

  // reset
  inputData->close();
  delete inputData;
}


