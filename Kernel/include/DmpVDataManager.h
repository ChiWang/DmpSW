/*
 *  $Id: DmpVDataManager.h, 2014-03-06 17:19:31 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataManager_H
#define DmpVDataManager_H

#include "TString.h"

class DmpEventRaw;

class DmpVDataManager{
/*
 *  DmpVDataManager
 *
 *
*/
 public:
  DmpVDataManager();
  virtual ~DmpVDataManager();
  //virtual Bool_t Core()=0;

  void  SetInDataPath(TString);
  void  SetOutDataPath(TString);
  void  SetDataName(TString name)   {fDataName = name;}
  DmpEventRaw*  GetRawEvent() const {return fEvtRaw;}
  //TString GetInDataPath() const     {return fInDataPath;}
  //TString GetOutDataPath() const    {return fOutDataPath;}

 protected:
  TString       fInDataPath;
  TString       fOutDataPath;
  TString       fDataName;
  DmpEventRaw   *fEvtRaw;
};

#endif

