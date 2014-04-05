/*
 *  $Id: DmpCalBgoDataManager.h, 2014-04-05 12:34:00 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#ifndef DmpCalBgoDataManager_H
#define DmpCalBgoDataManager_H

#include "DmpVDataManager.h"

class DmpCalBgoMetaData;

class DmpCalBgoDataManager : public DmpVDataManager{
public:
  static DmpCalBgoDataManager* GetInstance(){
    static DmpCalBgoDataManager instance;
    return &instance;
  }
  ~DmpCalBgoDataManager();
  bool InputData(const std::string&);
  void Initialize();
  void BookBranch();

private:
  DmpCalBgoDataManager();

public:
  TTree         *gInDataTree;   // in data
  DmpCalBgoMetaData* GetMetaData() const {return fMetaData;}

private:
  DmpCalBgoMetaData     *fMetaData;      // MetaData of Calibration

};

//-------------------------------------------------------------------
extern DmpCalBgoDataManager *gDataMgr;

#endif


