/*
 *  $Id: DmpEvtRdcBgoMSD.cc, 2014-04-24 10:59:32 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcBgoMSD.h"

//-------------------------------------------------------------------
DmpEvtRdcBgoMSD::DmpEvtRdcBgoMSD()
 :fSDID(-1)
{
}

//-------------------------------------------------------------------
DmpEvtRdcBgoMSD::~DmpEvtRdcBgoMSD(){
}

//-------------------------------------------------------------------
void DmpEvtRdcBgoMSD::SetSignal(const int &value,const short &sideID,const short &dyID){
// *
// *  TODO: check all fDyID
// *
  fDyID.push_back(sideID*10+dyID);
  fDyValue.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcBgoMSD::GetSignal(const short &sideID,const short &dyID){
  short id = sideID*10 + dyID;
  for(short i=0;i<fDyID.size();++i){
    if(fDyID[i] == id){
      return fDyValue[i];
    }
  }
}

