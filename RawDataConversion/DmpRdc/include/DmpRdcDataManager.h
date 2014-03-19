/*
 *  $Id: DmpRdcDataManager.h, 2014-03-09 20:12:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include "DmpVOutDataManager.h"

class DmpEventRaw;

class DmpRdcDataManager : public DmpVOutDataManager{
/*
 *  DmpRdcDataManager
 *
 *
*/
public:
  static DmpRdcDataManager*     GetInstance();
  void BookBranch();
  void SetOutDataName(std::string);

private:
  DmpRdcDataManager();
  ~DmpRdcDataManager();

public:
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}

private:
  DmpEventRaw   *fEvtRaw;

};

#endif

