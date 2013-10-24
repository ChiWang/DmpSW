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

#include "DmpVManager.hh"

class DmpRdcHeader;
class DmpRdcPsd;
class DmpRdcStk;
class DmpRdcBgo;
class DmpRdcNud;

class DmpRdcManager : public DmpVManager{
 public:
  static DmpRdcManager* GetInstance();      // get DmpRdc Manager
  void Clear();                             // delete DmpRdc Manager
  Bool_t BookBranch();

  inline  DmpRdcHeader* GetHeader()const    {return fHeader;}
  inline  DmpRdcPsd*    GetPsd()  const     {return fPsd;}
  inline  DmpRdcStk*    GetStk()  const     {return fStk;}
  inline  DmpRdcBgo*    GetBgo()  const     {return fBgo;}
  inline  DmpRdcNud*    GetNud()  const     {return fNud;}

 public:
  void FillAnEvent();           // fill current event
  void SaveRootFile();          // save all TTree of sub-detectors into fOutRootFile

 private:
  static DmpRdcManager*    fInstance;
  DmpRdcManager();
  ~DmpRdcManager();
  Bool_t TriggerCheck() const;

 private:
  DmpRdcHeader*  fHeader;
  DmpRdcPsd*     fPsd;
  DmpRdcStk*     fStk;
  DmpRdcBgo*     fBgo;
  DmpRdcNud*     fNud;

};

#endif

