/*
 *  $Id: DmpEvtRdcNudBlock.cc, 2014-07-18 17:00:17 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcNudBlock.h"

//-------------------------------------------------------------------
DmpEvtRdcNudBlock::DmpEvtRdcNudBlock()
 :fGlobalBlockID(-1),
  fGlobalFeeChannelID(-1),
  fADCCount(-100)
{
}

//-------------------------------------------------------------------
DmpEvtRdcNudBlock::~DmpEvtRdcNudBlock(){
}

//-------------------------------------------------------------------
void DmpEvtRdcNudBlock::SetSignal(const short &feeChannelID,const int &value){
  fGlobalFeeChannelID = feeChannelID;
  fADCCount = value;
}

