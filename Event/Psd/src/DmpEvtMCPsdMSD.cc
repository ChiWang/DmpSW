/*
 *  $Id: DmpEvtMCPsdMSD.cc, 2014-06-10 16:35:35 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCPsdMSD.h"

ClassImp(DmpEvtMCPsdMSD)

//------------------------------------------------------------------------------
DmpEvtMCPsdMSD::DmpEvtMCPsdMSD()
 :fSDID(0),
  fEnergy(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCPsdMSD::~DmpEvtMCPsdMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCPsdMSD::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosX = (e*x + fEnergy*fPosX)/totE;
  fPosY = (e*y + fEnergy*fPosY)/totE;
  fPosZ = (e*z + fEnergy*fPosZ)/totE;
  fEnergy = totE;
}

//-------------------------------------------------------------------
#include <iostream>
void DmpEvtMCPsdMSD::SetBackTrack(const int &id,const double &e){
  if(fBackTrack.find(id) != fBackTrack.end()){
    fBackTrack[id] += e;
  }else{
    fBackTrack.insert(std::make_pair(id,e));
    std::cout<<"[Psd] new back track id = "<<id<<std::endl;
  }
}

