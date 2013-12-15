/*=====================================================================
 *   File:   DmpEvtHeader.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  15/12/2013   21:52:35
=====================================================================*/

#include <iostream>

#include "TMath.h"
#include "DmpEvtHeader.hh"

using namespace TMath;

ClassImp(DmpEvtHeader)

//------------------------------------------------------------------------------
DmpEvtHeader::DmpEvtHeader()
 :fPackageID(-1),
  fEvtID(-1),
  fSec(0),
  fmSec(0),
  fTimeGap(0),
  fPID(kUnknown),
  fCharge(-100),
  fEnergy(-100)
{}

//------------------------------------------------------------------------------
DmpEvtHeader::~DmpEvtHeader()
{}

//------------------------------------------------------------------------------
void DmpEvtHeader::Reset(){
  fPackageID = -1;
  fEvtID = -1;
  fSec = 0;
  fmSec = 0;
  fTimeGap = 0;
  fPID = kUnknown;
  fCharge = -100;
  fEnergy = -100;
}

//------------------------------------------------------------------------------
void DmpEvtHeader::SetTime(Short_t Time[],Int_t size){
  static Long64_t SecTmp;
  static Short_t mSecTmp;
  SecTmp = Time[2]*Power(16,6)+Time[3]*Power(16,4)+Time[4]*Power(16,2)+Time[5]*Power(16,0);
  mSecTmp = Time[6]*256+Time[7];
  fTimeGap = (fPackageID==0 && fEvtID==-1)?100:((SecTmp-fSec)*1000+(mSecTmp-fmSec));
  fSec = SecTmp;
  fmSec = mSecTmp;
  fTime = Time;
}

//------------------------------------------------------------------------------
void DmpEvtHeader::ShowTime(Short_t mode) const{
/*
 *  use cerr instead of cout, since most situation while calling ShowTime() is just after a cerr.
 *  So, if we use cout in this function, then the output file will not match the file of the last cerr information in.
 *
*/ 
  Long64_t tmp=fSec;
  if (mode ==1) {
    std::cerr<<"Normal time:"<<std::endl;
  } else {
    std::cerr<<"Hex time:\t";
    std::cerr<<std::hex<<fTime[2]<<" "<<fTime[3]<<" "<<fTime[4]<<" "<<fTime[5]<<" "<<fTime[6]<<" "<<fTime[7]<<std::endl;
/*
    std::cerr<<std::hex<<tmp/Power(16,6)<<"  "; tmp = tmp%(16*16*16*16*16*16);
    std::cerr<<std::hex<<tmp/Power(16,4)<<"  "; tmp = tmp%(16*16*16*16);
    std::cerr<<std::hex<<tmp/Power(16,2)<<"  "; tmp = tmp%(16*16);
    std::cerr<<std::hex<<tmp<<"  "; tmp = fmSec;
    std::cerr<<std::hex<<tmp/256<<"  "<<tmp%256<<std::endl;
*/
  }
}


