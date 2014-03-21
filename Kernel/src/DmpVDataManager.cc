/*
 *  $Id: DmpVDataManager.cc, 2014-03-20 00:00:54 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "DmpVDataManager.h"

//-------------------------------------------------------------------
DmpVDataManager::DmpVDataManager()
 :fPgkID("Dmp"),
  fOutDataTree(0),
  fOutDataPath("./"),
  fInDataName("no"),
  fOutDataName("no"),
  fNote("no")
{
}

//-------------------------------------------------------------------
DmpVDataManager::~DmpVDataManager(){
}

//-------------------------------------------------------------------
void DmpVDataManager::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
void DmpVDataManager::SaveOutput(){
  SetOutDataName();
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  std::cout<<"Result in : "<<fOutDataPath+fOutDataName<<", entries = "<<fOutDataTree->GetEntries()<<std::endl;
  delete fOutDataTree;
  delete aFile;
  fInDataName = "no";
  fOutDataName = "no";
  fNote = "no";
}

#include <sys/stat.h>       // mkdir()
//-------------------------------------------------------------------
void DmpVDataManager::SetOutDataPath(const std::string &path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
void DmpVDataManager::SetOutDataName(){
  boost::filesystem::path inpath(fInDataName);
  if(fNote == "no"){
    fOutDataName = fPgkID+TimeStamp()+"_"+inpath.stem()+".root";
  }else{
    fOutDataName = fPgkID+TimeStamp()+"_"+inpath.stem()+"_"+fNote+".root";
  }
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVDataManager::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S",p);
  return timeStamp;
}


