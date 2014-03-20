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
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  delete headerAlg;
  delete psdAlg;
  delete stkAlg;
  delete bgoAlg;
  delete nudAlg;
  std::cout<<"\n**************************************************"<<std::endl;
  std::cout<<"*             Delete Raw Data Conversion          *"<<std::endl;
  std::cout<<"***************************************************"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName, long nEvt){
  dataMgr->SetInDataName(dataName);
  // open file
  std::ifstream inputData(dataName.c_str(),std::ios::in|std::ios::binary);
  if (inputData.good()) {
    headerAlg->SetFileStream(&inputData);
    psdAlg->SetFileStream(&inputData);
    stkAlg->SetFileStream(&inputData);
    bgoAlg->SetFileStream(&inputData);
    nudAlg->SetFileStream(&inputData);
  }else{
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    inputData.close();
    return;
  }

  // convert and save output
  dataMgr->BookBranch();
  for (long i=0;!inputData.eof();++i){
{// debug
  if (i > nEvt) break;
}
    if(not headerAlg->Convert())    continue;
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::endl;
#endif
}
    if(not psdAlg->Convert())   continue;
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::endl;
#endif
}
    if(not stkAlg->Convert())   continue;
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::endl;
#endif
}
    if(not bgoAlg->Convert())   continue;
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::endl;
#endif
}
    if(not nudAlg->Convert())   continue;
    {// trigger check
    if(headerAlg->GetTrigger() != psdAlg->GetTrigger() ||
       headerAlg->GetTrigger() != bgoAlg->GetTrigger())
    {}
    }
    dataMgr->FillEvent();
  }
  dataMgr->SaveOutput();

  // reset
  inputData.close();
}


