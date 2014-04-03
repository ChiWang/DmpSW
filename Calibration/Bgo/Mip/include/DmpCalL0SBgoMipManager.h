/*=============================================================================
#       FileName :          DmpCalL0SBgoMipManager.h
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-17   15:44:29
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-17   15:44:29
=============================================================================*/

#ifndef DmpCalL0SBgoMipManager_H
#define DmpCalL0SBgoMipManager_H

#include "TString.h"

class TFile;
class TTree;
class DmpRdcHeader;
class DmpRdcPsd;
class DmpRdcStk;
class DmpRdcBgo;
class DmpRdcNud;

class DmpRdcManager {
 public:
  static DmpRdcManager* GetInstance();      // get DmpRdc Manager
  void Clear();                             // delete DmpRdc Manager
  TTree* BookTree(TString treeName);
  Bool_t BookBranch(TTree* tree, Bool_t read=0);

  inline void SetInDataPath(TString path)   {fInDataPath=path;}
  inline void SetDataName(TString name)     {fDataName=name;}
  inline void SetOutDataPath(TString path)  {fOutDataPath=path;}
  inline TString GetInDataPath() const      {return fInDataPath;}
  inline TString GetOutDataPath() const     {return fOutDataPath;}
  inline  DmpRdcHeader* GetHeader()const    {return fHeader;}
  inline  DmpRdcPsd*    GetPsd()  const     {return fPsd;}
  inline  DmpRdcStk*    GetStk()  const     {return fStk;}
  inline  DmpRdcBgo*    GetBgo()  const     {return fBgo;}
  inline  DmpRdcNud*    GetNud()  const     {return fNud;}

  void FillAnEvent();           // fill current event
  void SaveRootFile();          // save all TTree of sub-detectors into fOutRootFile

 private:
  static DmpRdcManager*    fInstance;
  DmpRdcManager();
  ~DmpRdcManager();
  Bool_t TriggerCheck() const;

 private:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  TFile*    fOutRootFile;
  TTree*    fTree;
  
 private:
  DmpRdcHeader*  fHeader;
  DmpRdcPsd*     fPsd;
  DmpRdcStk*     fStk;
  DmpRdcBgo*     fBgo;
  DmpRdcNud*     fNud;

};

#endif

