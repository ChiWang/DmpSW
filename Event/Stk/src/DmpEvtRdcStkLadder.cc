/*
 *  $Id: DmpEvtRdcStkLadder.cc, 2014-07-19 11:10:08 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcStkLadder.h"

//-------------------------------------------------------------------
DmpEvtRdcStkLadder::DmpEvtRdcStkLadder()
 :fGlobalLadderID(-1)
{
}

//-------------------------------------------------------------------
DmpEvtRdcStkLadder::~DmpEvtRdcStkLadder(){
}

//-------------------------------------------------------------------
void DmpEvtRdcStkLadder::SetSignal(const int &feeChannelID,const short &stripID,const int &value){
  fGlobalFeeChannelID.push_back(feeChannelID);
  fStripID.push_back(stripID);
  fADCCount.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcStkLadder::GetSignal(const short &stripID) const{
  short index = -1;
  for(short i=0;i<fStripID.size();++i){
    if(fStripID[i] == stripID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fADCCount[index];
}

//-------------------------------------------------------------------
int DmpEvtRdcStkLadder::GetFeeID(const short &stripID) const{
  short index = -1;
  for(short i=0;i<fStripID.size();++i){
    if(fStripID[i] == stripID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index]/10000;
}

//-------------------------------------------------------------------
int DmpEvtRdcStkLadder::GetFeeChannelID(const short &stripID) const{
  short index = -1;
  for(short i=0;i<fStripID.size();++i){
    if(fStripID[i] == stripID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index]%10000;
}

//-------------------------------------------------------------------
int DmpEvtRdcStkLadder::GetGlocalFeeChannelID(const short &stripID) const{
  short index = -1;
  for(short i=0;i<fStripID.size();++i){
    if(fStripID[i] == stripID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index];
}

