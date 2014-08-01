/*
 *  $Id: DmpRdcAlgEQM.cc, 2014-08-01 11:44:22 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/08/2014
*/

#include "DmpEvtHeader.h"

//-------------------------------------------------------------------
DmpRdcAlgEQM::DmpRdcAlgEQM()
 :DmpVAlg("Rdc/EQM"),fInDataName("NO"),fEvtHeader(0),
  fBgoBarSet(0),fCNCTPathBgo("NO"),fCNCTDoneBgo(false),
  fPsdStripSet(0),fCNCTPathPsd("NO"),fCNCTDonePSd(false),
  fStkLadderSet(0),fCNCTPathStk("NO"),fCNCTDoneStk(false),
  fNudBlockSet(0),fCNCTPathNud("NO"),fCNCTDoneNud(false)
{
  OptMap.insert(std::make_pair("BinaryFile",    0));
  OptMap.insert(std::make_pair("Psd/Connector", 1));
  OptMap.insert(std::make_pair("Stk/Connector", 2));
  OptMap.insert(std::make_pair("Bgo/Connector", 3));
  OptMap.insert(std::make_pair("Nud/Connector", 4));
}

//-------------------------------------------------------------------
~DmpRdcAlgEQM::DmpRdcAlgEQM(){
}

//-------------------------------------------------------------------
void DmpRdcAlgEQM::Set(const std::string &type, const std::string &argv){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<"No argument type: "<<type<<DmpLogEndl;
  }
  switch (OptMap[type]){
    case 0:
    {// BinaryFile
      fInDataName = argv;
      break;
    }
    case 1:
    {// Psd/Connector
      fCNCTPathPsd = argv;
      break;
    }
    case 2:
    {// Stk/Connector
      fCNCTPathStk = argv;
      break;
    }
    case 3:
    {// Bgo/Connector
      fCNCTPathBgo = argv;
      break;
    }
    case 4:
    {// Nud/Connector
      fCNCTPathNud = argv;
      break;
    }
  }
}

//-------------------------------------------------------------------
bool DmpRdcAlgEQM::Initialize(){
  bool psd = InitializePsd();   // set connector, fMapPsd, and fCNCTDonePsd
  bool stk = InitializeStk();
  bool bgo = InitializeBgo();
  bool nud = InitializeNud();
  return (psd && stk && bgo && nud);
}

//-------------------------------------------------------------------
bool ProcessThisEvent(){
// *
// *  TODO:  check DmpCore::Run() event id and IO svc of event id....
// *
  fActiveSubDet = false;
  ReadDataIntoDataBuffer();     // invoke this function many times, then fStkBuffer.size will == 1, and size of DataBuffer of others > 1
  if(fStkBuffer.size == 1){
    short id = fStkBuffer.begin()->first;
    fActiveSubDet = true;
    ProcessThisEventHeader(id);   // read data(this id) from it data buffer, and ***then delete*** this data in that buffer
    ProcessThisEventPsd(id);
    ProcessThisEventStk(id);
    ProcessThisEventBgo(id);
    ProcessThisEventNud(id);
    // then fStkBuffer.size = 0
  }
  return fActiveSubDet;     // if not ture, will not fill this event
}

//-------------------------------------------------------------------
bool DmpRdcAlgEQM::Finalize(){
  fPsdStripSet->Delete();
  fStkLadderSet->Delete();
  fBgoBarSet->Delete();
  fNudBlockSet->Delete();
  return true;
}


