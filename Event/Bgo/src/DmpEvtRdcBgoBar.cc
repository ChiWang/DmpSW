/*
 *  $Id: DmpEvtRdcBgoBar.cc, 2014-07-17 15:09:45 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcBgoBar.h"

//-------------------------------------------------------------------
DmpEvtRdcBgoBar::DmpEvtRdcBgoBar()
 :fGlobalBarID(-1)
{
}

//-------------------------------------------------------------------
DmpEvtRdcBgoBar::~DmpEvtRdcBgoBar(){
}

//-------------------------------------------------------------------
void DmpEvtRdcBgoBar::SetSignal(const short &feeChannelID,const short &dynodeID,const int &value){
  fGlobalFeeChannelID.push_back(feeChannelID);
  fDynodeID.push_back(dynodeID);
  fADCCount.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcBgoBar::GetSignal(const short &dynodeID) const{
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
short DmpEvtRdcBgoBar::GetFeeID(const short &dynodeID) const{
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
short DmpEvtRdcBgoBar::GetFeeChannelID(const short &dynodeID) const{
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
short DmpEvtRdcBgoBar::GetGlocalFeeChannelID(const short &dynodeID) const{
  short index = -1;
  for(short i=0;i<fDynodeID.size();++i){
    if(fDynodeID[i] == dynodeID){
      index = i;
      break;
    }
  }
  return (index == -1)?-100:fGlobalFeeChannelID[index];
}

