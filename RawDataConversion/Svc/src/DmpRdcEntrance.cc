/*
 *  $Id: DmpRdcEntrance.cc, 2014-05-04 15:28:15 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpRdcEntrance.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
void DmpEntrance::RdcExecute(){
  DmpRdcSvcDataMgr *dmpRdcDataMgr = (DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr");
  DmpAlgorithmManager *dmpAlgMgr = gCore->AlgorithmManager();
  // open file
  if(not dmpRdcDataMgr->OpenInputData()) return;
  // convert and save output
  dmpRdcDataMgr->BookBranch();
  for(long i=0;!dmpRdcDataMgr->InFileStream()->eof();++i){
    if(not dmpAlgMgr->Process())  continue;
    dmpRdcDataMgr->FillEvent();
    dmpRdcDataMgr->ResetEvent();
  }
  dmpRdcDataMgr->SaveOutput();
}


