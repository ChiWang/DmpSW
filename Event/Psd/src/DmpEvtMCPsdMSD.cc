/*
 *  $Id: DmpEvtMCPsdMSD.cc, 2014-05-01 21:19:08 DAMPE $
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
void DmpEvtMCPsdMSD::SetBackTrack(const int &id,const double &p,const double &e){
  for(int i=0;i<fBackTrackID.size();++i){
    if(id == fBackTrackID[i]){
      fBTDepositedE[i] += e;
      if(p != fBackTrackPosZ[i]){
        std::cout<<"xxxx"<<std::endl;
      }
      return;
    }
  }
  fBackTrackID.push_back(id);
  fBackTrackPosZ.push_back(p);
  fBTDepositedE.push_back(e);
}

