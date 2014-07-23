/*
 *  $Id: DmpRdcAlgNud.cc, 2014-05-28 11:05:19 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcNudBlock.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpDataBufSvc.h"

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::InitializeNud(){
  if(fCNCTPathNud == "NO"){
    DmpLogWarning<<"No set connector:\tNud"<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"Setting connector:\tNud"<<DmpLogEndl;
  }
  // setup connector
// *
// *  TODO: set method?
// *
  fCNCTDoneNud = true;
  fNudBlockSet = new TClonesArray("DmpEvtRdcNudBlock",5);
  if(not gDataBufSvc->RegisterObject("Event/Rdc/Nud",fNudBlockSet)){
    fIniStatus = false;
    return;
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventNud(){
  fNudBlockSet->Delete();
  DmpLogDebug<<"[Nud] from "<<fFile.tellg();
//-------------------------------------------------------------------
// *
// *  TODO: check conversion Nud
// *
  static short feeID=0, nBytes=0, nSignal=0, data=0;
  static short runMode;
  static unsigned short data2=0;
  fFile.read((char*)(&data),1);
  if(data!=0xeb){
    fEvtHeader->SetErrorLog(DmpDetectorID::kNud,0,DmpEvtRdcHeader::NotFind_0xeb);
    return false;
  }
  fFile.read((char*)(&data),1);
  if (data!=0x90) {
    fEvtHeader->SetErrorLog(DmpDetectorID::kNud,0,DmpEvtRdcHeader::NotFind_0x90);
    return false;
  }
  fFile.read((char*)(&data),1);     // trigger
  fEvtHeader->SetTrigger(DmpDetectorID::kNud,data);
  fFile.read((char*)(&data),1);     // run mode and FEE ID
  feeID = data%16;
  runMode = data2/16-fFEETypeNud;
  fEvtHeader->SetRunMode(DmpDetectorID::kNud,runMode);
  fFile.read((char*)(&data),1);     // data length, 2 Bytes
  fFile.read((char*)(&data2),1);
  nBytes = data*256+data2-2-2;            // 2 bytes for data length, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
  //if (fEvtHeader->GetRunMode(DmpDetectorID::kNud) == DmpDetectorID::k0Compress) 
  if(runMode == DmpRunMode::k0Compress){
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


