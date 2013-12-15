/*=====================================================================
 *   File:   DmpRdcBgo.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:31:21
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
  std::cout<<"\tEvent Conversion:\tBgo\t\tMode: 2013 whole Bgo"<<std::endl;
  static const Short_t  kStdDataLength0 = ((kBarNb+kRefBarNb)*kDyNb*kSideNb+3)*2;   // 3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte
  static Short_t feeID=0, channelID=0;
  static Short_t nChan=0, dataLong=0;
  static Short_t rawHex[2]={0};

  static Short_t pl=0,nc=0,tmp=0;     // for loop, define as static at here to save time

  fBgo->Reset();
  for (pl=0;pl<kPlaneNb*2;++pl) {
    tmp=0;
    fHexData->read((char*)(&tmp),1);
std::cerr<<" at = "<<fHexData->tellg();
    if (tmp!=0xeb) {
      std::cerr<<"Error: DmpRdcManager::ConversionBgo()\t0xeb wrong iii\t";
#ifdef Dmp_DEBUG
      std::cerr<<tmp<<std::endl;
#endif
      fHeader->ShowTime(0);
      return false;
    }
    fHexData->read((char*)(&tmp),1);
std::cerr<<" xxxx at = "<<fHexData->tellg();
    if (tmp!=0x90) {
      std::cerr<<"Error: DmpRdcManager::ConversionBgo()\t0x90 wrong\t";
      fHeader->ShowTime(0);
      return false;
    }
    fHexData->read((char*)(&tmp),1);        //trigger
std::cerr<<" 1 at = "<<fHexData->tellg();
    fHexData->read((char*)(&feeID),1);
std::cerr<<" 2 at = "<<fHexData->tellg();
    if (pl == 0) {                          //trigger check, runMode check
      fTrigger["Bgo"] = tmp;
      fBgo->SetMode(DmpEvtSubDet::DmpERunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Bgo"]) {
        std::cerr<<"Error: DmpRdcManager::ConversionBgo()\tFEE trigger not match\t";
        fHeader->ShowTime(0);
        return false;
      }
      if (feeID/16 != fBgo->GetMode()) {
        std::cerr<<"Error: DmpRdcManagerConversionBgo()\tFEE mode not match\t";
        fHeader->ShowTime(0);
        return false;
      }
    }
    feeID = feeID%16;
    fHexData->read((char*)(&tmp),1);        // datalong, 2 Bytes
std::cerr<<" 3 at = "<<fHexData->tellg();
    fHexData->read((char*)(&dataLong),1);
std::cerr<<" 4 at = "<<fHexData->tellg();
    Int_t dataLength = tmp*256 + dataLong;
    if (dataLength == kStdDataLength0) {
      nChan = (dataLength-2*3)/2;
    } else {
      nChan = (dataLength-2*3)/3;
    }
std::cout<<"\t\t\t XX 2  nChan = "<<nChan<<" dL = "<<std::hex<<tmp<<" "<<dataLong<<std::endl;

    for (nc=0;nc<nChan;++nc) {
      if (dataLength == kStdDataLength0) {
        channelID = nc;
      } else {
        fHexData->read((char*)(&channelID),1);
std::cerr<<" (nc = "<<nc<<") at = "<<fHexData->tellg();
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
    fHexData->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }
  return true;
}


