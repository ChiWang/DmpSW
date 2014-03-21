/*
 *  $Id: DmpRdcVAlg.cc, 2014-03-21 00:01:42 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "DmpRdcVAlg.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"

std::ifstream*  DmpRdcVAlg::fFile = 0;
DmpEvtHeader*   DmpRdcVAlg::fHeader = 0;

DmpRdcVAlg::DmpRdcVAlg(){
  fHeader = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetEventHeader();
}

//-------------------------------------------------------------------
DmpRdcVAlg::~DmpRdcVAlg(){
}

