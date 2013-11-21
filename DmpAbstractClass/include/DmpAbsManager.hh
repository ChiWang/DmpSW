/*=============================================================================
#       FileName :          DmpAbsManager.hh
#       Version  :          0.0.1
#       Author   :          DAMPE software group
#                           Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-17   17:21:22
#
#------------------------------------------------------------------------------
#       Description  :
#           1)  access to Database
#           2)  input output method
#           3)  Book tree, save root file
#
#------------------------------------------------------------------------------
#       History  :
#           2013/11/07  inherit from TObject.   Chi.WANG
#                                          Update:  2013-11-11   09:08:48
=============================================================================*/

#ifndef DmpAbsManager_H
#define DmpAbsManager_H

//#include "TObject.h"
#include "TString.h"

class TFile;
class TTree;

//class DmpAbsManager : public TObject {
class DmpAbsManager {
 public:
  DmpAbsManager();
  //DmpAbsManager(const DmpAbsManager *other);
  virtual ~DmpAbsManager();

  TTree*  GetTreePointer() const;
  TString GetInDataPath() const;
  TString GetOutDataPath() const;
  void    SetInDataPath(TString path);
  void    SetOutDataPath(TString path);
  void    SetDataName(TString name);
  void    ResetRootFile();
  Bool_t  BookTree();

 public:
  virtual Bool_t    BookBranch() = 0;
  virtual void      SaveRootFile();

 protected:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  TFile     *fInRootFile;
  TFile     *fOutRootFile;
  TTree     *fTree;
  
// ClassDef(DmpAbsManager,1)        // adding class in root
};

inline TTree* DmpAbsManager::GetTreePointer() const{
  return fTree;
}

inline TString DmpAbsManager::GetInDataPath() const{
  return fInDataPath;
}

inline TString DmpAbsManager::GetOutDataPath() const{
  return fOutDataPath;
}

inline void DmpAbsManager::SetDataName(TString name){
  fDataName = name;
}

#endif


