/*
 *  $Id: DmpRdcEntrance.cc, 2014-04-30 23:25:33 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpRdcEntrance.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpKernel.h"

//-------------------------------------------------------------------
void DmpCore::RdcExecute(){
  DmpRdcSvcDataMgr *dmpRdcDataMgr = (DmpRdcSvcDataMgr*)gKernel->ServiceManager()->Get("Rdc/DataMgr");
  DmpAlgorithmManager *dmpAlgMgr = gKernel->AlgorithmManager();
  // open file
  if(not dmpRdcDataMgr->OpenInputData()) return;
  // convert and save output
  dmpRdcDataMgr->BookBranch();
  for(long i=0;!dmpRdcDataMgr->InFileStream()->eof();++i){
    if(not dmpAlgMgr->Process())  continue;
    dmpRdcDataMgr->FillEvent();
  }
  dmpRdcDataMgr->SaveOutput();
}


