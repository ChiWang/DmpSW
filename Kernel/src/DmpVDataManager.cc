/*
 *  $Id: DmpVDataManager.cc, 2014-03-06 16:33:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>
#include "TSystem.h"

#include "DmpEventRaw.h"
#include "DmpVDataManager.h"

//------------------------------------------------------------------------------
DmpVDataManager::DmpVDataManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName(""),
  fEvtRaw(0)
{
  fEvtRaw = new DmpEventRaw();
}

//------------------------------------------------------------------------------
DmpVDataManager::~DmpVDataManager(){
  if(fEvtRaw != 0 ){
    delete fEvtRaw;
    fEvtRaw = 0;
  }
}

//------------------------------------------------------------------------------
void DmpVDataManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
void DmpVDataManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

