/*
 *  $Id: DmpVDataManager.cc, 2014-03-20 00:00:54 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "DmpVDataManager.h"

//-------------------------------------------------------------------
DmpVDataManager::DmpVDataManager()
 :fInDataName("no"),
  fOutDataPath("./"),
  fOutDataName("no"),
  fNote("no")
{
}

//-------------------------------------------------------------------
DmpVDataManager::~DmpVDataManager(){
}

#include <sys/stat.h>       // mkdir()
//-------------------------------------------------------------------
void DmpVDataManager::SetOutDataPath(const std::string &path){
  if (path[path.length()-1] == '/') {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath.c_str(),0755);
}

//-------------------------------------------------------------------
#include <time.h>
std::string DmpVDataManager::TimeStamp(){
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  char timeStamp[20];
  strftime(timeStamp,99,"%Y%m%d%H%M%S",p);
  return timeStamp;
}


