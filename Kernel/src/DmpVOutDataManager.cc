/*
 *  $Id: DmpVOutDataManager.cc, 2014-03-11 19:50:31 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"

#include "DmpVOutDataManager.h"

//-------------------------------------------------------------------
DmpVOutDataManager::DmpVOutDataManager()
 :fOutDataPath("./"),
  fOutDataName("no"),
  fOutDataTree(0)
{
  fOutDataTree = new TTree("DAMPE","DAMPE");    // should rename in concrete class
}

//-------------------------------------------------------------------
DmpVOutDataManager::~DmpVOutDataManager(){
  delete fOutDataTree;
}

#include <sys/stat.h>       // mkdir()
//-------------------------------------------------------------------
void DmpVOutDataManager::SetOutDataPath(std::string path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include "TFile.h"
void DmpVOutDataManager::SaveOutput(){
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  delete aFile;
  std::cout<<"Result in : "<<fOutDataPath+fOutDataName<<std::endl;
  fOutDataName = "no";
}

//-------------------------------------------------------------------
void DmpVOutDataManager::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVOutDataManager::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S.root",p);
  return timeStamp;
}

