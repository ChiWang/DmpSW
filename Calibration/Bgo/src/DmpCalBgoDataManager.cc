/*
 *  $Id: DmpCalBgoDataManager.cc, 2014-04-04 21:28:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

#include "DmpCalBgoDataManager.h"
#include "DmpCalBgoMSD.h"
#include "DmpDetectorBgo.h"

//-------------------------------------------------------------------
DmpCalBgoDataManager::DmpCalBgoDataManager()
 :gInDataTree(0),
  fBgoMSDSet(0)
{
  fBgoMSDSet = new TClonesArray("DmpCalBgoMSD",300);
  int nBar = DmpDetector::Bgo::kPlaneNo*2*(DmpDetector::Bgo::kBarNo+DmpDetector::Bgo::kRefBarNo);
  for(short i=0;i<nBar;++i){    // cal. for all MSD
    fBgoMSDSet->New(i);
  }
}

//-------------------------------------------------------------------
DmpCalBgoDataManager::~DmpCalBgoDataManager(){
  fBgoMSDSet->Delete();
  fBgoMSDSet->Clear();
  delete fBgoMSDSet;
}

//-------------------------------------------------------------------
bool DmpCalBgoDataManager::InputData(const std::string &n){
  fInDataName = n;
// *
// *  TODO: set in data Tree
// *
  TFile *inFile = new TFile(n);
  gInDataTree = (TTree*)inFile->Get("RawEvent");
}

//-------------------------------------------------------------------
bool DmpCalBgoDataManager::InputData(const std::string &dat, const std::string &RootFile){
  fInDataName = n;
// *
// *  TODO: open root file ans set TTree at gInDataTree;
// *

}

//-------------------------------------------------------------------
void DmpCalBgoDataManager::Initialize(){
}

//-------------------------------------------------------------------
void DmpCalBgoDataManager::BookBranch(){
}

//-------------------------------------------------------------------
DmpCalBgoMSD* DmpCalBgoDataManager::GetBgoMSD(const int &id, const short &side){
  DmpCalBgoMSD *aMSD = 0;
  if(id > 100){ // return a normal bar
    aMSD = (DmpCalBgoMSD*)fBgoMSDSet->At(id%100*(DmpDetector::Bgo::kBarNo+DmpDetector::Bgo::kRefBarNo)+id/100);
  }else{        // return a Ref. bar
    aMSD = (DmpCalBgoMSD*)fBgoMSDSet->At(id*(DmpDetector::Bgo::kBarNo+DmpDetector::Bgo::kRefBarNo)+side);
  }
  return aMSD;
}

//-------------------------------------------------------------------
DmpCalBgoDataManager*  gDataMgr = DmpCalBgoDataManager::GetInstance();


