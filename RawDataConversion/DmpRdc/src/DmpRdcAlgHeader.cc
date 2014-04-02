/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-04-02 13:11:10 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#include "DmpRdcAlgHeader.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"

//-------------------------------------------------------------------
DmpRdcAlgHeader::DmpRdcAlgHeader(const std::string &n)
 :DmpVAlgorithm(n)
{
  fEvtHeader = gDataMgr->GetRawEvent()->GetEventHeader();
}

//-------------------------------------------------------------------
#include "DmpRdcLog.h"
bool DmpRdcAlgHeader::ProcessThisEvent(){
  gRdcLog->StatusLog(0);
//-------------------------------------------------------------------
  static short tmp=0;
  static std::ifstream *inFile = gDataMgr->gInFile;
  inFile->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  inFile->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  inFile->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  inFile->read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
  fEvtHeader->CountThisEvent();    // find a science data header 0xe225 0813
  inFile->read((char*)(&tmp),1);      // this needed
  inFile->read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(DmpDetector::kWhole,tmp);
  inFile->read((char*)(&tmp),1);      // Datalength
  inFile->read((char*)(&tmp),1);      // Datalength
  for (short index=0;index<8;++index) {     // size = 8
    inFile->read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
  gDataMgr->GetRawEvent()->Reset(); // perpare for the sub-Det Convert()
//-------------------------------------------------------------------
  gRdcLog->StatusLog(1);
  return true;
}


