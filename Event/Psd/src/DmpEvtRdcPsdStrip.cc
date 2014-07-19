/*
 *  $Id: DmpEvtRdcPsdStrip.cc, 2014-07-19 10:02:17 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcPsdStrip.h"

//-------------------------------------------------------------------
DmpEvtRdcPsdStrip::DmpEvtRdcPsdStrip()
 :fGlobalStripID(-1)
{
}

//-------------------------------------------------------------------
DmpEvtRdcPsdStrip::~DmpEvtRdcPsdStrip(){
}

//-------------------------------------------------------------------
void DmpEvtRdcPsdStrip::SetSignal(const short &feeChannelID,const short &dynodeID,const int &value){
  fGlobalFeeChannelID.push_back(feeChannelID);
  fDynodeID.push_back(dynodeID);
  fADCCount.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcPsdStrip::GetSignal(const short &dynodeID) const{
  short index = -1;
  for(short i=0;i<fDynodeID.size();++i){
    if(fDynodeID[i] == dynodeID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fADCCount[index];
}

//-------------------------------------------------------------------
short DmpEvtRdcPsdStrip::GetFeeID(const short &dynodeID) const{
  short index = -1;
  for(short i=0;i<fDynodeID.size();++i){
    if(fDynodeID[i] == dynodeID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index]/1000;
}

//-------------------------------------------------------------------
short DmpEvtRdcPsdStrip::GetFeeChannelID(const short &dynodeID) const{
  short index = -1;
  for(short i=0;i<fDynodeID.size();++i){
    if(fDynodeID[i] == dynodeID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index]%1000;
}

//-------------------------------------------------------------------
short DmpEvtRdcPsdStrip::GetGlocalFeeChannelID(const short &dynodeID) const{
  short index = -1;
  for(short i=0;i<fDynodeID.size();++i){
    if(fDynodeID[i] == dynodeID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index];
}

