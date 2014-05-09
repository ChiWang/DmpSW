/*
 *  $Id: DmpEvtMCNudMSD.cc, 2014-05-09 11:07:39 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCNudMSD.h"

ClassImp(DmpEvtMCNudMSD)

//------------------------------------------------------------------------------
short DmpEvtMCNudMSD::fDeltaTime = 500; // default, 500ns

DmpEvtMCNudMSD::DmpEvtMCNudMSD()
 :fSDID(0),
  fTimeFirstStep(0),
  fTimeLastStep(0)
{
  fEnergy.push_back(0);
  fPositionX.push_back(0);
  fPositionY.push_back(0);
  fPositionZ.push_back(0);
}

//------------------------------------------------------------------------------
DmpEvtMCNudMSD::~DmpEvtMCNudMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCNudMSD::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
// *
// *  TODO:  Bug???
//          Step 0 ~ Step N belongs to one track, but they are not continuous time
// *
  if((fTimeLastStep - fTimeFirstStep) < fDeltaTime*fEnergy.size()){
    int index = fEnergy.size()-1;
    double totE = e + fEnergy[index];
    fPositionX[index] = (e*x + fEnergy[index]*fPositionX[index])/totE;
    fPositionY[index] = (e*y + fEnergy[index]*fPositionY[index])/totE;
    fPositionZ[index] = (e*z + fEnergy[index]*fPositionZ[index])/totE;
    fEnergy[index] = totE;
  }else{
    fEnergy.push_back(e);
    fPositionX.push_back(x);
    fPositionY.push_back(y);
    fPositionZ.push_back(z);
  }
}

//-------------------------------------------------------------------
std::vector<double> DmpEvtMCNudMSD::GetPosition(const std::string &n) const{
  if("x" == n){
    return fPositionX;
  }else if("y" == n){
    return fPositionY;
  }else if("z" == n){
    return fPositionZ;
  }
}


