/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-03-21 09:34:01 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpRdcAlgPsd.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtPsdHit.h"
#include "DmpDetectorPsd.h"
#include "DmpEvtHeader.h"
#include "DmpRdcConnectorInterface.h"

DmpRdcAlgPsd::DmpRdcAlgPsd(){
  fHitCollection = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetHitCollection(DmpDetector::kPsd);
}

//-------------------------------------------------------------------
DmpRdcAlgPsd::~DmpRdcAlgPsd(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::SetupConnector(){
  std::string path = DmpRdcConnectorInterface::GetInstance()->GetConnectorPath(DmpDetector::kPsd);
  if(path == "default"){
    std::cout<<"\nNo set connector:\tPsd"<<std::endl;
    return true;
  }else{
    fRunMe = true;
    std::cout<<"\nSetting connector:\tPsd";
  }
// *
// *  TODO:  check connector right?
// *
/*
  int FEEID, ChannelID;
  short LID, BID, SID, DID;
  int const MaxSignalNb_Side = (BT2012::kBarNb+BT2012::kRefBarNb)*BT2012::kDyNb;
  std::string note;
  char fileName[20];
  for(short l=0;l<BT2012::kPlaneNb*2;++l){
    LID = l;
    sprintf(fileName,"Layer_%d.cnct",l);
    ifstream cnctFile(path+fileName);
    if (!cnctFile.good()) {
      std::cerr<<"Error: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\tRead "<<fileName<<"\tfailed..."<<std::endl;
      return false;
    }
    for(short s=0;s<BT2012::kSideNb;++s){
      getline(cnctFile,note);   // reserved 1 line for note
      cnctFile>>SID;
      getline(cnctFile,note);   // reserved 1 line for note
      cnctFile>>FEEID;
      getline(cnctFile,note);   // reserved 1 line for note
      for(short c=0;c<MaxSignalNb_Side;++c){
        cnctFile>>BID;
        cnctFile>>DID;
        cnctFile>>ChannelID;
        ConnectorPsd.insert(std::make_pair(FEEID*1000+ChannelID,LID*10000+BID*100+SID*10+DID));     // FEEID*1000 + ChannelID as key, since MaxSignalNb_Side = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
      }
    }
    cnctFile.close();
  }
*/
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::Convert(){
  if(not fRunMe) return true;
  std::cout<<"\t"<<__PRETTY_FUNCTION__;
  StatusLog(0);
// *
// *  TODO: conversion Psd
// *
//-------------------------------------------------------------------
  static short tmp=0, tmp2 = 0, nBytes = 0;
  for (short FEEID=0;FEEID<DmpDetector::Psd::Quarter::kFEENo;++FEEID) {
    sFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      StatusLog(-1);
      return false;
    }
    sFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      StatusLog(-2);
      return false;
    }
    sFile->read((char*)(&tmp),1);       // trigger
    if(FEEID == 0){
      sHeader->SetTrigger(DmpDetector::kPsd,tmp);
    }else{
      if(sHeader->GetTrigger(DmpDetector::kPsd) != tmp){
        StatusLog(-3);
        return false;
      }
    }
    sFile->read((char*)(&tmp),1);       // run mode and FEE ID
    if(FEEID == 0){
      sHeader->SetRunMode(DmpDetector::kPsd,tmp/16);
    }else{
      if(sHeader->GetRunMode(DmpDetector::kPsd) != tmp/16){
        StatusLog(-4);
        return false;
      }
    }
    sFile->read((char*)(&tmp),1);       // data length, 2 bytes
    sFile->read((char*)(&tmp2),1);
    nBytes = tmp*256+tmp2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(sHeader->GetRunMode(DmpDetector::kPsd) == DmpDetector::k0Compress){
      for(short i=0;i<nBytes;i+=2){     // k0Compress
        sFile->read((char*)(&tmp),1);
        sFile->read((char*)(&tmp),1);
// *
// *  TODO: add hits information
// *
        //fHitCollection->
      //fPsd->SetSignal(
      //  ConnectorPsd[feeID*1000+channelID],         // LBSD_ID
      //  rawHex[0]*256+rawHex[1]);                   // ADC
      }
    }else{
      for(short i=0;i<nBytes;i+=3){     // kCompress
        sFile->read((char*)(&tmp),1);
        sFile->read((char*)(&tmp),1);
        sFile->read((char*)(&tmp),1);
// *
// *  TODO: add hits information
// *
        //fHitCollection->
      //fPsd->SetSignal(
      //  ConnectorPsd[feeID*1000+channelID],         // LBSD_ID
      //  rawHex[0]*256+rawHex[1]);                   // ADC
      }
    }
    sFile->read((char*)(&tmp),1);       // 2 bytes for 0x0000
    sFile->read((char*)(&tmp),1);       // must split them, 2 bytes for 0x0000
    sFile->read((char*)(&tmp),1);       // 2 bytes for CRC
    sFile->read((char*)(&tmp),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------

  StatusLog(nBytes);
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgPsd::AppendThisSignal(const int &id,const float &v){
}

