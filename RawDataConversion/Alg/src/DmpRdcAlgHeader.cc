/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-04-17 10:41:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#include "DmpServiceManager.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpEvtRdcHeader.h"
#include "DmpRdcAlgHeader.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader::DmpRdcAlgHeader()
 :DmpVAlg("Header/2014"),
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
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::ProcessThisEvent(){
  fLog->Type(0);
//std::cout<<"\tfrom "<<fFile->tellg();
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
  fFile->read((char*)(&tmp),1);      // this needed
  fFile->read((char*)(&tmp),1);      // trigger
// *
// *  TODO: trigger max != 4096??
// *
  fEvtHeader->SetTrigger(tmp);
  fFile->read((char*)(&tmp),1);      // Datalength
  fFile->read((char*)(&tmp),1);      // Datalength
  for (short index=0;index<8;++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  fLog->Type(1);
//std::cout<<" to "<<fFile->tellg()<<std::endl;
  return true;
}


