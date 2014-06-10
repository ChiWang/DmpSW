/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-05-28 13:10:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::InitialisePsd(){
  if(fCNCTPathPsd == "NO"){
    DmpLogWarning<<"No set connector:\tPsd"<<DmpLogEndl;
    return true;
  }else{
    DmpLogInfo<<"Setting connector:\tPsd"<<DmpLogEndl;
  }
  // setup connector
// *
// *  TODO:  check connector right?
// *
  fCNCTDonePsd = true;
  fPsdStripSet = new TClonesArray("DmpEvtRdcMSD",90);
  DmpIOSvc::GetInstance()->AddBranch("Rdc/Psd",fPsdStripSet);
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventPsd(){
  fPsdStripSet->Delete();
  fPsdStripSet->Clear();
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short data=0;
  static unsigned short data2=0;
  for(feeCounts=0;feeCounts<fFEENoPsd;++feeCounts){
    fFile.read((char*)(&data),1);
    if (data!=0xeb) {
      DmpLogError<<"value "<<std::hex<<data<<std::dec<<DmpLogEndl;
      fEvtHeader->SetErrorLog(DmpDetector::kPsd,feeCounts+1,DmpEvtRdcHeader::NotFind_0xeb);
      return false;
    }
    fFile.read((char*)(&data),1);
    if (data!=0x90) {
      DmpLogError<<DmpLogEndl;
      fEvtHeader->SetErrorLog(DmpDetector::kPsd,feeCounts+1,DmpEvtRdcHeader::NotFind_0x90);
      return false;
    }
    fFile.read((char*)(&data),1);       // trigger
    if(feeCounts == 0){
      fEvtHeader->SetTrigger(DmpDetector::kPsd,data);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetector::kPsd) != data){
        DmpLogError<<DmpLogEndl;
        fEvtHeader->SetErrorLog(DmpDetector::kPsd,feeCounts+1,DmpEvtRdcHeader::NotMatch_Trigger);
        return false;
      }
    }
    fFile.read((char*)(&data),1);       // run mode and FEE ID
    feeID = data%16;
    if(feeCounts == 0){
      fEvtHeader->SetRunMode(DmpDetector::kPsd,data/16-fFEETypePsd);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetector::kPsd) != data/16-fFEETypePsd){
        DmpLogError<<DmpLogEndl;
        fEvtHeader->SetErrorLog(DmpDetector::kPsd,feeID,DmpEvtRdcHeader::NotMatch_RunMode);
        return false;
      }
    }
    fFile.read((char*)(&data),1);       // data length, 2 bytes
    fFile.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->GetRunMode(DmpDetector::kPsd) == DmpDetector::k0Compress){
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
    fFile.read((char*)(&data),1);       // 2 bytes for 0x0000
    fFile.read((char*)(&data),1);       // must split them, 2 bytes for 0x0000
    fFile.read((char*)(&data),1);       // 2 bytes for CRC
    fFile.read((char*)(&data),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::AppendSignalPsd(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::FinalizePsd(){
  if(fCNCTDonePsd){
    delete fPsdStripSet;
  }
  return true;
}
