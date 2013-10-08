/*=============================================================================
#       FileName :          DmpRdcManager.hh
#       Version  :          0.0.1
#       Author   :          USTC    (ylzhang1@mail.ustc.edu.cn chiwang@mail.ustc.edu.cn zhzhy@mail.ustc.edu.cn)
#       Time     :          2013-08-03   09:21:56
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-11   09:02:05
=============================================================================*/

#ifndef DmpRdcManager_H
#define DmpRdcManager_H

#include "TString.h"

class TFile;
class DmpRdcHeader;
class DmpRdcPsd;
class DmpRdcStk;
class DmpRdcBgo;
class DmpRdcNud;

class DmpRdcManager {
 public:
  static DmpRdcManager* GetInstance();      // get DmpRdc Manager
  void Clear();                             // delete DmpRdc Manager

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
  void SaveRootFile();          // save all TTree of sub-detectors into fOutDataFile

 private:
  static DmpRdcManager*    fInstance;
  DmpRdcManager();
  ~DmpRdcManager();
  Bool_t TriggerCheck() const;

 private:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  TFile*    fOutDataFile;
  
 private:
  DmpRdcHeader*  fHeader;
  DmpRdcPsd*     fPsd;
  DmpRdcStk*     fStk;
  DmpRdcBgo*     fBgo;
  DmpRdcNud*     fNud;

};

#endif

