/*
 *  $Id: DmpEvtRdcMSD.cc, 2014-04-29 22:47:00 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#include "DmpEvtRdcMSD.h"

//-------------------------------------------------------------------
DmpEvtRdcMSD::DmpEvtRdcMSD()
 :fSDID(-1)
{
}

//-------------------------------------------------------------------
DmpEvtRdcMSD::~DmpEvtRdcMSD(){
}

//-------------------------------------------------------------------
void DmpEvtRdcMSD::SetSignal(const int &signalID,const short &value){
  fSignalID.push_back(signalID);
  fSignalValue.push_back(value);
}

//-------------------------------------------------------------------
int DmpEvtRdcMSD::GetSignal(const short &signalID) const{
  for(short i=0;i<fSignalID.size();++i){
    if(fSignalID[i] == signalID){
      return fSignalValue[i];
    }
  }
}

