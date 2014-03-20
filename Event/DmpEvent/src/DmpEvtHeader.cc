/*
 *  $Id: DmpEvtHeader.cc, 2014-02-24 23:22:46 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/ 

#include <iostream>

#include "TParticle.h"
#include "DmpEvtHeader.h"

ClassImp(DmpEvtHeader)

//-------------------------------------------------------------------
DmpEvtHeader::DmpEvtHeader()
 :fEventID(-1),
  fParticle(0)
{
  fParticle = new TParticle();
}

DmpEvtHeader::~DmpEvtHeader(){
  delete fParticle;
}

void DmpEvtHeader::SetParticlePdgCode(int pdgCode){
  fParticle->SetPdgCode(pdgCode);
}

//-------------------------------------------------------------------
/*
void DmpEvtHeader::SetTime(short Time[],int size){
  static Long64_t SecTmp;
  static Short_t mSecTmp;
  SecTmp = Time[2]*Power(16,6)+Time[3]*Power(16,4)+Time[4]*Power(16,2)+Time[5]*Power(16,0);
  mSecTmp = Time[6]*256+Time[7];
  fTimeGap = (fPackageID==0 && fEventID==-1)?100:((SecTmp-fSec)*1000+(mSecTmp-fmSec));
  fSec = SecTmp;
  fmSec = mSecTmp;
  fTime = Time;
}
*/

void DmpEvtHeader::PrintTime() const{
 //*  use cerr instead of cout, since most situation while calling ShowTime() is just after a cerr.
 //*  So, if we use cout in this function, then the output file will not match the file of the last cerr information in.
 std::cout<<"Time:\t";
 for(short i=0;i<GetTimeSize();++i){
   std::cout<<" "<<std::hex<<fTime[i];
 }
 std::cout<<std::dec<<std::endl;
}

