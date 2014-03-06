/*
 *  $Id: DmpVDataManager.cc, 2014-03-06 21:43:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDegub
#include <iostream>
#endif
#include "DmpEventRaw.h"
#include "DmpVDataManager.h"

using namespace std;
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
void DmpVDataManager::SetInDataPath(string path){
  if (path.[path.length()-1] == '/') {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
#include <sys/stat.h>       // mkdir()
void DmpVDataManager::SetOutDataPath(string path){
  if (path.[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath,0755);
}

