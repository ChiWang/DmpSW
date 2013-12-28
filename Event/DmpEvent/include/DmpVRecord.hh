/*=====================================================================
 *   File:   DmpVRecord.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   21:30:33
=====================================================================*/

#ifndef DmpVRecord_H
#define DmpVRecord_H

#include "TObject.h"
#include "TString.h"


class DmpVRecord :public TObject{
/*
 * DmpVRecord
 *
 *  when calibration, like dmpBgoPed, recored calibration results in rootfile and command version, and used data name.
 *
 *
 */

 public:
  DmpVRecord();
  virtual ~DmpVRecord();
  void SetVersion(Short_t v)    {fVersion = v;}
  void SetDataName(TString n)   {fDataName = n;}
  Short_t GetVersion()  const   {return fVersion;}
  TString GetDataName() const   {return fDataName;}

 protected:
  Short_t   fVersion;       // version of command
  TString   fDataName;      // used data name 

  ClassDef(DmpVRecord,1)
};

#endif


