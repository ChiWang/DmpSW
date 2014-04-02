/*
 *  $Id: DmpRdcAlgStk.cc, 2014-03-21 00:26:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpRdcAlgStk.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtStkHit.h"
#include "DmpEvtHeader.h"

DmpRdcAlgStk::DmpRdcAlgStk(const std::string &name)
 :DmpRdcVAlgSubDet(name)
{
  fHitCollection = gDataMgr->GetRawEvent()->GetHitCollection(DmpDetector::kStk);
}

//-------------------------------------------------------------------
DmpRdcAlgStk::~DmpRdcAlgStk(){
}

//-------------------------------------------------------------------
#include "DmpRdcCnctPath.h"
bool DmpRdcAlgStk::Initialize(){
  std::string path = DmpRdcCnctPath::GetInstance()->GetConnectorPath(DmpDetector::kStk);
  if(path == "default"){
    std::cout<<"\nNo set connector:\tStk"<<std::endl;
    return true;
  }else{
    fRunMe = true;
    std::cout<<"\nSetting connector:\tStk";
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
        ConnectorStk.insert(std::make_pair(FEEID*1000+ChannelID,LID*10000+BID*100+SID*10+DID));     // FEEID*1000 + ChannelID as key, since MaxSignalNb_Side = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
      }
    }
    cnctFile.close();
  }
*/
  return true;
}

//-------------------------------------------------------------------
#include "DmpRdcLog.h"
bool DmpRdcAlgStk::ProcessThisEvent(){
  if(not fRunMe) return true;
  std::cout<<"\t"<<__PRETTY_FUNCTION__;
  gRdcLog->StatusLog(0);
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------
/*
  static const short  kFeeDataLength0 = ((BT2012::kBarNb+BT2012::kRefBarNb)*BT2012::kDyNb*BT2012::kSideNb*2+3)*2;  // 3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte.  Fee type A or B
  static const short  kFeeDataLength1 = ((BT2012::kBarNb+BT2012::kRefBarNb)*BT2012::kDyNb*BT2012::kSideNb+3)*2;   // Fee type C
  static short feeCount=0, feeID=0, channelID=0;
  static short nChan=0, dataLong=0;
  static short rawHex[2]={0};
  static short nc=0,tmp=0;     // for loop, define as static at here to save time

  fStk->Reset();
  for (feeCount=0;feeCount<BT2012::kPlaneNb;++feeCount) {
    tmp=0;
    sFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      std::cerr<<"\nError: DmpRdcAlgorithm::ConversionStk()\t0xeb wrong\tFee = "<<feeCount<<"\t";
      sHeader->ShowTime(0);
      return false;
    }
    sFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      std::cerr<<"\nError: DmpRdcAlgorithm::ConversionStk()\t0x90 wrong\t";
      sHeader->ShowTime(0);
      return false;
    }
    sFile->read((char*)(&tmp),1);        //trigger
    sFile->read((char*)(&feeID),1);
    if (feeCount == 0) {                          //trigger check, runMode check
      fTrigger["Stk"] = tmp;
      fStk->SetMode(DmpVEvtSubDet::DmpERunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Stk"]) {
        std::cerr<<"\nError: DmpRdcAlgorithm::ConversionStk()\tFEE trigger not match\t";
        sHeader->ShowTime(0);
        return false;
      }
      if (feeID/16 != fStk->GetMode()) {
        std::cerr<<"\nError: DmpRdcAlgorithmConversionStk()\tFEE mode not match\t";
        sHeader->ShowTime(0);
        return false;
      }
    }
    feeID = feeID%16;
    sFile->read((char*)(&tmp),1);        // datalong, 2 Bytes
    sFile->read((char*)(&dataLong),1);
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
        sFile->read((char*)(&channelID),1);
      }
      sFile->read((char*)(&rawHex[0]),1);
      sFile->read((char*)(&rawHex[1]),1);
      fStk->SetSignal(20518,rawHex[0]*256+rawHex[1]);
      fStk->SetSignal(
        ConnectorStk[feeID*1000+channelID],         // LBSD_ID
        rawHex[0]*256+rawHex[1]);                   // ADC
    }
    sFile->read((char*)(&tmp),2);             // reserve, 2 Bytes
    sFile->read((char*)(&tmp),2);             // CRC,     2 Bytes
//    sFile->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }
*/
//-------------------------------------------------------------------

  gRdcLog->StatusLog(1);
  return true;
}

void DmpRdcAlgStk::AppendThisSignal(const int &id,const float &v){
}

