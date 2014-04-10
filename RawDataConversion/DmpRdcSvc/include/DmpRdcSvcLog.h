/*
 *  $Id: DmpRdcSvcLog.h, 2014-04-10 21:26:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#ifndef DmpRdcLog_H
#define DmpRdcLog_H

#include "DmpVLogSvc.h"

class DmpRdcLog : public DmpVLogSvc{
public:
  static DmpRdcLog*  GetInstance(){
    static DmpRdcLog instance;
    return &instance;
  }
  ~DmpRdcLog(){}
  void StatusLog(const short &n=0) const;

private:
  DmpRdcLog():DmpVLogSvc("DmpRdcLog"){}

public:
  void PrintLocation() const;

};

//-------------------------------------------------------------------
extern DmpRdcLog *gRdcLog;

#endif

