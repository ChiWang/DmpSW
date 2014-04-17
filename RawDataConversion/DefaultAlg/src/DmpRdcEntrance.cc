/*
 *  $Id: DmpRdcEntrance.cc, 2014-04-17 11:31:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpRdcEntrance.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpServiceManager.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
void DmpCore::RdcExecute(){
  static DmpRdcSvcDataMgr *gRdcDataMgr = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"));
  // open file
  if(not gRdcDataMgr->OpenInputData()) return;
  // convert and save output
  gRdcDataMgr->BookBranch();
  for(long i=0;!gRdcDataMgr->InFileStream()->eof();++i){
    if(not gDmpAlgMgr->Process())  continue;
    gRdcDataMgr->FillEvent();
  }
  gRdcDataMgr->SaveOutput();
}


