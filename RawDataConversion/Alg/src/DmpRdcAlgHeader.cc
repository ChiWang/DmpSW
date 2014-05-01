/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-04-17 10:41:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#include "DmpRdcAlgHeader.h"
#include "DmpEvtRdcHeader.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpKernel.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader::DmpRdcAlgHeader()
 :DmpVAlg("Header/2014"),
  fFile(0),
  fEvtHeader(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::Initialize(){
// *
// *  TODO:     1.  check Get a 0?
//              2.  fFile will update if set a new data??
// *
  fFile = ((DmpRdcSvcDataMgr*)gKernel->ServiceManager()->Get("Rdc/DataMgr"))->InFileStream();
  fEvtHeader = ((DmpRdcSvcDataMgr*)gKernel->ServiceManager()->Get("Rdc/DataMgr"))->GetEventHeader();
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::ProcessThisEvent(){
  static bool firstIn = true;
  if(gKernel->PrintDebug() && firstIn){
    std::cout<<"\nDEBUG: "<<__PRETTY_FUNCTION__<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
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
// *
// *  TODO: trigger first byte means??
// *
  fFile->read((char*)(&tmp),1);      // this needed
  fFile->read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(tmp);
  fFile->read((char*)(&tmp),1);      // Datalength
  fFile->read((char*)(&tmp),1);      // Datalength
  for (std::size_t index=0;index<8;++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  if(gKernel->PrintDebug()){
    std::cout<<" to "<<fFile->tellg()<<std::endl;
    firstIn = true;
  }
  return true;
}


