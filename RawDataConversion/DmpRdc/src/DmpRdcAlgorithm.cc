/*
 *  $Id: DmpRdcAlgorithm.cc, 2014-03-11 17:12:10 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpEvtHeader.h"
#include "DmpRdcAlgorithm.h"
//#include "DmpRdcDataManager.h"        // may need?

using namespace DmpRdcAlg;

//-------------------------------------------------------------------
bool DmpRdcAlgorithm::ConvertEventHeader(){
// *
// *  TODO: 
// *
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::dec<<fInputData->tellg();
#endif
  static short tmp=0;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  } else {
    fHeader->CountPackage();
  }
  fInputData->read((char*)(&tmp),1);      //this needed
  fInputData->read((char*)(&gTrigger["Header"]),1);
  fInputData->read((char*)(&tmp),1);      //Datalength
  fInputData->read((char*)(&tmp),1);      //Datalength

  static short time[8], i;            // 8 bytes for time
  for (i=0;i<8;++i) {
    time[i]=0;
    fInputData->read((char*)(&time[i]),1);
  }

  fHeader->SetTime(time,8);
#ifdef DmpDebug
std::cerr<<"\tto "<<std::dec<<fInputData->tellg()<<std::endl;
//std::cout<<"\t\ttrigger = "<<gTrigger["Header"]<<"\tPackage ID = "<<fHeader->GetPackageID()<<std::endl;
#endif

  return true;
}


