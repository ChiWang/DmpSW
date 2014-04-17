/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-04-17 10:48:48 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpDetectorBgo.h"
#include "DmpEvtBgoMSD.h"
#include "DmpEvtHeader.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpServiceManager.h"

DmpRdcAlgBgo::DmpRdcAlgBgo()
 :DmpRdcVAlgSubDet("Rdc/Bgo/DefaultAlg")
{
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
//-------------------------------------------------------------------
  static short tmp=0, tmp2=0, nBytes=0;
  for (short counts=0;counts<DmpDetector::Bgo::kFEENo;++counts) {
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
    fFile->read((char*)(&tmp),1);       // trigger
    if(counts == 0){
      fEvtHeader->SetTrigger(DmpDetector::kBgo,tmp);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetector::kBgo) != tmp){
        fLog->Type(-3);
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // run mode and FEE ID
    static short feeID = 0;
    feeID = tmp%16;
    if(counts == 0){
      fEvtHeader->SetRunMode(DmpDetector::kBgo,tmp/16-DmpDetector::Bgo::kFEEType);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetector::kBgo) != tmp/16-DmpDetector::Bgo::kFEEType){
        fLog->Type(-4);
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // data length, 2 bytes
    fFile->read((char*)(&tmp2),1);
    nBytes = tmp*256+tmp2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->GetRunMode(DmpDetector::kBgo) == DmpDetector::k0Compress){
      for(short i=0;i<nBytes;i+=2){     // k0Compress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
        AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }else{
      for(short i=0;i<nBytes;i+=3){     // kCompress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
// *
// *  TODO: open me
// *
        //AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }
    fFile->read((char*)(&tmp),1);       // 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // must split them, 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // 2 bytes for CRC
    fFile->read((char*)(&tmp),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  fLog->Type(nBytes);
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
    std::cout<<"\n\tSetting connector:\tBgo";
  }
  short feeID=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fConnectorPath);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      std::cout<<"reading cnct file ("<<fConnectorPath<<") failed"<<std::endl;
      cnctFile.close();
      return false;
    }
    cnctFile>>feeID;
    for(short s=0;s<DmpDetector::Bgo::kFEEChannelNo;++s){
      cnctFile>>channelID;
      cnctFile>>layerID;
      cnctFile>>barID;
      cnctFile>>sideID;
      cnctFile>>dyID;
      fConnector.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
  }
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBgo::AppendThisSignal(const int &id, const float &v){
  static DmpEvtBgoMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtBgoMSD*)fMSDSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fMSDSet->GetEntriesFast();
    aMSD = (DmpEvtBgoMSD*)fMSDSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
    //std::cout<<"\nadd new bar = "<<barID;
  }else{
    aMSD = (DmpEvtBgoMSD*)fMSDSet->At(index);
  }
  aMSD->SetSignal(id%100,v);
}


