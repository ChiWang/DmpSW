/*
 *  $Id: DmpRdcDataManager.h, 2014-03-09 20:12:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <fstream>
#include "DmpVDataManager.h"

class DmpEventRaw;

class DmpRdcDataManager : public DmpVDataManager{
/*
 *  DmpRdcDataManager
 *
 *
*/
public:
  static DmpRdcDataManager* GetInstance(){
    static DmpRdcDataManager instance;
    return &instance;
  }
  ~DmpRdcDataManager();
  std::ifstream     *gInFile;   // in file pointer. update it for every binary data
  void Initialize();
  void BookBranch();
  void FillEvent();

private:
  DmpRdcDataManager();

public:
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}

private:
  DmpEventRaw   *fEvtRaw;

};

#endif

