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
  fEvtHeader(0),
  fConnectorPath("no"),
  fConnectorDone(false),
  fFEEType(0),
  fFEENo(0),
  fFEEChannelNo(0),
  fMSDSet(0)
{
std::cout<<"DEBUG: name: "<<n<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
  fFile = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->InFileStream();
  fLog = ((DmpRdcSvcLog*)gDmpSvcMgr->Get("Rdc/Log"));
  fEvtHeader = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetEventHeader();
  if(not InitializeSubDet()){
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpRdcVAlgSubDet::Set(const std::string &type,const std::string &argv){
  if(type == "CnctPath"){
    fConnectorPath = argv;
  }else if(type == "FEE/Type"){
    fFEEType = boost::lexical_cast<short>(argv);
  }else if(type == "FEE/Number"){
    fFEENo = boost::lexical_cast<short>(argv);
  }else if(type == "FEE/ChannelNumber"){
    fFEEChannelNo = boost::lexical_cast<short>(argv);
  }
}


