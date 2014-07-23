/*
 *  $Id: DmpDataBufSvc.cc, 2014-07-23 12:10:26 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/07/2014
*/

#include <boost/algorithm/string.hpp>
#include "DmpDataBufSvc.h"

//-------------------------------------------------------------------
DmpDataBufSvc::DmpDataBufSvc()
 :DmpVSvc("DmpDataBufSvc")
{}

//-------------------------------------------------------------------
DmpDataBufSvc::~DmpDataBufSvc(){
}

//-------------------------------------------------------------------
bool DmpDataBufSvc::Initialize(){
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpDataBufSvc::Finalize(){
  DmpLogInfo<<"[DmpDataBufSvc::Finalize] +--Deleting data..."<<DmpLogEndl;
  for(DmpDataBufFolderMap::iterator aFolder=fDataBufPool.begin();aFolder!=fDataBufPool.end();++aFolder){
    DmpDataBufTreeMap aTreeMap = aFolder->second;
    DmpLogInfo<<"[DmpDataBufSvc::Finalize] |  +--"<<aFolder->first<<std::endl;
    for(DmpDataBufTreeMap::iterator aTree=aTreeMap.begin();aTree!=aTreeMap.end();++aTree){
      DmpDataBufBranchMap aBranchMap = aTree->second;
    DmpLogInfo<<"[DmpDataBufSvc::Finalize] |  |  +--"<<aTree->first<<std::endl;
      for(DmpDataBufBranchMap::iterator it=aBranchMap.begin();it!=aBranchMap.end();++it){
    DmpLogInfo<<"[DmpDataBufSvc::Finalize] |  |  |  +--"<<it->first<<std::endl;
        delete it->second;
      }
    }
  }
  DmpLogInfo<<"[DmpDataBufSvc::Finalize] +--Done"<<DmpLogEndl;
  return true;
}

//-------------------------------------------------------------------
TObject* DmpDataBufSvc::ReadObject(const std::string &path){
  // check path
  std::string folderName, treeName, branchName;
  if(not PathCheck(path,folderName,treeName,branchName)){
    return 0;
  }
  // find object
  TObject *dataPtr = 0;
  if(fDataBufPool.find(folderName) != fDataBufPool.end()){    // find it in fDataBufPool
    if(fDataBufPool[folderName].find(treeName) != fDataBufPool[folderName].end()){
      if(fDataBufPool[folderName][treeName].find(branchName) != fDataBufPool[folderName][treeName].end()){
        dataPtr = fDataBufPool[folderName][treeName][branchName];
      }
    }
  }// create buffer map in input data buffer pool, not here
  if(0 == dataPtr){ // find it in fInputDataBufPool or input root file
    if(fInputDataBufPool.find(folderName) != fInputDataBufPool.end()){    // find it in fInputDataBufPool
      if(fInputDataBufPool[folderName].find(treeName) != fInputDataBufPool[folderName].end()){
        if(fInputDataBufPool[folderName][treeName].find(branchName) != fInputDataBufPool[folderName][treeName].end()){
          dataPtr = fInputDataBufPool[folderName][treeName][branchName];
        }
      }else{
        DmpDataBufBranchMap aNewBranchMap;
        fInputDataBufPool[folderName].insert(std::make_pair(treeName,aNewBranchMap));
      }
    }else{
      DmpDataBufTreeMap aNewTreeMap;
      fInputDataBufPool.insert(std::make_pair(folderName,aNewTreeMap));
      DmpDataBufBranchMap aNewBranchMap;
      fInputDataBufPool[folderName].insert(std::make_pair(treeName,aNewBranchMap));
    }
    if(0 == dataPtr){   // find it in input root file
      TTree *findTree = gRootIOSvc->GetInputTree(folderName,treeName);
      if(findTree){
        findTree->SetBranchAddress(branchName.c_str(),&dataPtr);
        fInputDataBufPool[folderName][treeName].insert(std::make_pair(branchName,dataPtr));
      }
    }
  }
  return dataPtr;
}

//-------------------------------------------------------------------
bool DmpDataBufSvc::PathCheck(const std::string &checkMe,std::string &folderName,std::string &treeName,std::string &branchName){
  std::vector<std::string> temp;
  boost::split(temp,checkMe,boost::is_any_of("/"));
  if(3 != temp.size()){
    DmpLogError<<"[DmpDataBufSvc::PathCheck] wrong path: "<<checkMe<<DmpLogEndl;
    return false;
  }else{
    folderName = temp[0];
    treeName = temp[1];
    branchName = temp[2];
  }
  return true;
}

//-------------------------------------------------------------------
DmpDataBufSvc *gDataBufSvc = DmpDataBufSvc::GetInstance();


