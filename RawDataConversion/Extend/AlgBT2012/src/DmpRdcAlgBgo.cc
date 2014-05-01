/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-05-01 17:40:40 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
 *    Yifeng WEI (weiyf@mail.ustc.edu.cn) 24/04/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "Rdc/DmpRdcSvcDataMgr.h"
#include "DmpKernel.h"
#include "DmpRdcAlgBgo.h"

DmpRdcAlgBgo::DmpRdcAlgBgo()
 :DmpRdcVAlgSubDet("Bgo/Rdc/BT2012"),
  fFEEType(0),
  fFEENo(6)
{
}

//-------------------------------------------------------------------
DmpRdcAlgBgo::~DmpRdcAlgBgo(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgBgo::ProcessThisEvent(){
  static bool firstIn = true;
  if(gKernel->PrintDebug() && firstIn){
    std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
  if(not fConnectorDone){
    if(gKernel->PrintError()){
      std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    }
    return true;
  }
// *
// *  TODO: SetErrorLog wrong
// *
//-------------------------------------------------------------------
  static short tmp=0, tmp2=0, nBytes=0;
  for (short counts=0;counts<fFEENo;++counts) {
    fFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      return false;
    }
    fFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      return false;
    }
    fFile->read((char*)(&tmp),1);       // trigger
    if(counts == 0){
      fEvtHeader->SetTrigger(DmpDetector::kBgo,tmp);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetector::kBgo) != tmp){
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // run mode and FEE ID
    static short feeID = 0;
    feeID = tmp%16;
    if(counts == 0){
      fEvtHeader->SetRunMode(DmpDetector::kBgo,tmp/16-fFEEType);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetector::kBgo) != tmp/16-fFEEType){
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // data length, 2 bytes
    fFile->read((char*)(&tmp2),1);
    nBytes = tmp*256+tmp2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->GetRunMode(DmpDetector::kBgo) == DmpDetector::k0Compress){
      for(short i=0;i<nBytes;i+=2){     // k0Compress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
        AppendThisSignal(fConnector[feeID*1000+i/2],tmp*256+tmp2);
      }
    }else{
      for(short i=0;i<nBytes;i+=3){     // kCompress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
// *
// *  TODO: open me
// *
        //AppendThisSignal(fConnector[feeID*1000+xx],tmp*256+tmp2);
      }
    }
    fFile->read((char*)(&tmp),1);       // 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // must split them, 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // 2 bytes for CRC
    fFile->read((char*)(&tmp),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
bool DmpRdcAlgBgo::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gKernel->ServiceManager()->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kBgo);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tBgo"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tBgo"<<std::endl;
  }
  short feeID=0, channelNo=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fConnectorPath);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      std::cout<<"\t\treading cnct file ("<<iter->path().string()<<") failed"<<std::endl;
      cnctFile.close();
      return false;
    }else{
      std::cout<<"\t\treading cnct file: "<<iter->path().string();
    }
    cnctFile>>feeID;
    cnctFile>>channelNo;
    for(short s=0;s<channelNo;++s){
      cnctFile>>channelID;
      cnctFile>>layerID;
      cnctFile>>barID;
      cnctFile>>sideID;
      cnctFile>>dyID;
      fConnector.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
    std::cout<<" Done. ID = "<<feeID<<"\tN_channel = "<<channelNo<<std::endl;
  }
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBgo::AppendThisSignal(const int &id, const float &v){
  static DmpEvtRdcMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtRdcMSD*)fMSDSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fMSDSet->GetEntriesFast();
    aMSD = (DmpEvtRdcMSD*)fMSDSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtRdcMSD*)fMSDSet->At(index);
  }
  aMSD->SetSignal(v,id%100);
}


