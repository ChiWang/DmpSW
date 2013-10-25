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

#include "DmpRdcManager.hh"

#include "DmpDcdParameterBgo.hh"
#include "DmpEvtBgo.hh"     // include DmpDcdRunMode.hh

using namespace DmpDcdParameter::Bgo;

void DmpRdcManager::ConstructorBgo(){
  fEvtBgo   = new DmpEvtBgoRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpRdcManager::DestructorBgo(){
  delete fEvtBgo;
}

Bool_t DmpRdcManager::SetConnectorBgo(){
  std::cout<<"\n\tSetup Bgo connector"<<std::endl;
  Int_t FEEID, ChannelID;
  Short_t PlaneID, QuadrantID, BarID, DyID;
  Int_t const ChannelNbOneQuadrant = (kBarNb+kRefBarNb)*kDyNb;
  std::string note;
  for(Short_t p=0;p<kPlaneNb;++p){
    char fileName[20];
    sprintf(fileName,"Plane_%d.cnct",p);
    ifstream mapFile(fConnectorPath+"/Bgo/Chuyang/"+fileName);
    if (!mapFile.good()) {
      std::cout<<"\t\tPlane_"<<p<<"\tfailed..."<<std::endl;
      return false;
    } else {
      std::cout<<"\t\tSetting Plane_"<<p<<std::endl;
    }
    getline(mapFile,note);   mapFile>>PlaneID;
    if (PlaneID != p) {
      std::cout<<"\t\tError: Plane ID in Connector file is wrong..."<<std::endl;
      return false;
    }
    for(Short_t quadrantID=0;quadrantID<kSideNb*2;++quadrantID){        // kSideNb*2:   2 layers in one plane
      getline(mapFile,note);   mapFile>>QuadrantID;
      getline(mapFile,note);   mapFile>>FEEID;
      getline(mapFile,note);
      for(Int_t c=0;c<ChannelNbOneQuadrant;++c){
        mapFile>>BarID;
        mapFile>>DyID;
        mapFile>>ChannelID;
        Short_t array[4] = {PlaneID,QuadrantID,BarID,DyID};
        ConnectorBgo.insert(std::make_pair(FEEID*1000+ChannelID,array));     // FEEID*1000 + ChannelID as key, since ChannelNbOneQuadrant = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
      }
    }
    mapFile.close();
  }
  std::cout<<"\n\t\t\t\tSuccessful"<<std::endl;
  return true;
}

// need real data to implement this part
Bool_t DmpRdcManager::ConversionBgo(ifstream *HexData){
#ifdef Dmp_DEBUG
//  std::cout<<"\t\t\tEvent Conversion:\tBgo"<<std::endl;
#endif
  fEvtBgo->Reset();
  Short_t feeID=0, channelID=0;
  Short_t nChan=0, dataLong=0;
  Short_t rawHex[2]={0};

  for (Short_t pl=0;pl<kPlaneNb*2;++pl) {
    Short_t tmp=0;
    HexData->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      std::cout<<"\t\t\t\t----> 0xeb wrong\t"<<std::hex<<tmp<<std::endl;
      return false;
    }
    HexData->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      std::cout<<"\t\t\t\t----> 0x90 wrong\t"<<std::hex<<tmp<<std::endl;
      return false;
    }
    HexData->read((char*)(&tmp),1);         //trigger
    HexData->read((char*)(&feeID),1);
    if (pl == 0) {                           //trigger check, runMode check
      fTrigger["Bgo"] = tmp;
      fEvtBgo->SetMode(DmpDcdRunMode(feeID/16));
    } else {
      if (tmp != fTrigger["Bgo"]) {
        std::cout<<"\t\t\t\t----> FEE trigger not match"<<std::endl;
        return false;
      }
      if (feeID/16 != fEvtBgo->GetMode()) {
        std::cout<<"\t\t\t\t----> FEE Mode not match"<<std::endl;
        return false;
      }
    }
    feeID = feeID%16;
    HexData->read((char*)(&tmp),1);         // datalong, 2 Bytes
    HexData->read((char*)(&dataLong),1);
    Int_t dataLength = tmp*256 + dataLong;
    if (dataLength == kStdDataLength) {
      nChan = (dataLength-2*3)/2;
    } else {
      nChan = (dataLength-2*3)/3;
    }
//std::cout<<"\t\t\t XX 2  nChan = "<<nChan<<" dL = "<<dataLength<<" kDL = "<<kStdDataLength<<std::endl;

    for (Short_t nc=0;nc<nChan;++nc) {
      if (dataLength == kStdDataLength) {
        channelID = nc;
      } else {
        HexData->read((char*)(&channelID),1);
      }
      HexData->read((char*)(&rawHex[0]),1);
      HexData->read((char*)(&rawHex[1]),1);
      fEvtBgo->SetSignal(1,2,3,4,rawHex[0]*256+rawHex[1]);
/*
      fEvtBgo->SetSignal(
        ConnectorBgo[feeID*1000+channelID][0],     // Plane ID
        ConnectorBgo[feeID*1000+channelID][2],     // Quadrant ID
        ConnectorBgo[feeID*1000+channelID][1],     // Bar ID
        ConnectorBgo[feeID*1000+channelID][3],     // Dy ID
        rawHex[0]*256+rawHex[1]);                  // ADC
*/
    }
    HexData->read((char*)(&tmp),2);             // reserve, 2 Bytes
    HexData->read((char*)(&tmp),2);             // CRC,     2 Bytes
    HexData->read((char*)(&tmp),2);             // 5aa5,    2 Bytes
  }
  return true;
}

