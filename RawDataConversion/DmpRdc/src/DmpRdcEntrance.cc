/*
 *  $Id: DmpRdcEntrance.cc, 2014-03-20 16:02:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpRdcEntrance.h"
#include "DmpRdcDataManager.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
void DmpCore::RdcExecute(const std::string &dataName){
  // open file
  if(not gDataMgr->InputData(dataName)) return;
  // convert and save output
  gDataMgr->BookBranch();
  for(long i=0;!gDataMgr->gInDataStream.eof();++i){
    if(not gDmpAlgMgr->Process())  continue;
    gDataMgr->FillEvent();
  }
  gDataMgr->SaveOutput();
  // reset
  gDataMgr->gInDataStream.close();
}


