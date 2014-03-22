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
  static DmpRdcDataManager* GetInstance();
  ~DmpRdcDataManager();
  void Initialize();
  void BookBranch();
  bool TriggerMatch(const short&);  // set match level(with Bgo) 1: Psd; 2(or 3): Psd, Stk; 4: Psd, Stk, Nud

private:
  DmpRdcDataManager();

public:
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}

private:
  DmpEventRaw   *fEvtRaw;

};

#endif

