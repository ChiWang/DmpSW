/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-05-28 11:01:14 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
 *    Yifeng WEI (weiyf@mail.ustc.edu.cn) 24/04/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
bool DmpRdcAlgBT2012::InitialiseBgo(){
  if(fCNCTPathBgo == "NO"){
    DmpLogWarning<<"No set connector:\tBgo"<<DmpLogEndl;
    return true;
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
      return false;
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
  fBgoBarSet = new TClonesArray("DmpEvtRdcMSD",300);
  DmpIOSvc::GetInstance()->AddBranch("Rdc/Bgo",fBgoBarSet);
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventBgo(){
  fBgoBarSet->Delete();
  fBgoBarSet->Clear();
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short data=0;
  static unsigned short data2=0;
  for (feeCounts=0;feeCounts<fFEENoBgo;++feeCounts) {
    fFile.read((char*)(&data),1);
    if (data!=0xeb) {
      DmpLogError<<DmpLogEndl;
      fEvtHeader->SetErrorLog(DmpDetector::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0xeb);
      return false;
    }
    fFile.read((char*)(&data),1);
    if (data!=0x90) {
      DmpLogError<<DmpLogEndl;
      fEvtHeader->SetErrorLog(DmpDetector::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0x90);
      return false;
    }
    fFile.read((char*)(&data),1);       // trigger
    if(feeCounts == 0){
      fEvtHeader->SetTrigger(DmpDetector::kBgo,data);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetector::kBgo) != data){
        fEvtHeader->SetErrorLog(DmpDetector::kBgo,feeCounts+1,DmpEvtRdcHeader::NotMatch_Trigger);
        return false;
      }
    }
    fFile.read((char*)(&data),1);       // run mode and FEE ID
    feeID = data%16;
    if(feeCounts == 0){
      fEvtHeader->SetRunMode(DmpDetector::kBgo,data/16-fFEETypeBgo);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetector::kBgo) != data/16-fFEETypeBgo){
        DmpLogError<<DmpLogEndl;
        fEvtHeader->SetErrorLog(DmpDetector::kBgo,feeID,DmpEvtRdcHeader::NotMatch_RunMode);
        return false;
      }
    }
    fFile.read((char*)(&data),1);       // data length, 2 bytes
    fFile.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->GetRunMode(DmpDetector::kBgo) == DmpDetector::k0Compress){
      nSignal = nBytes/2;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalBgo(fMapBgo[feeID*1000+i],(data*256+data2)&0x3fff);
      }
    }else{
      nSignal = nBytes/3;
      for(short i=0;i<nSignal;++i){     // kCompress
        fFile.read((char*)(&channelID),1);
        fFile.read((char*)(&data),1);
        fFile.read((char*)(&data2),1);
        AppendSignalBgo(fMapBgo[feeID*1000+channelID],(data*256+data2)&0x3fff);
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
void DmpRdcAlgBT2012::AppendSignalBgo(const int &id, const int &v){
  static DmpEvtRdcMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fBgoBarSet->GetEntriesFast();++i){
    if(((DmpEvtRdcMSD*)fBgoBarSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fBgoBarSet->GetEntriesFast();
    aMSD = (DmpEvtRdcMSD*)fBgoBarSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtRdcMSD*)fBgoBarSet->At(index);
  }
  aMSD->SetSignal(id%100,v);
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::FinalizeBgo(){
  if(fCNCTDoneBgo){
    delete fBgoBarSet;
  }
  return true;
}


