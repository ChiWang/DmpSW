/*
 *  $Id: DmpEvtMCStkMSD.cc, 2014-06-09 14:18:26 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 05/06/2014
*/

#include "DmpEvtMCStkMSD.h"

//-------------------------------------------------------------------
DmpEvtMCStkMSD::DmpEvtMCStkMSD()
 :fSDID(0)
{
}

//-------------------------------------------------------------------
DmpEvtMCStkMSD::~DmpEvtMCStkMSD(){
}

//-------------------------------------------------------------------
void  DmpEvtMCStkMSD::AddG4Hit(const double &e,const int &trackID, bool isBackTrack){
  if(isBackTrack){
    if(fBwdTrack.find(trackID) != fBwdTrack.end()){
      fBwdTrack[trackID] += e;
    }else{
      fBwdTrack.insert(std::make_pair(trackID,e));
    }
  }else{
    if(fFwdTrack.find(trackID) != fFwdTrack.end()){
      fFwdTrack[trackID] += e;
    }else{
      fFwdTrack.insert(std::make_pair(trackID,e));
    }
  }
}

//-------------------------------------------------------------------
double DmpEvtMCStkMSD::GetTotalEnergy(short type) const{
  double FwdE = 0, BwdE = 0;
  double value = 0;
  for(std::map<int,double>::const_iterator it=fFwdTrack.begin(); it!=fFwdTrack.end(); ++it){
    FwdE += it->second;
  }
  for(std::map<int,double>::const_iterator it=fBwdTrack.begin(); it!=fBwdTrack.end(); ++it){
    BwdE += it->second;
  }
  if(1 == type){
    value = FwdE;
  }else if(-1 == type){
    value = BwdE;
  }else{
    value = FwdE + BwdE;
  }
  return value;
}

