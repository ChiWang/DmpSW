/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-03-19 18:41:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpRdcAlgPsd.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtPsdHit.h"
//#include "DmpEvtHeader.h"
#include "DmpRdcConnectorInterface.h"

DmpRdcAlgPsd::DmpRdcAlgPsd()
 :fRunMe(true),
  fFile(0),
  fHits(0),
  fTrigger(0)
{
  fHits = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetHitCollection(DmpDetector::kPsd);
}

DmpRdcAlgPsd::~DmpRdcAlgPsd(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::SetupConnector(){
// *
// *  TODO:  check connector right?
// *
  std::string path = DmpRdcConnectorInterface::GetInstance()->GetConnectorPath(DmpDetector::kPsd);
  if(path == "default"){
    fRunMe = false;
    std::cout<<"\nNo set connector:\tPsd"<<std::endl;
    return true;
  }else{
    std::cout<<"\nSetting connector:\tPsd";
  }
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
static bool noFrom=true; // debug
{// debug
#ifdef DmpDebug
if(noFrom){
  std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\tfrom "<<fFile->tellg()<<std::endl;
  noFrom = false;
}
#endif
}
// *
// *  TODO: conversion bgo
// *
/*
  static const short  kFeeDataLength0 = ((BT2012::kBarNb+BT2012::kRefBarNb)*BT2012::kDyNb*BT2012::kSideNb*2+3)*2;  // 3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte.  Fee type A or B
  static const short  kFeeDataLength1 = ((BT2012::kBarNb+BT2012::kRefBarNb)*BT2012::kDyNb*BT2012::kSideNb+3)*2;   // Fee type C
  static short feeCount=0, feeID=0, channelID=0;
  static short nChan=0, dataLong=0;
  static short rawHex[2]={0};
  static short nc=0,tmp=0;     // for loop, define as static at here to save time

  fPsd->Reset();
  for (feeCount=0;feeCount<BT2012::kPlaneNb;++feeCount) {
    tmp=0;
    fFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      std::cerr<<"\nError: DmpRdcAlgorithm::ConversionPsd()\t0xeb wrong\tFee = "<<feeCount<<"\t";
      fHeader->ShowTime(0);
      return false;
    }
    fFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      std::cerr<<"\nError: DmpRdcAlgorithm::ConversionPsd()\t0x90 wrong\t";
      fHeader->ShowTime(0);
      return false;
    }
    fFile->read((char*)(&tmp),1);        //trigger
    fFile->read((char*)(&feeID),1);
    if (feeCount == 0) {                          //trigger check, runMode check
      fTrigger["Psd"] = tmp;
      fPsd->SetMode(DmpVEvtSubDet::DmpERunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Psd"]) {
        std::cerr<<"\nError: DmpRdcAlgorithm::ConversionPsd()\tFEE trigger not match\t";
        fHeader->ShowTime(0);
        return false;
      }
      if (feeID/16 != fPsd->GetMode()) {
        std::cerr<<"\nError: DmpRdcAlgorithmConversionPsd()\tFEE mode not match\t";
        fHeader->ShowTime(0);
        return false;
      }
    }
    feeID = feeID%16;
    fFile->read((char*)(&tmp),1);        // datalong, 2 Bytes
    fFile->read((char*)(&dataLong),1);
    int dataLength = tmp*256 + dataLong;
    if (dataLength == kFeeDataLength0 || dataLength == kFeeDataLength1) {
      nChan = (dataLength-2*3)/2;
    } else {
      nChan = (dataLength-2*3)/3;
    }
//std::cout<<"\t\t\t XX 2  nChan = "<<std::dec<<nChan<<" dL = "<<std::hex<<tmp<<" "<<dataLong<<std::endl;

    for (nc=0;nc<nChan;++nc) {
      if (dataLength == kFeeDataLength0 || dataLength == kFeeDataLength1) {
        channelID = nc;
      } else {
        fFile->read((char*)(&channelID),1);
      }
      fFile->read((char*)(&rawHex[0]),1);
      fFile->read((char*)(&rawHex[1]),1);
      fPsd->SetSignal(20518,rawHex[0]*256+rawHex[1]);
      fPsd->SetSignal(
        ConnectorPsd[feeID*1000+channelID],         // LBSD_ID
        rawHex[0]*256+rawHex[1]);                   // ADC
    }
    fFile->read((char*)(&tmp),2);             // reserve, 2 Bytes
    fFile->read((char*)(&tmp),2);             // CRC,     2 Bytes
//    fFile->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }

  */
{// debug
#ifdef DmpDebug
std::cout<<" to "<<fFile->tellg()<<std::endl;
noFrom = true;
#endif
}
  return true;
}


