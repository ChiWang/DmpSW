/*
 *  $Id: DmpEvtMCNudMSD.cc, 2014-05-09 11:07:39 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCNudMSD.h"

ClassImp(DmpEvtMCNudMSD)

//------------------------------------------------------------------------------
short DmpEvtMCNudMSD::fDeltaTime = 50; // default, 500ns

DmpEvtMCNudMSD::DmpEvtMCNudMSD()
 :fSDID(0),
  fMinTime(9000),
  fMaxTime(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCNudMSD::~DmpEvtMCNudMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCNudMSD::AddG4Hit(const double &e,const double &t){
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

