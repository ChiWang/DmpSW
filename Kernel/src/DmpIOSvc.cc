/*
 *  $Id: DmpIOSvc.cc, 2014-05-23 10:31:45 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

//#include "TTree.h"
#include "TFile.h"

#include "DmpIOSvc.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpIOSvc::DmpIOSvc()
 :DmpVSvc("DmpIOSvc"),
  fInFileTag(""),
  fOutFilePath("./"),
  fOutFileName("NO"),
  fOutRootFile(0),
  fUseTimestamp(true),
  fTag("Dmp")
{
  OptMap.insert(std::make_pair("InData/Read",   0));
  OptMap.insert(std::make_pair("InData/Update", 1));
  OptMap.insert(std::make_pair("OutData/Path",  2));
  OptMap.insert(std::make_pair("OutData/Tag",   3));
  OptMap.insert(std::make_pair("OutData/Timestamp", 4));
}

//-------------------------------------------------------------------
DmpIOSvc::~DmpIOSvc(){
}

//-------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
#include "boost/lexical_cast.hpp"
void DmpIOSvc::Set(const std::string &option,const std::string &argv){
  if(OptMap.find(option) == OptMap.end()){
    DmpLogError<<"No argument type: "<<option<<DmpLogEndl;
  }
  switch (OptMap[option]){
    case 0:
    {// InData/Read
      fInRootFile.insert(std::make_pair(argv,new TFile(argv.c_str(),"read")));
      InFileTag(argv);
      break;
    }
    case 1:
    {// InData/Update
      fInRootFile.insert(std::make_pair(argv,new TFile(argv.c_str(),"update")));
      if("./" != fOutFilePath){
        fOutFilePath = "WRONG_0";
        return;
      }
      fOutFilePath = argv;
      fOutFileName = "INPUT";
      fOutRootFile = fInRootFile[argv];
      break;
    }
    case 2:
    {// OutData/Path 
      if("./" != fOutFilePath){
        fOutFilePath = "WRONG_0";
        return;
      }
      if(argv[argv.length()-1] == '/'){
        fOutFilePath = argv;
      }else{
        fOutFilePath = argv + "/";
      }
      mkdir(fOutFilePath.c_str(),0755);
      break;
    }
    case 3:
    {// OutData/Tag 
      fTag += argv;
      break;
    }
    case 4:
    {// OutData/Timestamp
      if("off" == argv){
        fUseTimestamp = false;
      }else if("on" == argv){
        fUseTimestamp = true;
      }else{
        DmpLogWarning<<"Wrong option("<<argv<<") of Timestamp. using the default option off}"<<DmpLogEndl;
        fUseTimestamp = false;
      }
      break;
    }
  }
}

//-------------------------------------------------------------------
bool DmpIOSvc::Initialize(){
  if("WRONG_0" == fOutFilePath){
    DmpLogError<<"Can not set \'output file as a input file\' and \'output path\' at the same time"<<DmpLogEndl;
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
//  Save output
#include "DmpRandom.h"
bool DmpIOSvc::Finalize(){
  if(not gCore->InitializeDone()) return false;
  if("INPUT" != fOutFileName){
    if(DmpRandom::fActive){
      fOutFileName = fTag + fInFileTag + Timestamp() +"_Seed_"+boost::lexical_cast<std::string>(DmpRandom::GetSeed())+".root";
    }else{
      fOutFileName = fTag + fInFileTag + Timestamp() +".root";
    }
    DmpLogInfo<<"Result in "<<fOutFilePath+fOutFileName<<DmpLogEndl;
    fOutRootFile = new TFile((TString)(fOutFilePath+fOutFileName),"recreate");
  }else{
    DmpLogInfo<<"Result in the input file: "<<fOutFilePath<<DmpLogEndl;
    fOutRootFile->cd();
  }
  for(short i=0;i<fOutTreeSet.size();++i){
    DmpLogInfo<<"\tTree: "<<fOutTreeSet[i]->GetName()<<", entries = "<<fOutTreeSet[i]->GetEntries()<<DmpLogEndl;
    fOutTreeSet[i]->Write();
    delete fOutTreeSet[i];
  }
  if("INPUT" != fOutFileName && "NO" != fOutFileName){
    fOutRootFile->Close();
    delete fOutRootFile;
  }
  for(std::map<std::string,TFile*>::iterator it=fInRootFile.begin(); it!=fInRootFile.end(); ++it){
    it->second->Close();
    delete it->second;
  }
  DmpLogDebug<<DmpLogEndl;
  return true;
}

//-------------------------------------------------------------------
void DmpIOSvc::FillEvent(){
  for(short i=0;i<fOutTreeSet.size();++i){
    fOutTreeSet[i]->Fill();
  }
  DmpLogInfo<<"\tFill event "<<fOutTreeSet[0]->GetEntries()<<DmpLogEndl;
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
void DmpIOSvc::InFileTag(const std::string &filename){
  boost::filesystem::path inpath(filename);
  fInFileTag += "_"+inpath.stem().string();
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpIOSvc::Timestamp(){
  if(not fUseTimestamp) return "";
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"_%Y%m%d%H%M%S",p);
  return timeStamp;
}

//-------------------------------------------------------------------
TTree* DmpIOSvc::GetTree(const std::string &rootFileName,const std::string &treeName)const{
  if(fInRootFile.find(rootFileName) == fInRootFile.end()){
    DmpLogError<<"not has the input root file "<<rootFileName<<DmpLogEndl;
    return 0;
  }
  TTree *tree = dynamic_cast<TTree*>(fInRootFile.find(rootFileName)->second->Get(treeName.c_str()));
  return tree;
}

//-------------------------------------------------------------------
TTree* DmpIOSvc::BookTree(const std::string &treeName){
  short index = -1;
  for(short i=0;i<fOutTreeSet.size();++i){
    if(treeName == fOutTreeSet[i]->GetName()){
      index = i;
      break;
    }
  }
  if(-1 == index){
    index = fOutTreeSet.size();
    fOutTreeSet.push_back(new TTree(treeName.c_str(),treeName.c_str()));
  }
  return fOutTreeSet[index];
}



