/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-05-16 01:58:15 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcVAlgSubDet.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpRdcVAlgSubDet::DmpRdcVAlgSubDet(const std::string &n)
 :DmpVAlg(n),
  fFile(0),
  fEvtHeader(0),
  fConnectorPath("no"),
  fConnectorDone(false),
  fMSDSet(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
  fFile = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->InFileStream();
  fEvtHeader = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->GetEventHeader();
  if(not InitializeSubDet()){
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
//#include <boost/lexical_cast.hpp>
void DmpRdcVAlgSubDet::Set(const std::string &type,const std::string &argv){
  if(type == "CnctPath"){
    fConnectorPath = argv;
  }
}


