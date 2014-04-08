/*
 *  $Id: DmpRdcLog.h, 2014-04-08 14:47:51 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#ifndef DmpRdcLog_H
#define DmpRdcLog_H

#include "DmpVLog.h"

class DmpRdcLog : public DmpVLog{
public:
  static DmpRdcLog*  GetInstance(){
    static DmpRdcLog instance;
    return &instance;
  }
  ~DmpRdcLog(){}
  void StatusLog(const short &n=0) const;

private:
  DmpRdcLog(){}

public:
  void PrintLocation() const;

};

//-------------------------------------------------------------------
extern DmpRdcLog *gRdcLog;

#endif

