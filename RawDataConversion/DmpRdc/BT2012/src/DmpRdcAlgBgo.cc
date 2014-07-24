/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-06-29 20:42:16 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
 *    Yifeng WEI (weiyf@mail.ustc.edu.cn) 24/04/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcBgoBar.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpDataBufSvc.h"

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
void DmpRdcAlgBT2012::InitializeBgo(){
  if(fCNCTPathBgo == "NO"){
    DmpLogWarning<<"No set connector:\tBgo"<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"Setting connector:\tBgo"<<DmpLogEndl;
  }
  // setup connector
  short feeID=0, channelNo=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fCNCTPathBgo);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      DmpLogError<<"\t\treading cnct file ("<<iter->path().string()<<") failed"<<DmpLogEndl;
      cnctFile.close();
      fIniStatus = false;
      return;
    }else{
      std::cout<<"\t\treading cnct file: "<<iter->path().string();
    }
    cnctFile>>feeID;
    cnctFile>>channelNo;
    for(short s=0;s<channelNo;++s){
      cnctFile>>channelID;
      cnctFile>>layerID;
      cnctFile>>barID;
      cnctFile>>sideID;
      cnctFile>>dyID;
      fMapBgo.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
    std::cout<<" Done. ID = "<<feeID<<"\tN_channel = "<<channelNo<<std::endl;
  }
  fCNCTDoneBgo = true;
  fBgoBarSet = new TClonesArray("DmpEvtRdcBgoBar",300);
  if(not gDataBufSvc->RegisterObject("Event/Rdc/Bgo",fBgoBarSet)){
    fIniStatus = false;
    return;
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventBgo(){
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short  runMode;
  static short data=0;
  static unsigned short data2=0;
  fBgoBarSet->Delete();
  DmpLogDebug<<"[Bgo] from "<<fFile.tellg();
//-------------------------------------------------------------------
  for (feeCounts=0;feeCounts<fFEENoBgo;++feeCounts) {
    fFile.read((char*)(&data2),1);
    if (data!=0xeb) {
      fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0xeb);
      return false;
    }
    fFile.read((char*)(&data2),1);
    if (data2!=0x90) {
      fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0x90);
      return false;
    }
    fFile.read((char*)(&data2),1);       // trigger
    if(feeCounts == 0){
      fEvtHeader->SetTrigger(DmpDetectorID::kBgo,data2);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetectorID::kBgo) != data2){
        fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotMatch_Trigger);
        return false;
      }
    }
    fFile.read((char*)(&data2),1);       // run mode and FEE ID
    feeID = data2%16;
    runMode = data2/16-fFEETypeBgo;
    //if(feeCounts == 0){
    fEvtHeader->SetRunMode(DmpDetectorID::kBgo,runMode);
    fFile.read((char*)(&data),1);       // data length, 2 bytes
    fFile.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(runMode == DmpRunMode::kCompress){
      nSignal = nBytes/3;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // kCompress
        fFile.read((char*)(&channelID),1);
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalBgo(feeID*1000+channelID,(data*256+data2)&0x3fff);
      }
    }else{
      nSignal = nBytes/2;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalBgo(feeID*1000+i,(data*256+data2)&0x3fff);
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
void DmpRdcAlgBT2012::AppendSignalBgo(const int &globalFeeChannelID, const int &v){
  static DmpEvtRdcBgoBar *aBgoBar = 0;
  static short i=0, globalBarID=0;
  if(fMapBgo.find(globalFeeChannelID) == fMapBgo.end()){
    DmpLogError<<"Connector Key Wrong. Global Fee Channel ID: "<<globalFeeChannelID<<". ADC = "<<v<<DmpLogEndl;
    return;
  }else{
    globalBarID = fMapBgo[globalFeeChannelID]/100;
  }
  int index = -1;
  for(i=0;i<fBgoBarSet->GetEntriesFast();++i){
    if(((DmpEvtRdcBgoBar*)fBgoBarSet->At(i))->GetGlobalBarID() == globalBarID){
      index = i;
    }
  }
  if(index < 0){
    index = fBgoBarSet->GetEntriesFast();
    aBgoBar = (DmpEvtRdcBgoBar*)fBgoBarSet->ConstructedAt(index);
    aBgoBar->SetGlobalBarID(globalBarID);
  }else{
    aBgoBar = (DmpEvtRdcBgoBar*)fBgoBarSet->At(index);
  }
  aBgoBar->SetSignal(globalFeeChannelID,fMapBgo[globalFeeChannelID]%100,v);
}


