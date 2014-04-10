/*
 *  $Id: DmpRdcSvcLog.h, 2014-04-10 21:26:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#ifndef DmpRdcSvcLog_H
#define DmpRdcSvcLog_H

#include "DmpVLogSvc.h"

class DmpRdcSvcLog : public DmpVLogSvc{
public:
  static DmpRdcSvcLog*  GetInstance(){
    static DmpRdcSvcLog instance;
    return &instance;
  }
  ~DmpRdcSvcLog(){}
  void StatusLog(const short &n=0) const;

private:
  DmpRdcSvcLog():DmpVLogSvc("DmpRdcSvcLog"){}

public:
  void PrintLocation() const;

};

//-------------------------------------------------------------------
extern DmpRdcSvcLog *gRdcLog;

#endif

