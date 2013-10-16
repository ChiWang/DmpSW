
#include <iostream>

#include "TTree.h"
#include "TMath.h"

#include "DmpEvtVBasicHeader.hh"

using namespace std;
using namespace TMath;

DmpEvtVBasicHeader::DmpEvtVBasicHeader()
 :fEvtID(-1),
  fSec(0),
  fmSec(0),
  fTimeGap(0),
  fPID(kUnknown)
{}

DmpEvtVBasicHeader::~DmpEvtVBasicHeader()
{}

void DmpEvtVBasicHeader::SetTime(Short_t* Time){
  cout<<"\t\t\t Setting time"<<endl;
  Long64_t SecTmp = Time[2]*Power(16,6)+Time[3]*Power(16,4)+Time[4]*Power(16,2)+Time[5]*Power(16,0);
  Short_t  mSecTmp = Time[6]*256+Time[7];
  fTimeGap = (fSec==0 && fmSec==0)?111:((SecTmp-fSec)*1000+(mSecTmp-fmSec));
  fSec = SecTmp;
  fmSec = mSecTmp;
}

void DmpEvtVBasicHeader::ShowTime() const{
  cout<<"Show normal time"<<endl;
}

void DmpEvtVBasicHeader::BookBranchHeaderBasic(){
  if (fRootFile) {
    fTree->SetBranchAddress("EventID",&fEvtID);
    fTree->SetBranchAddress("Second",&fSec);
    fTree->SetBranchAddress("mSecond",&fmSec);
    fTree->SetBranchAddress("TimeGap/mSec",&fTimeGap);
    fTree->SetBranchAddress("Particle ID",&fPID);
  } else {
    fTree->Branch("EventID",&fEvtID,"fEvtID/L");
    fTree->Branch("Second",&fSec,"fSec/L");
    fTree->Branch("mSecond",&fmSec,"fSec/S");
    fTree->Branch("TimeGap",&fTimeGap,"fTimeGap/L");
    fTree->Branch("ParticleID",&fPID,"fPID/S");
  }
}


