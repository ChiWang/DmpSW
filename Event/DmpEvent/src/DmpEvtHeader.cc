/*=============================================================================
#       FileName :          DmpEvtHeader.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   10:01:28
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-25   19:00:08
=============================================================================*/

#include <iostream>

#include "TMath.h"
#include "DmpEvtHeader.hh"

using namespace TMath;

ClassImp(DmpEvtHeader)

//______________________________________________________________________________
DmpEvtHeader::DmpEvtHeader()
 :fPackageID(-1),
  fEventID(-1),
  fSec(0),
  fmSec(0),
  fTimeGap(0),
  fPID(kUnknown),
  fCharge(-100),
  fEnergy(-100)
{
}

//______________________________________________________________________________
DmpEvtHeader::~DmpEvtHeader()
{}

//______________________________________________________________________________
void DmpEvtHeader::Reset(){
  fPackageID = -1;
  fEventID = -1;
  fSec = 0;
  fmSec = 0;
  fTimeGap = 0;
  fPID = kUnknown;
  fCharge = -100;
  fEnergy = -100;
}

//______________________________________________________________________________
Bool_t DmpEvtHeader::IsValidEvent(){
  ++fEventID;
  return true;
}

//______________________________________________________________________________
void DmpEvtHeader::SetTime(Short_t Time[],Int_t size){
#ifdef Dmp_DEGUB
  std::cout<<"\t\t\t Setting time"<<std::endl;
#endif
  Long64_t SecTmp = Time[2]*Power(16,6)+Time[3]*Power(16,4)+Time[4]*Power(16,2)+Time[5]*Power(16,0);
  Short_t  mSecTmp = Time[6]*256+Time[7];
  fTimeGap = (fSec==0 && fmSec==0)?111:((SecTmp-fSec)*1000+(mSecTmp-fmSec));
  fSec = SecTmp;
  fmSec = mSecTmp;
}

//______________________________________________________________________________
void DmpEvtHeader::ShowTime() const{
  std::cout<<"Normal time:"<<std::endl;
  std::cout<<"Hex time:"<<std::endl;
}


