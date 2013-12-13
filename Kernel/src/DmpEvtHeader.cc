/*=====================================================================
 *   File:   DmpEvtHeader.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:08:09
=====================================================================*/

#include <iostream>

#include "TMath.h"
#include "DmpEvtHeader.hh"

using namespace TMath;

ClassImp(DmpEvtHeader)

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
DmpEvtHeader::~DmpEvtHeader()
{}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void DmpEvtHeader::ShowTime(Short_t mode) const{
/*
 *  use cerr instead of cout, since most situation while calling ShowTime() is just after a cerr.
 *  So, if we use cout in this function, then the output file will not match the file of the last cerr information in.
 *
*/ 
  if (mode ==1) {
    std::cerr<<"Normal time:"<<std::endl;
  } else {
    std::cerr<<"Hex time:"<<std::endl;
  }
}


