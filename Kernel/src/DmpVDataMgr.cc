/*
 *  $Id: DmpVDataMgr.cc, 2014-04-12 17:22:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"
#include "TFile.h"

#include "DmpVDataMgr.h"

//-------------------------------------------------------------------
DmpVDataMgr::DmpVDataMgr()
 :fOutDataTree(0),
  fInData("no"),
  fOutDataPath("./"),
  fOutDataName("no"),
  fPgkID("Dmp"),
  fNote("no")
{
}

//-------------------------------------------------------------------
DmpVDataMgr::~DmpVDataMgr(){
}

//-------------------------------------------------------------------
void DmpVDataMgr::FillEvent(){
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
void DmpVDataMgr::SaveOutput(){
  SetOutDataName();
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  std::cout<<"\n===>\tResult in : "<<fOutDataPath+fOutDataName<<", entries = "<<fOutDataTree->GetEntries()<<std::endl<<std::endl;
  delete fOutDataTree;
  delete aFile;
  fNote = "no";
  fInData = "no";
}

//-------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
void DmpVDataMgr::SetOutDataPath(const std::string &argv){
  if (argv[argv.length()-1] == '/') {
    fOutDataPath = argv;
  } else {
    fOutDataPath = argv + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
void DmpVDataMgr::SetOutDataName(){
  boost::filesystem::path inpath(fInData);
  if(fNote == "no"){
    fOutDataName = fPgkID+inpath.stem()+".root";
    //fOutDataName = fPgkID+TimeStamp()+inpath.stem()+".root";
  }else{
    fOutDataName = fPgkID+inpath.stem()+"_"+fNote+".root";
    //fOutDataName = fPgkID+TimeStamp()+inpath.stem()+"_"+fNote+".root";
  }
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVDataMgr::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S_",p);
  return timeStamp;
}


