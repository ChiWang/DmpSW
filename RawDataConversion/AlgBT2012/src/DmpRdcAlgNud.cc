/*
 *  $Id: DmpRdcAlgNud.cc, 2014-05-28 11:05:19 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::InitialiseNud(){
  if(fCNCTPathNud == "NO"){
    DmpLogWarning<<"No set connector:\tNud"<<DmpLogEndl;
    return true;
  }else{
    DmpLogInfo<<"Setting connector:\tNud"<<DmpLogEndl;
  }
  // setup connector
// *
// *  TODO: set method?
// *
  fCNCTDoneNud = true;
  fNudBlockSet = new TClonesArray("DmpEvtRdcMSD",5);
  DmpIOSvc::GetInstance()->AddBranch("Rdc/Nud",fNudBlockSet);
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventNud(){
  fNudBlockSet->Delete();
  fNudBlockSet->Clear();
//-------------------------------------------------------------------
// *
// *  TODO: check conversion Nud
// *
  static short feeID=0, nBytes=0, nSignal=0, data=0;
  static unsigned short data2=0;
  fFile.read((char*)(&data),1);
  if(data!=0xeb){
    fEvtHeader->SetErrorLog(DmpDetector::kNud,0,DmpEvtRdcHeader::NotFind_0xeb);
    return false;
  }
  fFile.read((char*)(&data),1);
  if (data!=0x90) {
    fEvtHeader->SetErrorLog(DmpDetector::kNud,0,DmpEvtRdcHeader::NotFind_0x90);
    return false;
  }
  fFile.read((char*)(&data),1);     // trigger
  fEvtHeader->SetTrigger(DmpDetector::kNud,data);
  fFile.read((char*)(&data),1);     // run mode and FEE ID
  feeID = data%16;
  fEvtHeader->SetRunMode(DmpDetector::kNud,data/16-fFEETypeNud);
  fFile.read((char*)(&data),1);     // data length, 2 Bytes
  fFile.read((char*)(&data2),1);
  nBytes = data*256+data2-2-2;            // 2 bytes for data length, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
  //if (fEvtHeader->GetRunMode(DmpDetector::kNud) == DmpDetector::k0Compress) 
  if(fEvtHeader->GetRunMode(DmpDetector::kNud) == DmpDetector::k0Compress){
    nSignal = nBytes/2;
    DmpLogDebug<<"\t---> signalNo = "<<nSignal<<DmpLogEndl;
    for(short i=0;i<nSignal;++i){     // k0Compress
      fFile.read((char*)(&data),1);
      fFile.read((char*)(&data2),1);
// *
// *  TODO: store impfore into hits
// *
    //fNudBlockSet->
    }
  }else{
    nSignal = nBytes/3;
    DmpLogDebug<<"\t---> signalNo = "<<nSignal<<DmpLogEndl;
    for(short i=0;i<nSignal;++i){     // kCompress
    }
  }
  fFile.read((char*)(&data),1);     // 2 bytes for CRC
  fFile.read((char*)(&data),1);     // 2 bytes for CRC, MUST split them
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::AppendSignalNud(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::FinalizeNud(){
  if(fCNCTDoneNud){
    delete fNudBlockSet;
  }
  return true;
}

