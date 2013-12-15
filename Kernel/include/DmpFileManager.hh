/*=====================================================================
 *   File:   DmpFileManager.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:06:40
=====================================================================*/

#ifndef DmpFileManager_H
#define DmpFileManager_H

#include "TObject.h"
#include "TString.h"

class DmpFileManager : virtual public TObject{
/*
 * DmpFileManager
 *
 *  
 *
*/
 public:
  DmpFileManager();
  virtual ~DmpFileManager();

  void  SetInDataPath(TString);
  void  SetOutDataPath(TString);
  void  SetDataName(TString name)   {fDataName = name;}
  TString GetInDataPath() const     {return fInDataPath;}
  TString GetOutDataPath() const    {return fOutDataPath;}

 protected:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  
  ClassDef(DmpFileManager,0)

};

#endif


