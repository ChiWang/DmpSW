/*
 *  $Id: DmpVDataManager.cc, 2014-03-08 10:25:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "TTree.h"

#include "DmpVDataManager.h"

std::string DmpVDataManager::fInDataPath = "./";
std::string DmpVDataManager::fOutDataPath = "./";
std::string DmpVDataManager::fOutDataName = "default";      // "default" used in CreateDefaultName(). Do NOT change this value.
//------------------------------------------------------------------------------

DmpVDataManager::DmpVDataManager()
 :fOutDataTree(0)
{
  fOutDataTree = new TTree("DAMPE","DAMPE");    // should rename in concrete class
}

DmpVDataManager::~DmpVDataManager(){
  delete fOutDataTree;
}

//------------------------------------------------------------------------------
void DmpVDataManager::SetInDataPath(std::string path){
  if (path[path.length()-1] == '/') {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
void DmpVDataManager::SetOutDataPath(std::string path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
void DmpVDataManager::SetOutDataName(std::string name){
  fOutDataName = name;
}

//-------------------------------------------------------------------
#include "TFile.h"
void DmpVDataManager::SaveOutput(){
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  delete aFile;
  std::cout<<"Output : "<<fOutDataPath+fOutDataName<<std::endl;
  fOutDataName = "default";
}

void DmpVDataManager::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
#include <time.h>
bool DmpVDataManager::CreateDefaultName(){ // define fOutDataName
  if(fOutDataName != "default") return false;
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char name[20];
  strftime(name,99,"%Y%m%d%H%M%S.root",p);
  fOutDataName = name;  // add tag in UseDefaultDataName in concrete class
  return true;
}

