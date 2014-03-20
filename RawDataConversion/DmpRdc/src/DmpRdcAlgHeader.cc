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
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"

DmpRdcAlgHeader::DmpRdcAlgHeader()
 :fHeader(0),
  fFile(0),
  fTrigger(0)
{
  fHeader = DmpRdcDataManager::GetInstance()->GetRawEvent()->GetEventHeader();  
}

DmpRdcAlgHeader::~DmpRdcAlgHeader(){
}

bool DmpRdcAlgHeader::Convert(){
// *
// *  TODO: header convert
// *
  static long id = 0;
  static short tmp=0;
  fFile->read((char*)(&tmp),1);
{
#ifdef DmpDebug
std::cout<<std::dec<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}
  if (tmp!=0xe2)    return false;
  fFile->read((char*)(&tmp),1);
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::dec<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}
  if (tmp!=0x25)    return false;
  fFile->read((char*)(&tmp),1);
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::dec<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}
  if (tmp!=0x08)    return false;
  fFile->read((char*)(&tmp),1);
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::dec<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  }else{
    ++id;    // find a science data header
    fHeader->SetEventID(id);
  }
  fFile->read((char*)(&tmp),1);      //this needed
  fFile->read((char*)(&fTrigger),1);
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::dec<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}
  fFile->read((char*)(&tmp),1);      //Datalength
  fFile->read((char*)(&tmp),1);      //Datalength
{
#ifdef DmpDebug
std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"),\tn "<<std::dec<<fFile->tellg()<<" value = "<<std::hex<<tmp;
#endif
}

  for (short index=0;fHeader->GetTimeSize();++index) {     // size = 8
    fFile->read((char*)(&tmp),1);
    fHeader->SetTime(index,tmp);
  }

#ifdef DmpDebug
std::cerr<<"\tto "<<std::dec<<fFile->tellg()<<std::endl;
#endif
  return true;
}


