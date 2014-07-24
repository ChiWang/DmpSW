/*
 *  $Id: DmpRootIOSvc.h, 2014-07-21 09:38:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

#ifndef DmpRootIOSvc_H
#define DmpRootIOSvc_H

#include <boost/filesystem.hpp>     // path
#include <vector>
#include "DmpVSvc.h"

class TFile;
class TTree;

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
  bool WriteValid(const std::string &folderName,const std::string &treeName,const std::string &branchName); // in write list, no branch
  TTree* GetOutputTree(const std::string &folderName,const std::string &treeName);
  TTree* GetInputTree(const std::string &folderName,const std::string &treeName);
  void PrepareMetaData();
  bool PrepareEvent(const long &evtID); //only read fInTreeSet["Event"]
  void FillEvent(); // invoke in DmpCore::Run(), if fAlgMgr->ProcessThisEvent() return true

private:
  DmpRootIOSvc();

private:
typedef std::map<std::string, TTree*>  DmpRootIOTreeMap;                // key is "Tree"
typedef std::map<std::string, DmpRootIOTreeMap>  DmpRootIOFolderMap;    // key is "Folder"
  boost::filesystem::path   fInFileName;        // include path
  boost::filesystem::path   fOutFileName;       // include path. If is input file, set "INPUT"
  std::vector<std::string>  fWriteList;         // to fOutTreeSet
  TFile         *fInRootFile;
  TFile         *fOutRootFile;
  std::map<std::string,long>    fEntriesOfTree; // entries of each input event tree. key is "Folder/Tree"
  DmpRootIOFolderMap    fInTreeSet;     // input trees
  DmpRootIOFolderMap    fOutTreeSet;    // output trees
};

//-------------------------------------------------------------------
extern DmpRootIOSvc  *gRootIOSvc;

#endif


