/*
 *  $Id: DmpVDataManager.cc, 2014-03-08 10:25:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"

#include "DmpVDataManager.h"

DmpEPhase  DmpVDataManager::gPhase = DmpCore::Phase::kProduct;

//-------------------------------------------------------------------
DmpVDataManager::DmpVDataManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fOutDataName("default"),
  fOutDataTree(0)
{
  fOutDataTree = new TTree("DAMPE","DAMPE");    // should rename in concrete class
}

//-------------------------------------------------------------------
DmpVDataManager::~DmpVDataManager(){
  delete fOutDataTree;
}

//-------------------------------------------------------------------
void DmpVDataManager::SetPhase(DmpEPhase p){
  gPhase = p;
}

//-------------------------------------------------------------------
DmpEPhase  DmpVDataManager::GetPhase(){
  return gPhase;
}

#include <sys/stat.h>       // mkdir()
//-------------------------------------------------------------------
bool DmpVDataManager::SetInDataPath(std::string path){
  if (path[path.length()-1] == '/') {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
// *
// *  TODO: check directory exist?
// *
  struct stat inPathStat;
  stat(fInDataPath.c_str(),&inPathStat);
  return S_ISDIR(inPathStat.st_mode);
}

//-------------------------------------------------------------------
void DmpVDataManager::SetOutDataPath(std::string path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include "TFile.h"
void DmpVDataManager::SaveOutput(){
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  delete aFile;
  std::cout<<"Result in : "<<fOutDataPath+fOutDataName<<std::endl;
  fOutDataName = "default";
}

//-------------------------------------------------------------------
void DmpVDataManager::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVDataManager::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S.root",p);
  return timeStamp;
}

