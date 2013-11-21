/*=============================================================================
#       FileName :          DmpEvtHeader.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-15   23:45:53
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   22:15:57
=============================================================================*/

#include "TTree.h"
#include "TString.h"

#include "DmpEvtHeader.hh"

DmpEvtHeaderRaw::DmpEvtHeaderRaw()
 :fPackageID(-1)       // so first is 0
{}

DmpEvtHeaderRaw::~DmpEvtHeaderRaw(){
}

//______________________________________________________________________________
void DmpEvtHeaderRaw::SetTime(Short_t *Time){
  std::cout<<"\t\t\t Setting time"<<std::endl;
  Long64_t SecTmp = Time[2]*Power(16,6)+Time[3]*Power(16,4)+Time[4]*Power(16,2)+Time[5]*Power(16,0);
  Short_t  mSecTmp = Time[6]*256+Time[7];
  fTimeGap = (fSec==0 && fmSec==0)?111:((SecTmp-fSec)*1000+(mSecTmp-fmSec));
  fSec = SecTmp;
  fmSec = mSecTmp;
}

Bool_t DmpEvtHeaderRaw::BookBranch(TTree *tree, Bool_t read, TString pre){
  BookBranchVHeader(tree, read, pre);
  BookBranchHeaderRaw(tree, read, pre);
  return true;
}

void DmpEvtHeaderRaw::IsValidPackage(){
  ++fPackageID;
}

Bool_t DmpEvtHeaderRaw::IsValidEvent(){
  ++fEvtID;
}

void DmpEvtHeaderRaw::BookBranchHeaderRaw(TTree *tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_PackageID",&fPackageID);
  } else {
    tree->Branch(pre+"_PackageID",&fPackageID,"fPackageID/L");
  }
}


