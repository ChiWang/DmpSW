
#include <iostream>

#include "DmpEvtStk.hh"
#include "DmpRdcStk.hh"
#include "DmpDcdParameterStk.hh"

using namespace std;
using namespace DmpDcdParameter::Stk;

DmpRdcStk::DmpRdcStk()
 :fEvt(0)
{
  fEvt = new DmpEvtStkRaw();
}

DmpRdcStk::~DmpRdcStk(){
  delete fEvt;
}

Bool_t DmpRdcStk::SetConnector(){
  cout<<"\n\tSetup Stk connector"<<endl;
/*
  Int_t FEEID, ChannelID;
  Short_t LayerID, BarID, SideID, DyID;
  Int_t ChannelNbOneLayerOneSide = (kBarNb+kRefBarNb)*kDyNb;
//, LineNb = ChannelNbOneLayerOneSide+ 5;      //line number of one layer's map (check fMapPath+fileName). 5:    LayerID->2 lines(note 1 lilne, value 1 line); FEEID->2 lines; table note 1 line;
  string tmp;
  for(Int_t p=0;p<kPlaneNb;++p){
    char fileName[20];
    sprintf(fileName,"Plane_%d.infor",p);
    ifstream mapFile(fMapPath+fileName);
    if (!mapFile.good()) {cout<<"\tfailed"<<endl; return false;}
    for(Int_t layerID=0;layerID<2;++layerID){
      for(Int_t sideID=0;sideID<2;++sideID){
        getline(mapFile,tmp);   mapFile>>LayerID;
        getline(mapFile,tmp);   mapFile>>SideID;
        getline(mapFile,tmp);   mapFile>>FEEID;
        getline(mapFile,tmp);
        for(Int_t c=0;c<ChannelNbOneLayerOneSide;++c){
          mapFile>>BarID; mapFile>>DyID; mapFile>>ChannelID;
          Short_t array[4] = {LayerID,BarID,SideID,DyID};
          Connector.insert(make_pair(FEEID*1000+ChannelID,array));       //FEEID*1000 + ChannelID as key, since ChannelNbOneLayerOneSide = (22+2)*3*2 = (kBarNb+kRefBarNb)*kDynb*kSideNb = 144 > 100
        }
      }
    }
    mapFile.close();
  }
*/
  cout<<"\n\t\t\t\tSuccessful"<<endl;
  return true;
}

//  need real data to implement this part
Bool_t DmpRdcStk::Conversion(ifstream *HexData){
  cout<<"\t\t\tEvent Conversion:\tStk"<<endl;
  Short_t tmp=0;
/*
  for (Int_t i=0;i<fNByte;++i)
  HexData->read((char*)(&tmp),1);
  HexData->read((char*)(&tmp),1);
  if (tmp!=0xeb)    return false;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x90) {
   cout<<"\n----> Stk 0xeb90 wrong"<<endl;
   return false;
  }
*/
  return true;
}

