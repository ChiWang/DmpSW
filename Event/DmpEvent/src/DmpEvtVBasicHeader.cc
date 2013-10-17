
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

void DmpEvtVBasicHeader::Reset(){
}

Bool_t  DmpEvtVBasicHeader::BookBranch(TTree* tree, Bool_t read, TString detector){
}

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

void DmpEvtVBasicHeader::BookBranchHeaderBasic(TTree* tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_EventID",&fEvtID);
    tree->SetBranchAddress(pre+"_Second",&fSec);
    tree->SetBranchAddress(pre+"_mSecond",&fmSec);
    tree->SetBranchAddress(pre+"_TimeGap",&fTimeGap);
    tree->SetBranchAddress(pre+"_ParticleID",&fPID);
  } else {
    tree->Branch(pre+"_EventID",&fEvtID,"fEvtID/L");
    tree->Branch(pre+"_Second",&fSec,"fSec/L");
    tree->Branch(pre+"_mSecond",&fmSec,"fSec/S");
    tree->Branch(pre+"_TimeGap",&fTimeGap,"fTimeGap/L");
    tree->Branch(pre+"_ParticleID",&fPID,"fPID/S");
  }
}


