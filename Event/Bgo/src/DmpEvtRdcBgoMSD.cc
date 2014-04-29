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
void DmpEvtRdcBgoMSD::SetSignal(const int &value,const short &side_dyID){
  fDyID.push_back(side_dyID);
  fDyValue.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcBgoMSD::GetSignal(const short &side_dyID) const{
  for(short i=0;i<fDyID.size();++i){
    if(fDyID[i] == side_dyID){
      return fDyValue[i];
    }
  }
}

