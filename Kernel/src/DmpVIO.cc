/*
 *  $Id: DmpVIO.cc, 2014-04-08 10:31:09 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"
#include "TFile.h"

#include "DmpVIO.h"

//-------------------------------------------------------------------
DmpVIO::DmpVIO()
 :fOutDataTree(0),
  fInData("no"),
  fOutDataPath("./"),
  fOutDataName("no"),
  fPgkID("Dmp"),
  fNote("no")
{
}

//-------------------------------------------------------------------
DmpVIO::~DmpVIO(){
}

//-------------------------------------------------------------------
void DmpVIO::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl<<std::endl;
#endif
  fOutDataTree->Fill();
  ResetEvent();
}

//-------------------------------------------------------------------
void DmpVIO::SaveOutput(){
  SetOutDataName();
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  std::cout<<"Result in : "<<fOutDataPath+fOutDataName<<", entries = "<<fOutDataTree->GetEntries()<<std::endl;
  delete fOutDataTree;
  delete aFile;
  fNote = "no";
}

//-------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
void DmpVIO::SetOutDataPath(const std::string &path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
void DmpVIO::SetOutDataName(){
  boost::filesystem::path inpath(fInData);
  if(fNote == "no"){
    fOutDataName = fPgkID+TimeStamp()+"_"+inpath.stem()+".root";
  }else{
    fOutDataName = fPgkID+TimeStamp()+"_"+inpath.stem()+"_"+fNote+".root";
  }
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVIO::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S",p);
  return timeStamp;
}


