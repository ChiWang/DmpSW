/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-05-28 13:10:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtHeader.h"
#include "DmpEvtRdcPsdStrip.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpDataBuffer.h"

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::InitializePsd(){
  if(fCNCTPathPsd == "NO"){
    DmpLogWarning<<"No set connector:\tPsd"<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"Setting connector:\tPsd"<<DmpLogEndl;
  }
  // setup connector
// *
// *  TODO:  check connector right?
// *
  fCNCTDonePsd = true;
  fPsdStripSet = new TClonesArray("DmpEvtRdcPsdStrip",90);
  if(not gDataBuffer->RegisterObject("Event/Rdc/Psd",fPsdStripSet)){
    fIniStatus = false;
    return;
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventPsd(){
  fPsdStripSet->Delete();
  DmpLogDebug<<"[Psd] from "<<fFile.tellg();
//-------------------------------------------------------------------
  static short feeCounts=0, trigger=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short runMode;
  static char data=0;
  static unsigned char data2=0;
  for(feeCounts=0;feeCounts<fFEENoPsd;++feeCounts){
    fFile.read((char*)(&data2),1);
    if (data2!=0xeb) {
      fEvtHeader->SetFeeErrorTag(DmpDetectorID::kPsd,feeCounts+1,DmpDataError::NotFind_0xeb);
      return false;
    }
    fFile.read((char*)(&data2),1);
    if (data2!=0x90) {
      fEvtHeader->SetFeeErrorTag(DmpDetectorID::kPsd,feeCounts+1,DmpDataError::NotFind_0x90);
      return false;
    }
    fFile.read((char*)(&data2),1);       // trigger
    trigger = data2;
    fFile.read((char*)(&data2),1);       // run mode and FEE ID
    feeID = data2%16;
    runMode = data2/16-fFEETypePsd;
    fEvtHeader->SetFeeStatus(DmpDetectorID::kPsd,feeID,trigger,runMode);
    fFile.read((char*)(&data),1);       // data length, 2 bytes
    fFile.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(runMode == DmpRunMode::k0Compress){
      nSignal = nBytes/2;
      DmpLogDebug<<"\t---> signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalPsd(fMapPsd[feeID*1000+i],data*256+data2);
      }
    }else{
      nSignal = nBytes/3;
      DmpLogDebug<<"\t---> signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // kCompress
        fFile.read((char*)(&channelID),1);
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalPsd(fMapPsd[feeID*1000+channelID],data*256+data2);
      }
    }
    fFile.read((char*)(&data2),1);       // 2 bytes for 0x0000
    fFile.read((char*)(&data2),1);       // must split them, 2 bytes for 0x0000
    fFile.read((char*)(&data2),1);       // 2 bytes for CRC
    fFile.read((char*)(&data2),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::AppendSignalPsd(const int &id,const int &v){
// *
// *  TODO: example bgo
// 
}

