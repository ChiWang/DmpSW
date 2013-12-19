/*=====================================================================
 *   File:   DmpRdcBgo.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *      implement member functions of class DmpRdcManager (Bgo part)
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  15/12/2013   15:51:21
=====================================================================*/

#include <iostream>

#include "DmpRdcManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpEvtBgoRaw.hh"     // include DmpERunMode.hh
#include "DmpParameterBgo.hh"

using namespace DmpParameter::Bgo;

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::SetConnectorBgo(){
  std::cout<<"\nSetup connector:\tBgo"<<std::endl;
  std::cout<<"-----------------------"<<std::endl;
  Int_t FEEID, ChannelID;
  Short_t LID, BID, SID, DID;
  Int_t const MaxSignalNb_Side = (kBarNb+kRefBarNb)*kDyNb;
  std::string note;
  char fileName[20];

  for(Short_t l=0;l<kPlaneNb*2;++l){
    LID = l;
    sprintf(fileName,"Layer_%d.cnct",l);
    ifstream cnctFile(fConnectorPath+"/Bgo/"+fileName);
    if (!cnctFile.good()) {
      std::cerr<<"Error: DmpRdcManager::SetConnectorBgo():\tRead "<<fileName<<"\tfailed..."<<std::endl;
      return false;
    } else {
      std::cout<<"\t"<<fileName;
    }
    for(Short_t s=0;s<kSideNb;++s){
      getline(cnctFile,note);   // reserved 1 line for note
      cnctFile>>SID;
      getline(cnctFile,note);   // reserved 1 line for note
      cnctFile>>FEEID;
      getline(cnctFile,note);   // reserved 1 line for note
      for(Short_t c=0;c<MaxSignalNb_Side;++c){
        cnctFile>>BID;
        cnctFile>>DID;
        cnctFile>>ChannelID;
        ConnectorBgo.insert(std::make_pair(FEEID*1000+ChannelID,LID*10000+BID*100+SID*10+DID));     // FEEID*1000 + ChannelID as key, since MaxSignalNb_Side = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
      }
    }
    cnctFile.close();
  }
  std::cout<<"\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionBgo(){
#ifdef Dmp_DEBUG
std::cerr<<"\t\t-->Bgo from "<<std::dec<<fHexData->tellg();
#endif
  static const Short_t  kFeeDataLength0 = ((kBarNb+kRefBarNb)*kDyNb*kSideNb*2+3)*2;  // 3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte.  Fee type A or B
  static const Short_t  kFeeDataLength1 = ((kBarNb+kRefBarNb)*kDyNb*kSideNb+3)*2;   // Fee type C
  static Short_t feeCount=0, feeID=0, channelID=0;
  static Short_t nChan=0, dataLong=0;
  static Short_t rawHex[2]={0};
  static Short_t nc=0,tmp=0;     // for loop, define as static at here to save time

  fBgo->Reset();
  for (feeCount=0;feeCount<kPlaneNb;++feeCount) {
    tmp=0;
    fHexData->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      std::cerr<<"\nError: DmpRdcManager::ConversionBgo()\t0xeb wrong\tFee = "<<feeCount<<"\t";
      fHeader->ShowTime(0);
      return false;
    }
    fHexData->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      std::cerr<<"\nError: DmpRdcManager::ConversionBgo()\t0x90 wrong\t";
      fHeader->ShowTime(0);
      return false;
    }
    fHexData->read((char*)(&tmp),1);        //trigger
    fHexData->read((char*)(&feeID),1);
    if (feeCount == 0) {                          //trigger check, runMode check
      fTrigger["Bgo"] = tmp;
      fBgo->SetMode(DmpVEvtSubDet::DmpERunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Bgo"]) {
        std::cerr<<"\nError: DmpRdcManager::ConversionBgo()\tFEE trigger not match\t";
        fHeader->ShowTime(0);
        return false;
      }
      if (feeID/16 != fBgo->GetMode()) {
        std::cerr<<"\nError: DmpRdcManagerConversionBgo()\tFEE mode not match\t";
        fHeader->ShowTime(0);
        return false;
      }
    }
    feeID = feeID%16;
    fHexData->read((char*)(&tmp),1);        // datalong, 2 Bytes
    fHexData->read((char*)(&dataLong),1);
    Int_t dataLength = tmp*256 + dataLong;
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
        fHexData->read((char*)(&channelID),1);
      }
      fHexData->read((char*)(&rawHex[0]),1);
      fHexData->read((char*)(&rawHex[1]),1);
      fBgo->SetSignal(20518,rawHex[0]*256+rawHex[1]);
/*
      fBgo->SetSignal(
        ConnectorBgo[feeID*1000+channelID],         // LBSD_ID
        rawHex[0]*256+rawHex[1]);                   // ADC
*/
    }
    fHexData->read((char*)(&tmp),2);             // reserve, 2 Bytes
    fHexData->read((char*)(&tmp),2);             // CRC,     2 Bytes
//    fHexData->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }

#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
#endif

  return true;
}


