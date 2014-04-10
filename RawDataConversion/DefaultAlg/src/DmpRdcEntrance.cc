/*
 *  $Id: DmpRdcEntrance.cc, 2014-03-20 16:02:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpRdcEntrance.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName){
  // open file
  if(not gRdcDataMgr->InputData(dataName)) return;
  // convert and save output
  gRdcDataMgr->BookBranch();
  for(long i=0;!gRdcDataMgr->gInDataStream.eof();++i){
    if(not gDmpAlgMgr->Process())  continue;
    gRdcDataMgr->FillEvent();
  }
  gRdcDataMgr->SaveOutput();
  // reset
  gRdcDataMgr->gInDataStream.close();
}


