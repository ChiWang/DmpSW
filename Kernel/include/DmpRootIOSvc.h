/*
 *  $Id: DmpRootIOSvc.h, 2014-06-23 02:12:49 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

#ifndef DmpRootIOSvc_H
#define DmpRootIOSvc_H

#include <boost/filesystem.hpp>     // path
#include <boost/algorithm/string.hpp>
#include "TTree.h"
#include "TFile.h"
#include <vector>
#include "DmpVSvc.h"

class TObject;
//class TFile;
//class TTree;

class DmpRootIOSvc : public DmpVSvc{
/* 
 *  DmpRootIOSvc
 *
 *      it's the first element in DmpServiceManager
 *      it's a singleton for eanch job
 *      only one input and one output root file
 *      input of Simulation and Rdc is not compatible.
 */
public:
  static DmpRootIOSvc* GetInstance(){
    static DmpRootIOSvc instance;
    return &instance;
  }
  ~DmpRootIOSvc();
  void Set(const std::string&,const std::string&);
  bool Initialize();
  bool Finalize();

public:
  TObject* ReadObject(const std::string &path);  // if path/dataPtr not in any data buffer, use dataPtr to read a branch from input rootfile;
  template<typename T> bool RegisterObject(const std::string &path,const std::string &className,T *&dataPtr);  // path = Folder/Tree/Branch
  template<typename T> bool RegisterObject(const std::string &path,T *&dataPtr);   // path = Folder/Tree/Branch
  void PrepareMetaData();   // invoke in DmpCore::Run(), in the beginning
  bool PrepareEvent(const long &evtID); // invoke in DmpCore::Run(), for evry event, before fAlgMgr->ProcessThisEvent()
  void FillEvent(); // invoke in DmpCore::Run(), if fAlgMgr->ProcessThisEvent() return true

private:
  DmpRootIOSvc();
  void SaveMetadata();
  void SaveEventdata();
  void SaveCalibrationResult();
  bool NewBranchInInputTree(const std::string &t)const;

private:
typedef std::map<std::string, TTree*>  DmpTreeSet;          // key is "Folder/Tree"
  boost::filesystem::path   fInFileName;        // include path
  boost::filesystem::path   fOutFileName;       // include path. If is input file, set "INPUT"
  TFile         *fInRootFile;
  TFile         *fOutRootFile;
  DmpTreeSet    fInEvtTreeSet;      // event data, entries >=1
  std::map<std::string,long>    fInEvtEntries;      // entries of each input event tree
  DmpTreeSet    fInMetaTreeSet;     // metadata, entries = 1
  std::vector<std::string>  fWriteListEvt;      // to fOutEvtTreeSet
  std::vector<std::string>  fWriteListMeta;     // to fOutMetaTreeSet
  DmpTreeSet    fOutEvtTreeSet;     // event data, entries >= 1 for one job
  DmpTreeSet    fOutMetaTreeSet;    // metadata, one entry for whole job

private:
typedef std::map<std::string, TObject*>  DmpDataBuffer;     // key is "Folder/Tree/Branch"
  DmpDataBuffer     fInputDataBuf;  // My event class and TClonesArray all in me
  DmpDataBuffer     fTempDataBuf_MyClass;   // all the rest event classes
  DmpDataBuffer     fTempDataBuf_TClonesArray;  // all the rested TColnesArray

};

//-------------------------------------------------------------------
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
        std::string treeName = temp[0]+"/"+temp[1];
        if(fOutEvtTreeSet.find(treeName) == fOutEvtTreeSet.end()){
          if(NewBranchInInputTree(treeName)){
            DmpLogError<<"can not book new branch \'"<<path<<"\', since the tree in input root file..."<<DmpLogEndl;
            return false;
          }
          fOutEvtTreeSet.insert(std::make_pair(treeName,new TTree(temp[1].c_str(),temp[1].c_str())));
          //fOutEvtTreeSet[temp[0]+"/"+temp[1]]->SetDirectory((TDirectory*));
        }
        fOutEvtTreeSet[treeName]->Branch(temp[2].c_str(),className.c_str(),&dataPtr,32000,2);
        DmpLogInfo<<"[DmpRootIOSvc::RegisterObject] add new branch "<<path<<DmpLogEndl;
        break;
      }
    }
  }else if("Metadata" == temp[0]){
    for(short i=0;i<fWriteListMeta.size();++i){
      if(path == fWriteListMeta[i]){
        std::string treeName = temp[0]+"/"+temp[1];
        if(fOutMetaTreeSet.find(treeName) == fOutMetaTreeSet.end()){
          if(NewBranchInInputTree(treeName)){
            DmpLogError<<"can not book new branch \'"<<path<<"\', since the tree in input root file..."<<DmpLogEndl;
            return false;
          }
          fOutMetaTreeSet.insert(std::make_pair(treeName,new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutMetaTreeSet[treeName]->Branch(temp[2].c_str(),className.c_str(),&dataPtr,32000,2);
        DmpLogInfo<<"[DmpRootIOSvc::RegisterObject] add new branch "<<path<<DmpLogEndl;
        break;
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
  //return true;
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
        std::string treeName = temp[0]+"/"+temp[1];
        if(fOutEvtTreeSet.find(treeName) == fOutEvtTreeSet.end()){
          if(NewBranchInInputTree(treeName)){
            DmpLogError<<"can not book new branch \'"<<path<<"\', since the tree in input root file..."<<DmpLogEndl;
            return false;
          }
          fOutEvtTreeSet.insert(std::make_pair(treeName,new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutEvtTreeSet[treeName]->Branch(temp[2].c_str(),dataPtr,32000,2);
        DmpLogInfo<<"[DmpRootIOSvc::RegisterObject] add new branch "<<path<<DmpLogEndl;
        break;
      }
    }
  }else if("Metadata" == temp[0]){
    for(short i=0;i<fWriteListMeta.size();++i){
      if(path == fWriteListMeta[i]){
        std::string treeName = temp[0]+"/"+temp[1];
        if(fOutMetaTreeSet.find(treeName) == fOutMetaTreeSet.end()){
          if(NewBranchInInputTree(treeName)){
            DmpLogError<<"can not book new branch \'"<<path<<"\', since the tree in input root file..."<<DmpLogEndl;
            return false;
          }
          fOutMetaTreeSet.insert(std::make_pair(treeName,new TTree(temp[1].c_str(),temp[1].c_str())));
        }
        fOutMetaTreeSet[treeName]->Branch(temp[2].c_str(),dataPtr,32000,2);
        DmpLogInfo<<"[DmpRootIOSvc::RegisterObject] add new branch "<<path<<DmpLogEndl;
        break;
      }
    }
  }else{
    DmpLogError<<"wrong folder: path = "<<path<<DmpLogEndl;
    return false;
  }
  return true;
}


#endif


