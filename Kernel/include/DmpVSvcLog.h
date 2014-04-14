/*
 *  $Id: DmpVLog.h, 2014-04-12 16:29:36 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 08/04/2014
*/

#ifndef DmpVLog_H
#define DmpVLog_H

#include "DmpVSvc.h"

class DmpVLog : public DmpVSvc{
/*
 *  DmpVLog
 *
 *  all log class derived from here
 *
 */
public:
  DmpVLog():fLevel(0){}
  virtual ~DmpVLog(){}
  virtual void StatusLog(const short&) const=0;

protected:
  void SetLevel(const short &i){
    fLevel = i;
  }

private:
  short fLevel;

};

#endif

