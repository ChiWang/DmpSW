/*=============================================================================
#       FileName :          DmpRdcHeader.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-04   13:15:21
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-06   15:45:16
=============================================================================*/

#include <iostream>

#include "DmpRdcManager.hh"

#include "DmpDcdParameterDmg.hh"
#include "DmpEvtHeader.hh"

using namespace DmpDcdParameter::Dmg::Sci;

// need real data to implement this part
Bool_t DmpRdcManager::ConversionHeader(ifstream* HexData){
#ifdef Dmp_DEBUG
  std::cout<<"\t\t\tEvent Conversion:\tHeader"<<std::endl;
#endif
  Short_t tmp=0;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  HexData->read((char*)(&tmp),1);
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  } else {
    fEvtHeader->IsValidPackage();
  }
  HexData->read((char*)(&tmp),1);           //this needed
  HexData->read((char*)(&fTrigger["Header"]),1);
  HexData->read((char*)(&tmp),1);           //Datalongth
  HexData->read((char*)(&tmp),1);           //Datalongth

  Short_t time[kTimerLength];
  for (Int_t i=0;i<kTimerLength;++i) {
    time[i]=0;
    HexData->read((char*)(&time[i]),1);
  }

  fEvtHeader->SetTime(time);
#ifdef Dmp_DEBUG
std::cout<<"\t\ttrigger = "<<fTrigger["Header"]<<"\tPcg = "<<fEvtHeader->GetPackageID()<<std::endl;
#endif

  return true;
}

