/*
 *  $Id: DmpEvtMCStkStrip.cc, 2014-06-09 14:18:26 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 05/06/2014
*/

#include "DmpEvtMCStkStrip.h"

//-------------------------------------------------------------------
DmpEvtMCStkStrip::DmpEvtMCStkStrip()
 :fGlobalStripID(0),
  fEnergy(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0)
{
}

//-------------------------------------------------------------------
DmpEvtMCStkStrip::~DmpEvtMCStkStrip(){
}

//-------------------------------------------------------------------
void  DmpEvtMCStkStrip::AddG4Hit(const double &e,const double& x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosX = (e*x + fEnergy*fPosX)/totE;
  fPosY = (e*y + fEnergy*fPosY)/totE;
  fPosZ = (e*z + fEnergy*fPosZ)/totE;
  fEnergy = totE;
}

//-------------------------------------------------------------------
#include <iostream>
void DmpEvtMCStkStrip::SetBackTrack(const int &id,const double &e){
  if(fBackTrack.find(id) != fBackTrack.end()){
    fBackTrack[id] += e;
  }else{
    fBackTrack.insert(std::make_pair(id,e));
    std::cout<<"[Stk] new back track id = "<<id<<std::endl;
  }
}


