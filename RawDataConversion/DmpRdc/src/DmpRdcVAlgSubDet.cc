/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-03-21 00:07:10 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpRdcVAlgSubDet.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpRdcLog.h"

//-------------------------------------------------------------------
DmpEvtHeader*  DmpRdcVAlgSubDet::sHeader = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetEventHeader();

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::ProcessThisEvent(){
  if(not fRunMe) return true;
  std::cout<<"\t"<<__PRETTY_FUNCTION__;
  gRdcLog->StatusLog(0);
//-------------------------------------------------------------------
// set ProcessThisEvention method here
//-------------------------------------------------------------------
  gRdcLog->StatusLog(1);
  return true;
}

