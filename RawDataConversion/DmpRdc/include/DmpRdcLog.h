/*
 *  $Id: DmpRdcLog.h, 2014-04-02 10:57:15 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#ifndef DmpRdcLog_H
#define DmpRdcLog_H

#include "DmpVService.h"

class DmpRdcLog : public DmpVService{
public:
  static DmpRdcLog*  GetInstance(){
    static DmpRdcLog instance("RdcLog");
    return &instance;
  }
  ~DmpRdcLog(){}

private:
  DmpRdcLog(const std::string &n):DmpVService(n){}

public:
  void StatusLog(const short &n=0) const;
  void PrintLocation() const;

};

//-------------------------------------------------------------------
extern DmpRdcLog *gRdcLog;

#endif

