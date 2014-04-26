/*
 *  $Id: DmpRdcAlgNud.cc, 2014-04-17 10:48:46 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpDetectorNud.h"
#include "DmpEvtNudMSD.h"
#include "DmpEvtHeader.h"
#include "DmpRdcAlgNud.h"
#include "Rdc/DmpRdcSvcDataMgr.h"
#include "Rdc/DmpRdcSvcLog.h"
#include "DmpServiceManager.h"

DmpRdcAlgNud::DmpRdcAlgNud()
 :DmpRdcVAlgSubDet("Nud/Rdc/DefaultAlg")
{
}

//-------------------------------------------------------------------
DmpRdcAlgNud::~DmpRdcAlgNud(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgNud::ProcessThisEvent(){
  if(not fConnectorDone){
    std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    return true;
  }
  fLog->Type(0);
//-------------------------------------------------------------------
// *
// *  TODO: check conversion Nud
// *
  static short tmp=0, tmp2=0, nBytes=0;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0xeb) {
    fLog->Type(-1);
    return false;
  }
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x90) {
    fLog->Type(-2);
    return false;
  }
  fFile->read((char*)(&tmp),1);     // trigger
  fEvtHeader->SetTrigger(DmpDetector::kNud,tmp);
  fFile->read((char*)(&tmp),1);     // run mode and FEE ID
  static short feeID = 0;
  feeID = tmp%16;
  fEvtHeader->SetRunMode(DmpDetector::kNud,tmp/16-DmpDetector::Nud::kFEEType);
  fFile->read((char*)(&tmp),1);     // data length, 2 Bytes
  fFile->read((char*)(&tmp2),1);
  nBytes = tmp*256+tmp2-2-2;            // 2 bytes for data length, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
  //if (fEvtHeader->GetRunMode(DmpDetector::kNud) == DmpDetector::k0Compress) 
  for(short i=0;i<nBytes;i+=2){     // k0Compress
    fFile->read((char*)(&tmp),1);
    fFile->read((char*)(&tmp2),1);
// *
// *  TODO: store impfore into hits
// *
    //fMSDSet->
  }
  fFile->read((char*)(&tmp),1);     // 2 bytes for CRC
  fFile->read((char*)(&tmp),1);     // 2 bytes for CRC, MUST split them
//-------------------------------------------------------------------

  fLog->Type(nBytes);
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgNud::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kNud);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tNud"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tNud";
  }
// *
// *  TODO: set method?
// *
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgNud::AppendThisSignal(const int &id,const float &v){
// *
// *  TODO: example bgo
// *

}

