/*
 *  $Id: DmpIOSvc.h, 2014-05-22 09:24:24 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

#ifndef DmpIOSvc_H
#define DmpIOSvc_H

#include <vector>
#include <fstream>

#include "boost/algorithm/string.hpp"

#include "TTree.h"

#include "DmpVSvc.h"

class TObject;
class TFile;
class TTree;

class DmpIOSvc : public DmpVSvc{
/* 
 *  DmpIOSvc
 *
 *      it's the first element in DmpServiceManager
 *      it's a singleton for eanch job
 *      only output one root file
 */
public:
  static DmpIOSvc* GetInstance(){
    static DmpIOSvc instance;
    return &instance;
  }
  virtual ~DmpIOSvc();
  void Set(const std::string&,const std::string&);
  bool Initialise();
  bool Finalize();

public:
  template <typename T>
  bool ReadBranch(const std::string &path,T *&dataPtr){     // ReadBranch only used to read a input data.
  /*
   * setBranchAddress by the pointer of event class or TClonesArray.
   *
   *    path = RootFileName/TreeName/BranchName
   *
   */
    std::vector<std::string> pathLevel;
    boost::split(pathLevel,path,boost::is_any_of("/"));
    if(3 != pathLevel.size()){
      DmpLogError<<"path ("<<path<<") should be RootFileName/TreeName/BranchName"<<DmpLogEndl;
      return false;
    }
    TTree *tree = GetTree(pathLevel[0],pathLevel[1]);
    if(tree){
      tree->SetBranchAddress(pathLevel[2].c_str(),&dataPtr);
    }else{
      return false;
    }
    return true;
  }
  template <typename T>
  bool AddBranch(const std::string &path,T *&dataPtr){      // AddBranch only used to write data.
  /*
   * book a new branch into output root file by event class's name.
   *
   *    path = TreeName/BranchName/NameOfEventClass
   *
   * book a new branch into output root file by TClonesArray.
   *
   *    path = TreeName/BranchName
   *
   */
    DmpLogInfo<<"add new branch: "<<path<<DmpLogEndl;
    std::vector<std::string> pathLevel;
    boost::split(pathLevel,path,boost::is_any_of("/"));
    if(2 == pathLevel.size()){    // book branch for TClonesArray
      BookTree(pathLevel[0])->Branch(pathLevel[1].c_str(),dataPtr,32000,2);
    }else if( 3 == pathLevel.size()){ // book branch for event class
      BookTree(pathLevel[0])->Branch(pathLevel[1].c_str(),pathLevel[2].c_str(),&dataPtr,32000,2);
    }else{
      DmpLogError<<"path ("<<path<<") should be TreeName/BranchName or TreeName/Branch/EventClassName"<<DmpLogEndl;
      return false;
    }
    return true;
  }
  void FillEvent();
  void InFileTag(const std::string&);

private:
  DmpIOSvc();
  std::string Timestamp();
  TTree* GetTree(const std::string &rootFileName,const std::string &treeName)const;
  TTree* BookTree(const std::string &treeName);

private:
  std::vector<TFile*>   fInRootFile;

private:
  std::string           fOutFilePath;       // file path. default is "./". if is input file, set "INPUT"
  std::string           fOutFileName;       // file name. if is input file, set "INPUT"
  TFile                 *fOutRootFile;
  std::vector<TTree*>   fOutTreeSet;

  bool          fUseTimestamp;
  std::string   fTag;       // job tag, include notes
  std::string   fInFileTag;

};

#endif

