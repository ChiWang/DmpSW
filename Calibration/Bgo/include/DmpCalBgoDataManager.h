/*
 *  $Id: DmpCalBgoDataManager.h, 2014-04-04 21:19:51 chi $
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
  void Initialize();
  void BookBranch();
  virtual bool SetInData(const std::string);

private:
  DmpCalBgoDataManager();

public:
  TTree         *gInDataTree;   // in data
  DmpCalBgoMetaData* GetMetaData()const{return fMetaData;}

private:
  DmpCalBgoMetaData     *fMetaData;      // MetaData of Calibration

};

//-------------------------------------------------------------------
extern DmpCalBgoDataManager *gDataMgr;

#endif


