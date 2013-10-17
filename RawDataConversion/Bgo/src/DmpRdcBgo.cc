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
#                                          Update:  2013-08-16   16:05:59
=============================================================================*/

#include <iostream>

#include "DmpDcdParameterBgo.hh"
#include "DmpEvtBgo.hh"     // include DmpDcdRunMode.hh
#include "DmpRdcBgo.hh"

using namespace std;
using namespace DmpDcdParameter::Bgo;

DmpRdcBgo::DmpRdcBgo()
 :fEvt(0)
{
  fEvt = new DmpEvtBgoRaw();
}

DmpRdcBgo::~DmpRdcBgo(){
  delete fEvt;
}

Bool_t DmpRdcBgo::SetConnector(){
  cout<<"\n\tSetup Bgo connector"<<endl;
  Int_t FEEID, ChannelID;
  Short_t LayerID, BarID, SideID, DyID;
  Int_t const ChannelNbOneLayerOneSide = (kBarNb+kRefBarNb)*kDyNb;
  string note;
  for(Int_t p=0;p<kPlaneNb;++p){
    char fileName[20];
    sprintf(fileName,"Plane_%d.cnct",p);
    ifstream mapFile(fConnectorPath+"Bgo/"+fileName);
    if (!mapFile.good()) {
      cout<<"\t\tPlane_"<<p<<"\tfailed..."<<endl;
      return false;
    } else {
      cout<<"\t\tSetting Plane_"<<p<<endl;
    }
    for(Int_t layerID=0;layerID<2;++layerID){
      for(Int_t sideID=0;sideID<2;++sideID){
        getline(mapFile,note);   mapFile>>LayerID;
        getline(mapFile,note);   mapFile>>SideID;
        getline(mapFile,note);   mapFile>>FEEID;
        getline(mapFile,note);
        for(Int_t c=0;c<ChannelNbOneLayerOneSide;++c){
          mapFile>>BarID;
          mapFile>>DyID;
          mapFile>>ChannelID;
          Short_t array[4] = {LayerID,BarID,SideID,DyID};
          Connector.insert(make_pair(FEEID*1000+ChannelID,array));       //FEEID*1000 + ChannelID as key, since ChannelNbOneLayerOneSide = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
        }
      }
    }
    mapFile.close();
  }
  cout<<"\n\t\t\t\tSuccessful"<<endl;
  return true;
}

// need real data to implement this part
Bool_t DmpRdcBgo::Conversion(ifstream *HexData){
#ifdef DEBUG
//  cout<<"\t\t\tEvent Conversion:\tBgo"<<endl;
#endif
  fEvt->Reset();
  Short_t feeID=0, channelID=0;
  Short_t nChan=0, dataLong=0;
  Short_t rawHex[2]={0};

  for (Short_t pl=0;pl<kPlaneNb*2;++pl) {
    Short_t tmp=0;
    HexData->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      cout<<"\t\t\t\t----> 0xeb wrong\t"<<hex<<tmp<<endl;
      return false;
    }
    HexData->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      cout<<"\t\t\t\t----> 0x90 wrong\t"<<hex<<tmp<<endl;
      return false;
    }
    HexData->read((char*)(&tmp),1);         //trigger
    HexData->read((char*)(&feeID),1);
    if (pl == 0) {                           //trigger check, runMode check
      fTrigger = tmp;
      fEvt->SetMode(DmpDcdRunMode(feeID/16));
    } else {
      if (tmp != fTrigger) {
        cout<<"\t\t\t\t----> FEE trigger not match"<<endl;
        return false;
      }
      if (feeID/16 != fEvt->GetMode()) {
        cout<<"\t\t\t\t----> FEE Mode not match"<<endl;
        return false;
      }
    }
    feeID = feeID%16;
    HexData->read((char*)(&tmp),1);         // datalong, 2 Bytes
    HexData->read((char*)(&dataLong),1);
    fDataLength = tmp*256 + dataLong;
    if (fDataLength == kStdDataLength) {
      nChan = (fDataLength-2*3)/2;
    } else {
      nChan = (fDataLength-2*3)/3;
    }
//cout<<"\t\t\t XX 2  nChan = "<<nChan<<" dL = "<<fDataLength<<" kDL = "<<kStdDataLength<<endl;

    for (Short_t nc=0;nc<nChan;++nc) {
      if (fDataLength == kStdDataLength) {
        channelID = nc;
      } else {
        HexData->read((char*)(&channelID),1);
      }
      HexData->read((char*)(&rawHex[0]),1);
      HexData->read((char*)(&rawHex[1]),1);
      fEvt->SetSignal(1,2,3,4,rawHex[0]*256+rawHex[1]);
/*
      fEvt->SetSignal(
        Connector[feeID*1000+channelID][0],     // Layer ID
        Connector[feeID*1000+channelID][1],     // Bar ID
        Connector[feeID*1000+channelID][2],     // Side ID
        Connector[feeID*1000+channelID][3],     // Dy ID
        rawHex[0]*256+rawHex[1]);               // ADC
*/
    }
    HexData->read((char*)(&tmp),2);             // reserve, 2 Bytes
    HexData->read((char*)(&tmp),2);             // CRC,     2 Bytes
  }
  return true;
}

