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

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtHeader.hh"

DmpEvtHeaderRaw::DmpEvtHeaderRaw()
 :fPackageID(-1)       // so first is 0
{}

DmpEvtHeaderRaw::~DmpEvtHeaderRaw(){
}

TTree* DmpEvtHeaderRaw::GetTree(TString treeName){
  BookTree(treeName);
  BookBranchHeader();
  fTree->Branch("PackageID",&fPackageID,"fPackageID/L");
  return fTree;
}

TTree* DmpEvtHeaderRaw::GetTree(TString treeName, TFile* rootFile){
  BookTree(treeName,rootFile);
  BookBranchHeader();
  fTree->SetBranchAddress("PackageID",&fPackageID);
  return fTree;
}

void DmpEvtHeaderRaw::IsValidPackage(){
  ++fPackageID;
}

Bool_t DmpEvtHeaderRaw::IsValidEvent(){
  ++fEvtID;
}

void DmpEvtHeaderRaw::SetMode(DmpDcdRunMode M0,DmpDcdRunMode M1,DmpDcdRunMode M2,DmpDcdRunMode M3){
  if ( M0==M1 && M0==M2 && M0==M3) {
    fMode = M0;
  } else {
    fMode = kMixed;
  }
}
