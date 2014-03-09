/*
 *  $Id: DmpRdcDataManager.h, 2014-03-09 20:12:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include "DmpVDataManager.h"

class DmpEventRaw;

class DmpRdcDataManager : public DmpVDataManager{
/*
 *  DmpRdcDataManager
 *
 *
*/
public:
  static DmpRdcDataManager*     GetInstance();
  static void Vanish();
  void BookBranch();
  void CreateOutDataName(std::string);

private:
  DmpRdcDataManager();
  ~DmpRdcDataManager();
  static DmpRdcDataManager  *sInstance;

public:
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}

private:
  DmpEventRaw   *fEvtRaw;

};

#endif

