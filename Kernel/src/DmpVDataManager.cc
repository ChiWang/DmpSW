/*
 *  $Id: DmpVDataManager.cc, 2014-03-06 21:43:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "TTree.h"

#include "DmpVDataManager.h"

//------------------------------------------------------------------------------
DmpVDataManager::DmpVDataManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fOutDataName(""),
  fOutDataTree(0)
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
#include "TFile.h"
void DmpVDataManager::SaveOutput(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  TFile *aFile = new TFile((TString)fOutDataName,"recreate");
  fOutDataTree->Write();
  aFile->Close();
  delete aFile;
}

