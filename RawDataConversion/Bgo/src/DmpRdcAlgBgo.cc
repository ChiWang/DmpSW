/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-03-21 09:34:01 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpRdcAlgBgo.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtBgoHit.h"
#include "DmpEvtHeader.h"
#include "DmpDetectorBgo.h"

DmpRdcAlgBgo::DmpRdcAlgBgo(const std::string &name)
 :DmpRdcVAlgSubDet(name)
{
  fHitCollection = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetHitCollection(DmpDetector::kBgo);
}

//-------------------------------------------------------------------
DmpRdcAlgBgo::~DmpRdcAlgBgo(){
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "DmpRdcConnectorInterface.h"
bool DmpRdcAlgBgo::Initialize(){
  std::string path = DmpRdcConnectorInterface::GetInstance()->GetConnectorPath(DmpDetector::kBgo);
  if(path == "default"){
    std::cout<<"No set connector:\tBgo"<<std::endl;
    return true;
  }else{
    fRunMe = true;
    std::cout<<"\nSetting connector:\tBgo";
  }
  static short feeID=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(path);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (!cnctFile.good())   return false;
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
  return true;
}

//-------------------------------------------------------------------
#include "DmpRdcLog.h"
bool DmpRdcAlgBgo::ProcessThisEvent(){
  if(not fRunMe) return true;
  std::cout<<"\t"<<__PRETTY_FUNCTION__;
  gRdcLog->StatusLog(0);
//-------------------------------------------------------------------
  static short tmp=0, tmp2=0, nBytes=0;
  std::ifstream *&inFile = DmpRdcDataManager::GetInstance()->gInFile;
  for (short counts=0;counts<DmpDetector::Bgo::kFEENo;++counts) {
    inFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      gRdcLog->StatusLog(-1);
      return false;
    }
    inFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      gRdcLog->StatusLog(-2);
      return false;
    }
    inFile->read((char*)(&tmp),1);       // trigger
    if(counts == 0){
      sHeader->SetTrigger(DmpDetector::kBgo,tmp);
    }else{
      if(sHeader->GetTrigger(DmpDetector::kBgo) != tmp){
        gRdcLog->StatusLog(-3);
        return false;
      }
    }
    inFile->read((char*)(&tmp),1);       // run mode and FEE ID
    static short feeID = 0;
    feeID = tmp%16;
    if(counts == 0){
      sHeader->SetRunMode(DmpDetector::kBgo,tmp/16-DmpDetector::Bgo::kFEEType);
    }else{
      if(sHeader->GetRunMode(DmpDetector::kBgo) != tmp/16-DmpDetector::Bgo::kFEEType){
        gRdcLog->StatusLog(-4);
        return false;
      }
    }
    inFile->read((char*)(&tmp),1);       // data length, 2 bytes
    inFile->read((char*)(&tmp2),1);
    nBytes = tmp*256+tmp2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(sHeader->GetRunMode(DmpDetector::kBgo) == DmpDetector::k0Compress){
      for(short i=0;i<nBytes;i+=2){     // k0Compress
        inFile->read((char*)(&tmp),1);
        inFile->read((char*)(&tmp2),1);
        AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }else{
      for(short i=0;i<nBytes;i+=3){     // kCompress
// *
// *  TODO: fix me
// *
        inFile->read((char*)(&tmp),1);
        inFile->read((char*)(&tmp),1);
        inFile->read((char*)(&tmp2),1);
        //AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }
    inFile->read((char*)(&tmp),1);       // 2 bytes for 0x0000
    inFile->read((char*)(&tmp),1);       // must split them, 2 bytes for 0x0000
    inFile->read((char*)(&tmp),1);       // 2 bytes for CRC
    inFile->read((char*)(&tmp),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------

  gRdcLog->StatusLog(nBytes);
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBgo::AppendThisSignal(const int &id, const float &v){
  static DmpEvtBgoHit *aHit = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fHitCollection->GetEntriesFast();++i){
    if(((DmpEvtBgoHit*)fHitCollection->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fHitCollection->GetEntriesFast();
    aHit = (DmpEvtBgoHit*)fHitCollection->ConstructedAt(index);
    aHit->SetSDID(barID);
    //std::cout<<"\nadd new bar = "<<barID;
  }else{
    aHit = (DmpEvtBgoHit*)fHitCollection->At(index);
  }
  aHit->SetSignal(id%100,v);
}


