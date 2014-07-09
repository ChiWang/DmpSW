/*
 *  $Id: DmpRootIOSvc.cc, 2014-06-23 02:12:51 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

//#include <boost/algorithm/string.hpp>
//#include "TTree.h"
//#include "TFile.h"
#include "TClonesArray.h"

#include "DmpRootIOSvc.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpRootIOSvc::DmpRootIOSvc()
 :DmpVSvc("DmpRootIOSvc"),
  fInRootFile(0),
  fOutRootFile(0)
{
  fInFileName = "NOIN";
  fOutFileName = "NOOUT";
  OptMap.insert(std::make_pair("InData/Read",   0));
  OptMap.insert(std::make_pair("InData/Update", 1));
  OptMap.insert(std::make_pair("OutData/FileName",  2));
  OptMap.insert(std::make_pair("OutData/WriteList", 3));
}

//-------------------------------------------------------------------
DmpRootIOSvc::~DmpRootIOSvc(){
}

//-------------------------------------------------------------------
void DmpRootIOSvc::Set(const std::string &option,const std::string &argv){
  if(OptMap.find(option) == OptMap.end()){
    DmpLogError<<"No argument type: "<<option<<DmpLogEndl;
    throw;
  }
  switch (OptMap[option]){
    case 0: // InData/Read
    {
      fInFileName = argv;
      break;
    }
    case 1: // InData/Update
    {
      if("NOOUT" != fOutFileName.string()){
        DmpLogError<<"Can not set \'InData/Update\' after \'OutData/FileName\'"<<DmpLogEndl;
        fIniStatus = false;
        return;
      }
      fInFileName = argv;
      fOutFileName = argv;
      break;
    }
    case 2: // OutData/FileName 
    {
      if(fInFileName.string() == fOutFileName.string()){
        DmpLogError<<"Can not set \'OutData/FileName\' after \'InData/Update\'"<<DmpLogEndl;
        fIniStatus = false;
        return;
      }
      fOutFileName = argv;
      break;
    }
    case 3: // OutData/WriteList
    {
      std::vector<std::string>  tempList;
      boost::split(tempList,argv,boost::is_any_of(";"));
      for(short i=0;i<tempList.size();++i){
        std::vector<std::string>  temp;
        boost::split(temp,tempList[i],boost::is_any_of("/"));
        if(3 != temp.size()){
          DmpLogError<<"Wrong path of writing data: "<<tempList[i]<<DmpLogEndl;
          fIniStatus = false;
          return;
        }
        if("Event" == temp[0]){
          fWriteListEvt.push_back(tempList[i]);
        }else if("Metadata" == temp[0]){
          fWriteListMeta.push_back(tempList[i]);
        }else{
          DmpLogError<<"Wrong path of writing data: "<<tempList[i]<<DmpLogEndl;
          fIniStatus = false;
          return;
        }
      }
      break;
    }
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::Initialize(){
  DmpLogDebug<<"[DmpRootIOSvc::Initialize] initialization... "<<DmpLogEndl;  
  if(false == fIniStatus){
    return fIniStatus;
  }
  if("NOIN" != fInFileName.string()){
    if(".root" != fInFileName.extension()){
      DmpLogError<<"input data is not a root file... "<<fInFileName.string()<<DmpLogEndl;
      fIniStatus = false;
      return fIniStatus;
    }
    DmpLogInfo<<"input data: "<<fInFileName.string()<<DmpLogEndl;
    if(fInFileName.string() == fOutFileName.string()){
      fInRootFile = new TFile(fInFileName.string().c_str(),"update");
    }else{
      fInRootFile = new TFile(fInFileName.string().c_str(),"read");
    }
  }
  if("NOOUT" != fOutFileName.string()){
    if(".root" != fOutFileName.extension()){
      fOutFileName += ".root";
    }
    if(fInFileName.string() == fOutFileName.string()){
      fOutRootFile = fInRootFile;
    }else if(0 != fWriteListEvt.size() || 0 != fWriteListMeta.size()){
      if(not boost::filesystem::exists(fOutFileName.parent_path())){
        boost::filesystem::create_directories(fOutFileName.parent_path());
      }
      fOutRootFile = new TFile(fOutFileName.string().c_str(),"RECREATE");
      fOutRootFile->mkdir("Event");
      fOutRootFile->mkdir("Metadata");
      fOutRootFile->mkdir("Calibration");
    }
  }
  DmpLogDebug<<"[DmpRootIOSvc::Initialize] ... initialization done "<<DmpLogEndl;  
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::Finalize(){
  if(not gCore->InitializeDone()){
    return true;
  }
  if(fOutRootFile){
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] +--Writing "<<fOutFileName<<DmpLogEndl;
    SaveMetadata();
    SaveEventdata();
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] +--Done"<<DmpLogEndl;
  }
  if(fInRootFile){  // must after Savexxxx
    fInRootFile->Close();
    delete fInRootFile;
  }
  if(fInFileName.string() != fOutFileName.string() && "NOOUT" != fOutFileName.string()  && 0 != fOutRootFile){
    fOutRootFile->Close();
    delete fOutRootFile;
  }
  return true;
}

//-------------------------------------------------------------------
TObject* DmpRootIOSvc::ReadObject(const std::string &path){
  // check path level
  std::vector<std::string>  temp;
  boost::split(temp,path,boost::is_any_of("/"));
  if(3 != temp.size()){
    DmpLogError<<"[DmpRootIOSvc::ReadObject] input a wrong path: "<<path<<DmpLogEndl;
    return 0;
  }
  TObject *dataPtr = 0;
  // find object
  if(fTempDataBuf_MyClass.find(path) != fTempDataBuf_MyClass.end()){    // find it in fTempDataBuf_MyClass
    dataPtr = fTempDataBuf_MyClass[path];
  }else if(fTempDataBuf_TClonesArray.find(path) != fTempDataBuf_TClonesArray.end()){    // find it in fTempDataBuf_TClonesArray
    dataPtr = fTempDataBuf_TClonesArray[path];
  }else if(fInputDataBuf.find(path) != fInputDataBuf.end()){   // find it in fInputDataBuf
    dataPtr = fInputDataBuf[path];
  }else{    // find it in input root file, and insert it into fInputDataBuf
    std::string treeName = temp[0]+"/"+temp[1];
    if(fInEvtTreeSet.find(treeName) == fInEvtTreeSet.end()){
      fInEvtTreeSet.insert(std::make_pair(treeName,(TTree*)fInRootFile->Get(treeName.c_str())));
      fInEvtEntries.insert(std::make_pair(treeName,fInEvtTreeSet[treeName]->GetEntries()));
    }else{
      if(not fInEvtTreeSet[treeName]->GetListOfBranches()->FindObject(temp[2].c_str())){
        DmpLogError<<"the branch "<<temp[2]<<" not in "<<treeName<<DmpLogEndl;
        return 0;
      }
      fInEvtTreeSet[treeName]->SetBranchAddress(temp[2].c_str(),&dataPtr);
      fInputDataBuf.insert(std::make_pair(path,dataPtr));
    }
  }
  return dataPtr;
}

//-------------------------------------------------------------------
void DmpRootIOSvc::PrepareMetaData(){
  for(DmpTreeSet::iterator it=fOutMetaTreeSet.begin();it!=fOutMetaTreeSet.end();++it){
    it->second->GetEntry();
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::PrepareEvent(const long &evtID){
  if(0 == fInEvtTreeSet.size()){
    // some algorithm not use input root file, like Sim and Rdc
    return true;
  }
  bool atLeastOneTree = false;
  for(DmpTreeSet::iterator it=fInEvtTreeSet.begin();it!=fInEvtTreeSet.end();++it){
    if(evtID >= fInEvtEntries[it->first]){
      continue;
    }
    atLeastOneTree = true;
    it->second->GetEntry(evtID);
    DmpLogInfo<<it->first<<"\tevent ID = "<<evtID<<DmpLogEndl;
  }
  return atLeastOneTree;
}

//-------------------------------------------------------------------
void DmpRootIOSvc::FillEvent(){
  DmpLogDebug<<"Fill event "<<DmpLogEndl;
  for(DmpTreeSet::iterator it=fOutEvtTreeSet.begin();it!=fOutEvtTreeSet.end();++it){
    DmpLogDebug<<it->first<<"\tFill event "<<it->second->GetEntries()<<DmpLogEndl;
    it->second->Fill();
  }
}

//-------------------------------------------------------------------
void DmpRootIOSvc::SaveMetadata(){
  if(0 == fOutMetaTreeSet.size()){
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  +--No metadata to be stored..."<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  +--Saving metadata..."<<DmpLogEndl;
  }
  fOutRootFile->cd("Metadata");
  for(DmpTreeSet::iterator it=fOutMetaTreeSet.begin();it!=fOutMetaTreeSet.end();++it){
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  |  +--tree: "<<it->first<<DmpLogEndl;
    it->second->Fill();
    it->second->Write();
    delete it->second;
  }
}

//-------------------------------------------------------------------
void DmpRootIOSvc::SaveEventdata(){
  if(0 == fOutEvtTreeSet.size()){
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  +--No event data to be stored..."<<DmpLogEndl;
    return;
  }else{
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  +--Saving event data..."<<DmpLogEndl;
  }
  fOutRootFile->cd("Event");
  for(DmpTreeSet::iterator it=fOutEvtTreeSet.begin();it != fOutEvtTreeSet.end();++it){
    DmpLogInfo<<"[DmpRootIOSvc::Finalize] |  |  +--tree: "<<it->first<<", entries = "<<it->second->GetEntries()<<DmpLogEndl;
    it->second->Write();
    delete it->second;
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::NewBranchInInputTree(const std::string &treeName)const{
  if(fOutFileName.string()  == fInFileName.string()){
    if(fInRootFile->Get(treeName.c_str())){
      return true;
    }
  }
  return false;
}

