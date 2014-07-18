/*
 *  $Id: DmpEvtMCPsdStrip.cc, 2014-07-18 10:40:26 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCPsdStrip.h"

ClassImp(DmpEvtMCPsdStrip)

//------------------------------------------------------------------------------
DmpEvtMCPsdStrip::DmpEvtMCPsdStrip()
 :fGlobalStripID(0),
  fEnergy(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCPsdStrip::~DmpEvtMCPsdStrip(){
}

//-------------------------------------------------------------------
void DmpEvtMCPsdStrip::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosX = (e*x + fEnergy*fPosX)/totE;
  fPosY = (e*y + fEnergy*fPosY)/totE;
  fPosZ = (e*z + fEnergy*fPosZ)/totE;
  fEnergy = totE;
}

//-------------------------------------------------------------------
//#include <iostream>
void DmpEvtMCPsdStrip::SetBackTrack(const int &id,const double &e){
  if(fBackTrack.find(id) != fBackTrack.end()){
    fBackTrack[id] += e;
  }else{
    fBackTrack.insert(std::make_pair(id,e));
    //std::cout<<"[Psd] new back track id = "<<id<<std::endl;
  }
}

