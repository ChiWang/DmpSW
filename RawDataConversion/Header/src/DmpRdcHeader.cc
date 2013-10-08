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

#include "TROOT.h"

#include "DmpDcdParameterDmg.hh"
#include "DmpEvtHeader.hh"
#include "DmpRdcHeader.hh"

using namespace std;
using namespace DmpDcdParameter::Dmg::Sci;

DmpRdcHeader::DmpRdcHeader()
 :fEvt(0)
{
  fEvt = new DmpEvtHeaderRaw();
  fTree = fEvt->GetTree("Header");
}

DmpRdcHeader::~DmpRdcHeader(){
  delete fEvt;
}

// need real data to implement this part
Bool_t DmpRdcHeader::Conversion(ifstream* HexData){
#ifdef DEBUG
  cout<<"\t\t\tEvent Conversion:\tHeader"<<endl;
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
    cout<<"\t\t\t\t----> Searching 0xe225 0813"<<endl;
    return false;
  } else {
    fEvt->IsValidPackage();
  }
  HexData->read((char*)(&fTrigger),1);      //this needed
  HexData->read((char*)(&fTrigger),1);
  HexData->read((char*)(&tmp),1);           //Datalongth
  HexData->read((char*)(&tmp),1);           //Datalongth

  Short_t time[kTimerLength];
  for (Int_t i=0;i<kTimerLength;++i) {
    time[i]=0;
    HexData->read((char*)(&time[i]),1);
  }

  fEvt->SetTime(time);
#ifdef DEBUG
cout<<"\t\ttrigger = "<<fTrigger<<"\tPcg = "<<fEvt->GetPackageID()<<endl;
#endif

  return true;
}

