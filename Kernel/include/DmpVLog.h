/*
 *  $Id: DmpVLog.h, 2014-04-08 06:44:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 08/04/2014
*/

#ifndef DmpVLog_H
#define DmpVLog_H

class DmpVLog{
/*
 *  DmpVLog
 *
 *  all log class derived from here
 *
 */
public:
  DmpVLog(){}
  virtual ~DmpVLog(){}
  virtual void StatusLog(const short&) const=0;

};

#endif

