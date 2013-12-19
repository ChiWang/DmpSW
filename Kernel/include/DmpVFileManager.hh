/*=====================================================================
 *   File:   DmpVFileManager.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:06:40
=====================================================================*/

#ifndef DmpVFileManager_H
#define DmpVFileManager_H

#include "TObject.h"
#include "TString.h"

class DmpVFileManager : virtual public TObject{
/*
 * DmpVFileManager
 *
 *  
 *
*/
 public:
  DmpVFileManager();
  virtual ~DmpVFileManager();

  void  SetInDataPath(TString);
  void  SetOutDataPath(TString);
  void  SetDataName(TString name)   {fDataName = name;}
  TString GetInDataPath() const     {return fInDataPath;}
  TString GetOutDataPath() const    {return fOutDataPath;}

 protected:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  
  ClassDef(DmpVFileManager,0)

};

#endif


