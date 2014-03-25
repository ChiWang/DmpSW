/*
 *  $Id: DmpRdcAlgHeader.cc, 2014-03-19 13:10:00 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "DmpRdcAlgHeader.h"
#include "DmpRdcDataManager.h"
#include "DmpEvtHeader.h"

DmpRdcAlgHeader::DmpRdcAlgHeader(const std::string &name)
 :DmpRdcVAlg(name)
{
}

//-------------------------------------------------------------------
DmpRdcAlgHeader::~DmpRdcAlgHeader(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::ProcessThisEvent(){
  StatusLog(0);
// *
// *  TODO: check conversion Header
// *
//-------------------------------------------------------------------
  static short tmp=0;
  sFile->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  sFile->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  sFile->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  sFile->read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
  sHeader->CountThisEvent();    // find a science data header 0xe225 0813
  sFile->read((char*)(&tmp),1);      // this needed
  sFile->read((char*)(&tmp),1);      // trigger
  sHeader->SetTrigger(DmpDetector::kWhole,tmp);
  sFile->read((char*)(&tmp),1);      // Datalength
  sFile->read((char*)(&tmp),1);      // Datalength
  for (short index=0;index<8;++index) {     // size = 8
    sFile->read((char*)(&tmp),1);
    sHeader->SetTime(index,tmp);
  }
  StatusLog(1);
  return true;
}


