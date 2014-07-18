/*
 *  $Id: DmpEvtMCNudBlock.cc, 2014-07-18 09:59:24 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCNudBlock.h"

ClassImp(DmpEvtMCNudBlock)

//------------------------------------------------------------------------------
short DmpEvtMCNudBlock::fDeltaTime = 100; // default, 100ns

DmpEvtMCNudBlock::DmpEvtMCNudBlock()
 :fGlobalBlockID(0),
  fMinTime(9000),
  fMaxTime(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCNudBlock::~DmpEvtMCNudBlock(){
}

//-------------------------------------------------------------------
void DmpEvtMCNudBlock::AddG4Hit(const double &e,const double &t){
  if(fMinTime > t){
    fMinTime = t;
  }
  if(fMaxTime < t){
    fMaxTime = t;
  }
  int binID = t/fDeltaTime;
  if((binID+1) > fEnergy.size()){
    fEnergy.resize(binID+1);
    fEnergy[binID] = e;
  }else{
    double totE = e + fEnergy[binID];
    fEnergy[binID] = totE;
  }
}

