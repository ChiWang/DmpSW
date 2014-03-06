/*
 *  $Id: DmpVDataManager.h, 2014-03-06 21:45:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataManager_H
#define DmpVDataManager_H

#include <string>

class DmpEventRaw;

class DmpVDataManager{
/*
 *  DmpVDataManager
 *
 *  All DataManager class inherite from this class
*/
 public:
  DmpVDataManager();
  virtual ~DmpVDataManager();

  void  SetInDataPath(std::string);
  void  SetOutDataPath(std::string);
  void  SetDataName(std::string name)   {fDataName = name;}
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}

protected:
  std::string   fInDataPath;
  std::string   fOutDataPath;
  std::string   fDataName;
  DmpEventRaw   *fEvtRaw;
};

#endif

