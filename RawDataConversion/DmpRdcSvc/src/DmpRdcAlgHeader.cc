/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-04-08 15:27:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#include "DmpServiceManager.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpEvtHeader.h"
#include "DmpRdcAlgHeader.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader::DmpRdcAlgHeader(const std::string &n)
 :DmpVAlg(n),
  fFile(0),
  fLog(0),
  fEvtHeader(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
// *
  fFile = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->InFileStream();
  fLog = ((DmpRdcSvcLog*)gDmpSvcMgr->Get("Rdc/Log"));
  fEvtHeader = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetEventHeader();
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::ProcessThisEvent(){
  fLog->Type(0);
//-------------------------------------------------------------------
  static short tmp=0;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
  fEvtHeader->CountThisEvent();    // find a science data header 0xe225 0813
  fFile->read((char*)(&tmp),1);      // this needed
  fFile->read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(DmpDetector::kWhole,tmp);
  fFile->read((char*)(&tmp),1);      // Datalength
  fFile->read((char*)(&tmp),1);      // Datalength
  for (short index=0;index<8;++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  fLog->Type(1);
  return true;
}


