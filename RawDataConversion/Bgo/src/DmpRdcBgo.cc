/*=============================================================================
#       FileName :          DmpRdcBgo.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-06   15:07:46
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-24   20:53:36
=============================================================================*/

#include <iostream>

#include "DmpRdc.hh"
#include "DmpEvtBgoRaw.hh"     // include DmpERunMode.hh
#include "DmpDcdParameterBgo.hh"

using namespace DmpDcdParameter::Bgo;

//------------------------------------------------------------------------------
Bool_t DmpRdc::SetConnectorBgo(){
  std::cout<<"\n\tSetup connector:\tBgo"<<std::endl;
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
      std::cout<<"\t\tOpen "<<fileName<<"\tfailed..."<<std::endl;
      return false;
    } else {
      std::cout<<"\t"<<fileName;
    }
    for(Short_t s=0;s<kSideNb;++s){
      getline(cnctFile,note);   cnctFile>>SID;
      getline(cnctFile,note);   cnctFile>>FEEID;
      getline(cnctFile,note);
      for(Short_t c=0;c<MaxSignalNb_Side;++c){
        cnctFile>>BID;
        cnctFile>>DID;
        cnctFile>>ChannelID;
        ConnectorBgo.insert(std::make_pair(FEEID*1000+ChannelID,LID*10000+BID*100+SID*10+DID));     // FEEID*1000 + ChannelID as key, since MaxSignalNb_Side = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
      }
    }
    cnctFile.close();
  }
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdc::ConversionBgo(){
  std::cout<<"\t\t\tEvent Conversion:\tBgo\t\tMode: 2013 whole Bgo"<<std::endl;
  static const Short_t  kStdDataLength0 = ((kBarNb+kRefBarNb)*kDyNb*kSideNb+3)*2;   // 3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte
  static const Short_t  kStdDataLength1 = ((kBarNb+kRefBarNb)*kDyNb+3)*2;           // kStdDataLength0 is A and B type Fee. kStdDataLength1 is C type Fee
  static Short_t feeID=0, channelID=0;
  static Short_t nChan=0, dataLong=0;
  static Short_t rawHex[2]={0};

  static Short_t pl=0,nc=0,tmp=0;     // for loop, define as static at here to save time

  fBgo->Reset();
  for (pl=0;pl<kPlaneNb*2;++pl) {
    tmp=0;
    fHexData->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      std::cout<<"\t\tBgo ----> 0xeb wrong\t"<<std::hex<<tmp<<std::endl;
      return false;
    }
    fHexData->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      std::cout<<"\t\tBgo ----> 0x90 wrong\t"<<std::hex<<tmp<<std::endl;
      return false;
    }
    fHexData->read((char*)(&tmp),1);         //trigger
    fHexData->read((char*)(&feeID),1);
    if (pl == 0) {                          //trigger check, runMode check
      fTrigger["Bgo"] = tmp;
      fBgo->SetMode(DmpEvtSubDet::DmpERunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Bgo"]) {
        std::cout<<"\t\tBgo ----> FEE trigger not match.\tLast trigger = "<<fTrigger["Bgo"]<<"\tFEE 0x"<<std::hex<<feeID<<" trigger = "<<tmp<<std::endl;
        return false;
      }
      if (feeID/16 != fBgo->GetMode()) {
        std::cout<<"\t\tBgo ----> FEE Mode not match"<<std::endl;
        return false;
      }
    }
    feeID = feeID%16;
    fHexData->read((char*)(&tmp),1);         // datalong, 2 Bytes
    fHexData->read((char*)(&dataLong),1);
    Int_t dataLength = tmp*256 + dataLong;
    if (dataLength == kStdDataLength0 || dataLength == kStdDataLength1) {
      nChan = (dataLength-2*3)/2;
    } else {
      nChan = (dataLength-2*3)/3;
    }
//std::cout<<"\t\t\t XX 2  nChan = "<<nChan<<" dL = "<<dataLength<<std::endl;

    for (nc=0;nc<nChan;++nc) {
      if (dataLength == kStdDataLength0 || dataLength == kStdDataLength1) {
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
    fHexData->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }
  return true;
}

