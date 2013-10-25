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


