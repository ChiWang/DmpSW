/*
 *  $Id: DmpRdcAlgBT2012.cc, 2014-05-27 20:59:09 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 27/05/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpIOSvc.h"
#include "DmpRdcAlgBT2012.h"

//-------------------------------------------------------------------
DmpRdcAlgBT2012::DmpRdcAlgBT2012()
 :DmpVAlg("Rdc/BT2012"),fInDataName("NO"),fEvtHeader(0),
  fBgoBarSet(0),fCNCTPathBgo("NO"),fCNCTDoneBgo(false),fFEETypeBgo(0),fFEENoBgo(6),
  fPsdStripSet(0),fCNCTPathPsd("NO"),fCNCTDonePsd(false),fFEETypePsd(1),fFEENoPsd(1),
  fNudBlockSet(0),fCNCTPathNud("NO"),fCNCTDoneNud(false),fFEETypeNud(2),
  fStkLadderSet(0),fCNCTPathStk("NO"),fCNCTDoneStk(false),fFEETypeStk(3),fFEENoStk(8)
{
  OptMap.insert(std::make_pair("BinaryFile",    0));
  OptMap.insert(std::make_pair("Psd/FeeNumber", 1));
  OptMap.insert(std::make_pair("Stk/FeeNumber", 2));
  OptMap.insert(std::make_pair("Bgo/FeeNumber", 3));
  OptMap.insert(std::make_pair("Psd/Connector", 4));
  OptMap.insert(std::make_pair("Stk/Connector", 5));
  OptMap.insert(std::make_pair("Bgo/Connector", 6));
  OptMap.insert(std::make_pair("Nud/Connector", 7));
}

//-------------------------------------------------------------------
DmpRdcAlgBT2012::~DmpRdcAlgBT2012(){
}

//-------------------------------------------------------------------
#include "boost/lexical_cast.hpp"
void DmpRdcAlgBT2012::Set(const std::string &type, const std::string &argv){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<"No argument type: "<<type<<DmpLogEndl;
  }
  switch (OptMap[type]){
    case 0:
    {// BinaryFile
      fInDataName = argv;
      DmpIOSvc::GetInstance()->InFileTag(argv);
      break;
    }
    case 1:
    {// Psd/FeeNumber
      fFEENoPsd = boost::lexical_cast<short>(argv);
      break;
    }
    case 2:
    {// Stk/FeeNumber
      fFEENoStk = boost::lexical_cast<short>(argv);
      break;
    }
    case 3:
    {// Bgo/FeeNumber
      fFEENoBgo = boost::lexical_cast<short>(argv);
      break;
    }
    case 4:
    {// Psd/Connector
      fCNCTPathPsd = argv;
      break;
    }
    case 5:
    {// Stk/Connector
      fCNCTPathStk = argv;
      break;
    }
    case 6:
    {// Bgo/Connector
      fCNCTPathBgo = argv;
      break;
    }
    case 7:
    {// Nud/Connector
      fCNCTPathNud = argv;
      break;
    }
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::Initialise(){
  fFile.open(fInDataName.c_str(),std::ios::in|std::ios::binary);
  if(not fFile.good()){
    DmpLogError<<"Open "<<fInDataName<<" failed"<<DmpLogEndl;
    fFile.close();
    fInDataName = "WRONG";
    return false;
  }
  fEvtHeader = new DmpEvtRdcHeader();
  DmpIOSvc::GetInstance()->AddBranch("Rdc/EventHeader/DmpEvtRdcHeader",fEvtHeader);
  if(not InitialisePsd())   return false;
  if(not InitialiseStk())   return false;
  if(not InitialiseBgo())   return false;
  if(not InitialiseNud())   return false;
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEvent(){
  DmpLogDebug<<DmpLogEndl;
  bool oneEvtDone = false;
  while(not oneEvtDone){
    DmpLogDebug<<"from "<<fFile.tellg();
    if(ProcessThisEventHeader()){
      DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
    }else{
      DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
      continue;
    }
    if(fCNCTDoneNud){
      DmpLogDebug<<"[Nud] from "<<fFile.tellg();
      if(ProcessThisEventNud()){
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
      }else{
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
        continue;
      }
    }
    if(fCNCTDonePsd){
      DmpLogDebug<<"[Psd] from "<<fFile.tellg();
      if(ProcessThisEventPsd()){
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
      }else{
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
        continue;
      }
    }
    if(fCNCTDoneBgo){
      DmpLogDebug<<"[Bgo] from "<<fFile.tellg();
      if(ProcessThisEventBgo()){
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
      }else{
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
        continue;
      }
    }
    if(fCNCTDoneStk){
      DmpLogDebug<<"[Stk] from "<<fFile.tellg();
      if(ProcessThisEventStk()){
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
      }else{
        DmpLogDebug<<"to "<<fFile.tellg()<<DmpLogEndl;
        continue;
      }
    }
    if(fFile.tellg() < 0){
      DmpLogDebug<<"not fill the last event"<<DmpLogEndl;
      return false;
    }
    oneEvtDone = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::Finalize(){
  if("WRONG" != fInDataName && "NO" != fInDataName){
    delete fEvtHeader;
  }
  FinalizePsd();
  FinalizeStk();
  FinalizeBgo();
  FinalizeNud();
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventHeader(){
  fEvtHeader->Reset();
//-------------------------------------------------------------------
  static short tmp=0;
  fFile.read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fFile.read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fFile.read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fFile.read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
  fFile.read((char*)(&tmp),1);      // this needed
  fFile.read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(DmpDetector::kWhole,tmp);
  fFile.read((char*)(&tmp),1);      // Datalength
  fFile.read((char*)(&tmp),1);      // Datalength
  for(std::size_t index=0;index<8;++index){     // size = 8
    fFile.read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  return true;
}


