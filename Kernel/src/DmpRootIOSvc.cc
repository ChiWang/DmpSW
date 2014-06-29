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
  fInFileName("NOIN"),
  fInRootFile(0),
  fOutFilePath("./"),
  fOutFileName("NOOUT"),
  fOutRootFile(0),
  fWriteListOk(true)
{
  OptMap.insert(std::make_pair("InData/Read",   0));
  OptMap.insert(std::make_pair("InData/Update", 1));
  OptMap.insert(std::make_pair("OutData/Path",  2));
  OptMap.insert(std::make_pair("OutData/FileName",  3));
  OptMap.insert(std::make_pair("OutData/Write", 4));
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
      if (TString(argv).Contains(TString(".root"))){
        fInFileName = TString(argv);
      }else{
        fInFileName = TString(argv)+TString(".root");
      }
      break;
    }
    case 1: // InData/Update
    {
      if("./" != fOutFilePath){
        fOutFilePath = "WRONG_0";
        return;
      }
      if (TString(argv).Contains(TString(".root"))){
        fInFileName = TString(argv);
      }else{
        fInFileName = TString(argv)+TString(".root");
      }
      fOutFileName = fInFileName;
      break;
    }
    case 2: // OutData/Path
    {
      if(fInFileName == fOutFileName){
        fOutFilePath = "WRONG_0";
        return;
      }
      if(argv[argv.length()-1] == '/'){
        fOutFilePath = argv;
      }else{
        fOutFilePath = argv + "/";
      }
      break;
    }
    case 3: // OutData/FileName 
    {
      if(fInFileName == fOutFileName){
        fOutFilePath = "WRONG_0";
        return;
      }
      if (TString(argv).Contains(TString(".root"))){
        fOutFileName = TString(argv);
      }else{
        fOutFileName = TString(argv)+TString(".root");
      }
      break;
    }
    case 4: // OutData/Write
    {
      std::vector<std::string>  tempList;
      boost::split(tempList,argv,boost::is_any_of(";"));
      for(short i=0;i<tempList.size();++i){
        std::vector<std::string>  temp;
        boost::split(temp,tempList[i],boost::is_any_of("/"));
        if(3 != temp.size()){
          fWriteListOk = false;
          DmpLogError<<"Wrong path of writing data: "<<tempList[i]<<DmpLogEndl;
          return;
        }
        if("Event" == temp[0]){
          fWriteListEvt.push_back(tempList[i]);
        }else if("Metadata" == temp[0]){
          fWriteListMeta.push_back(tempList[i]);
        }else{
          fWriteListOk = false;
          DmpLogError<<"Wrong path of writing data: "<<tempList[i]<<DmpLogEndl;
          return;
        }
      }
      fWriteListOk = true;
      break;
    }
  }
}

