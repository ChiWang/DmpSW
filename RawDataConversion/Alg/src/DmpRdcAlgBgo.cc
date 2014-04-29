/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-04-26 09:58:29 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
 *    Yifeng WEI (weiyf@mail.ustc.edu.cn) 24/04/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpDetectorBgo.h"
#include "DmpEvtRdcBgoMSD.h"
#include "DmpEvtRdcHeader.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpServiceManager.h"

DmpRdcAlgBgo::DmpRdcAlgBgo()
 :DmpRdcVAlgSubDet("Bgo/Rdc/2014"),
  fFEEType(0),
  fFEENo(16)
{
std::cout<<"DEBUG: (for 2014)"<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
}

//-------------------------------------------------------------------
DmpRdcAlgBgo::~DmpRdcAlgBgo(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgBgo::ProcessThisEvent(){
  if(not fConnectorDone){
    std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    return true;
  }
  fLog->Type(0);
  fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(0,DmpRdcHeaderSubDet::k_good);       // the first element for whole subDet
//-------------------------------------------------------------------
  static short data=0, data2=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  for(short counts=0;counts<fFEENo;++counts){
    fFile->read((char*)(&data),1);
    if(data != 0xeb){
std::cout<<" xxzz1 = "<<std::hex<<data<<std::dec<<" tellg = "<<fFile->tellg()<<std::endl;
      return false;
    }
    fFile->read((char*)(&data),1);
    if(data != 0x90){
std::cout<<" xxzz2 = "<<std::hex<<data<<std::dec<<" tellg = "<<fFile->tellg()<<std::endl;
      fLog->Type(-1);
      fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(counts+1,DmpRdcHeaderSubDet::k_eb90);
      return false;
    }
    fFile->read((char*)(&data),1);       // reserved 1 byte
    fFile->read((char*)(&data),1);       // run mode and FEE ID
    feeID = data%16;
    if(counts == 0){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetRunMode(data/16-fFEEType);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kBgo)->RunMode() != data/16-fFEEType){
        fLog->Type(-4);
        return false;
      }
    }
    fFile->read((char*)(&data),1);       // data length, 2 bytes
    fFile->read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for trigger, 2 bytes for CRC
// *
// *  TODO: check data length
// *
    if(fEvtHeader->Detector(DmpDetector::kBgo)->RunMode() == DmpDetector::k0Compress){
      nSignal = nBytes/2;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fFile->read((char*)(&data),1);
        fFile->read((char*)(&data2),1);
        AppendThisSignal(fConnector[feeID*1000+i],data*256+data2);
      }
    }else{
      nSignal = nBytes/3;
      for(short i=0;i<nSignal;++i){     // kCompress
        fFile->read((char*)(&channelID),1);
        fFile->read((char*)(&data),1);
        fFile->read((char*)(&data2),1);
        if(fConnector[feeID*1000+channelID] != 0){
          AppendThisSignal(fConnector[feeID*1000+channelID],data*256+data2);
        //}else{
          //std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<" FeeID = "<<feeID<<" cha = "<<channelID<<" physi = "<<data*256+data2<<std::endl;
        }
      }
      if(nBytes%3){     // nBytes%3 == 1
        fFile->read((char*)(&data),1);
      }
    }
    fFile->read((char*)(&data),1);       // trigger status
    fFile->read((char*)(&data),1);       // trigger
    if(counts == 0){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetTrigger(data);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kBgo)->Trigger() != data){
        fLog->Type(-3);
        return false;
      }
    }
    fFile->read((char*)(&data),1);       // 2 bytes for CRC
    fFile->read((char*)(&data),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  fLog->Type(nSignal);
  return true;
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
bool DmpRdcAlgBgo::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kBgo);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tBgo"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tBgo"<<std::endl;
  }
  short feeID=0, channelNo=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fConnectorPath);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      std::cout<<"\t\treading cnct file ("<<iter->path().string()<<") failed"<<std::endl;
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
      fConnector.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
    std::cout<<" Done. ID = "<<feeID<<"\tN_channel = "<<channelNo<<std::endl;
  }
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBgo::AppendThisSignal(const int &id, const float &v){
  static DmpEvtRdcBgoMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtRdcBgoMSD*)fMSDSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fMSDSet->GetEntriesFast();
    aMSD = (DmpEvtRdcBgoMSD*)fMSDSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtRdcBgoMSD*)fMSDSet->At(index);
  }
  aMSD->SetSignal(v,id%100);
}


