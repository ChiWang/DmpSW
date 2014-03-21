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

DmpRdcAlgHeader::DmpRdcAlgHeader()
 :fTrigger(0)
{
}

//-------------------------------------------------------------------
DmpRdcAlgHeader::~DmpRdcAlgHeader(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgHeader::Convert(){
  StatusLog(0);
// *
// *  TODO: check conversion Header
// *
//-------------------------------------------------------------------
  static long id = -1;
  static short tmp=0;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fFile->read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;

  ++id;     // find a science data header 0xe225 0813
  fHeader->SetEventID(id);
  fFile->read((char*)(&tmp),1);      //this needed
  fFile->read((char*)(&fTrigger),1);
  fFile->read((char*)(&tmp),1);      //Datalength
  fFile->read((char*)(&tmp),1);      //Datalength
  for (short index=0;index<fHeader->GetTimeSize();++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fHeader->SetTime(index,tmp);
  }
  StatusLog(1);
  return true;
}