//-------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
bool DmpRootIOSvc::Initialize(){
  DmpLogDebug<<"[DmpRootIOSvc::Initialize] initialization... "<<DmpLogEndl;  
  if(not fWriteListOk){
    DmpLogError<<"Write list error..."<<DmpLogEndl;
    return false;
  }
  if("WRONG_0" == fOutFilePath){
    DmpLogError<<"Can not set \'output file as a input file\' and \'output path\' at the same time"<<DmpLogEndl;
    return false;
  }
  if("NOIN" != fInFileName){
    DmpLogInfo<<"input data: "<<fInFileName<<DmpLogEndl;
    if(fInFileName == fOutFileName){
      fInRootFile = new TFile(fInFileName.c_str(),"update");
    }else{
      fInRootFile = new TFile(fInFileName.c_str(),"read");
    }
  }
  if("NOOUT" != fOutFileName){
    if(fInFileName == fOutFileName){
      fOutRootFile = fInRootFile;
    }else if(0 != fWriteListEvt.size() || 0 != fWriteListMeta.size()){
      if("./" != fOutFilePath){
        mkdir(fOutFilePath.c_str(),0755);
      }
      fOutRootFile = new TFile((TString)(fOutFilePath+fOutFileName),"RECREATE");
      fOutRootFile->mkdir("Event");
      fOutRootFile->mkdir("Metadata");
    }
  }
  DmpLogDebug<<"[DmpRootIOSvc::Initialize] ... initialization done "<<DmpLogEndl;  
  return true;
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::Finalize(){
  if(not gCore->InitializeDone()){
    return true;
  }
  if(fOutRootFile){
    SaveMetadata();
    SaveEventdata();
  }
  if(fInRootFile){  // must after Savexxxx
    fInRootFile->Close();
    delete fInRootFile;
  }
  if(fInFileName != fOutFileName && "NOOUT" != fOutFileName && 0 != fOutRootFile){
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
/*
template<typename T> bool DmpRootIOSvc::RegisterObject(const std::string &path,const std::string &className,T *&dataPtr){
  // path check
  std::vector<std::string>  temp;
  boost::split(temp,path,boost::is_any_of("/"));
  if(3 != temp.size()){
    DmpLogError<<"[DmpRootIOSvc::RegisterObject] input a wrong path: "<<path<<DmpLogEndl;
    return false;
  }
  // insert data buffer
  if(fTempDataBuf_MyClass.find(path) != fTempDataBuf_MyClass.end()){
    DmpLogError<<path<<" is existing in data buffer"<<DmpLogEndl;
    return false;
  }
  fTempDataBuf_MyClass.insert(std::make_pair(path,dataPtr));
  // check write list, if yes, create a branch
  if("Event" == temp[0]){
    for(short i=0;i<fWriteListEvt.size();++i){
      if(path == fWriteListEvt[i]){
        if(fOutEvtTreeSet.find(temp[0]+"/"+temp[1]) == fOutEvtTreeSet.end()){
          fOutEvtTreeSet.insert(std::make_pair(temp[0]+"/"+temp[1],new TTree(temp[1].c_str(),temp[1].c_str())));
          //fOutEvtTreeSet[temp[0]+"/"+temp[1]]->SetDirectory((TDirectory*));
        }
        fOutEvtTreeSet[temp[0]+"/"+temp[1]]->Branch(temp[2].c_str(),className.c_str(),&dataPtr,32000,2);
        return true;
      }
    }
  }else if("Metadata" == temp[0]){
    for(short i=0;i<fWriteListMeta.size();++i){
      if(path == fWriteListMeta[i]){
        if(fOutMetaTreeSet.find(temp[0]+"/"+temp[1]) == fOutMetaTreeSet.end()){
          fOutMetaTreeSet.insert(std::make_pair(temp[0]+"/"+temp[1],new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutMetaTreeSet[temp[0]+"/"+temp[1]]->Branch(temp[2].c_str(),className.c_str(),&dataPtr,32000,2);
        return true;
      }
    }
  }else{
    DmpLogError<<"wrong folder: path = "<<path<<DmpLogEndl;
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
template<typename T> bool DmpRootIOSvc::RegisterObject(const std::string &path,T *&dataPtr){
  // path check
  std::vector<std::string>  temp;
  boost::split(temp,path,boost::is_any_of("/"));
  if(3 != temp.size()){
    DmpLogError<<"[DmpRootIOSvc::RegisterObject] input a wrong path: "<<path<<DmpLogEndl;
    return false;
  }
  // insert data buffer
  if(fTempDataBuf_TClonesArray.find(path) != fTempDataBuf_TClonesArray.end()){
    DmpLogError<<path<<" exist in data buffer"<<DmpLogEndl;
    return false;
  }
  fTempDataBuf_TClonesArray.insert(std::make_pair(path,dataPtr));
  // check write list, if yes, create a branch
  if("Event" == temp[0]){
    for(short i=0;i<fWriteListEvt.size();++i){
      if(path == fWriteListEvt[i]){
        if(fOutEvtTreeSet.find(temp[0]+"/"+temp[1]) == fOutEvtTreeSet.end()){
          fOutEvtTreeSet.insert(std::make_pair(temp[0]+"/"+temp[1],new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutEvtTreeSet[temp[0]+"/"+temp[1]]->Branch(temp[2].c_str(),dataPtr,32000,2);
        return true;
      }
    }
  }else if("Metadata" == temp[0]){
    for(short i=0;i<fWriteListMeta.size();++i){
      if(path == fWriteListMeta[i]){
        if(fOutMetaTreeSet.find(temp[0]+"/"+temp[1]) == fOutMetaTreeSet.end()){
          fOutMetaTreeSet.insert(std::make_pair(temp[0]+"/"+temp[1],new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutMetaTreeSet[temp[0]+"/"+temp[1]]->Branch(temp[2].c_str(),dataPtr,32000,2);
        return true;
      }
    }
  }else{
    DmpLogError<<"wrong folder: path = "<<path<<DmpLogEndl;
    return false;
  }
  return true;
}
*/

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
    DmpLogInfo<<"[DmpRootIOSvc::SaveMetadata] No metadata to be stored..."<<DmpLogEndl;
    return;
  }
  fOutRootFile->cd("Metadata");
  for(DmpTreeSet::iterator it=fOutMetaTreeSet.begin();it!=fOutMetaTreeSet.end();++it){
    DmpLogInfo<<"Fill metadata "<<it->first<<DmpLogEndl;
    it->second->Fill();
    it->second->Write();
    delete it->second;
  }
}

//-------------------------------------------------------------------
void DmpRootIOSvc::SaveEventdata(){
  if(0 == fOutEvtTreeSet.size()){
    DmpLogInfo<<"[DmpRootIOSvc::SaveEventdata] No event data to be stored..."<<DmpLogEndl;
    return;
  }
  fOutRootFile->cd("Event");
  for(DmpTreeSet::iterator it=fOutEvtTreeSet.begin();it != fOutEvtTreeSet.end();++it){
    DmpLogInfo<<"\tTree: "<<it->first<<", entries = "<<it->second->GetEntries()<<DmpLogEndl;
    it->second->Write();
    delete it->second;
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::NewBranchInInputTree(const std::string &treeName)const{
  if(fOutFileName == fInFileName){
    if(fInRootFile->Get(treeName.c_str())){
      return true;
    }
  }
  return false;
}

