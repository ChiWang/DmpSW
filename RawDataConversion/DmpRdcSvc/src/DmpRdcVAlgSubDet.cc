/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-04-06 20:13:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "DmpServiceManager.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpRdcVAlgSubDet.h"

//-------------------------------------------------------------------
DmpRdcVAlgSubDet::DmpRdcVAlgSubDet(const std::string &n)
 :DmpVAlg(n),
  fFile(0),
  fLog(0),
  fConnectorPath("no"),
  fEvtHeader(0),
  fMSDSet(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
  fFile = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->InFileStream();
  fLog = ((DmpRdcSvcLog*)gDmpSvcMgr->Get("Rdc/Log"));
  fEvtHeader = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetEventHeader();
  if(not SetupConnector()){
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::ProcessThisEvent(){
  if(fConnectorPath == "no") return true;
  fLog->Type(0);
//-------------------------------------------------------------------
// set ProcessThisEvention method here
//-------------------------------------------------------------------
  fLog->Type(1);
  return true;
}

//-------------------------------------------------------------------
void DmpRdcVAlgSubDet::Set(const std::string &type,const std::string &argv){
  if(type == "CnctPath"){
    fConnectorPath = argv;
  }
}


