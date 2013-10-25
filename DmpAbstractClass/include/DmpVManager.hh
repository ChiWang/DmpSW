/*=============================================================================
#       FileName :          DmpVManager.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-17   17:21:22
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-25   15:35:20
=============================================================================*/

#ifndef DmpVManager_H
#define DmpVManager_H

#include "TString.h"

class TFile;
class TTree;

class DmpVManager {
 public:
  DmpVManager();
  virtual ~DmpVManager();
  inline void   SetDataName(TString name)       {fDataName = name;}
  inline  TTree*  GetTreePointer() const        {return fTree;}
  inline  TString GetInDataPath() const         {return fInDataPath;}
  inline  TString GetOutDataPath() const        {return fOutDataPath;}
  void    SetInDataPath(TString path);
  void    SetOutDataPath(TString path);
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
  
};

#endif

