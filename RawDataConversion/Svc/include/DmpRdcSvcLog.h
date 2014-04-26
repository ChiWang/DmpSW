/*
 *  $Id: DmpRdcSvcLog.h, 2014-04-10 21:26:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#ifndef DmpRdcSvcLog_H
#define DmpRdcSvcLog_H

#include <fstream>

#include "DmpVLog.h"
#include "DmpVSvc.h"

class DmpEvtHeader;

class DmpRdcSvcLog : public DmpVSvc, public DmpVLog{
/*
 *  DmpRdcSvcLog
 *
 *  for DmpRdcAlg*, error log
 *
 */
public:
  DmpRdcSvcLog();
  ~DmpRdcSvcLog();
  bool Initialize();
  bool Finalize()   {return true;}
  void Set(const std::string &type,const std::string &argv);
  void Type(const short &n=0) const;

private:
  void PrintLocation() const;

private:
  std::ifstream     *fFile;
  DmpEvtHeader      *fEvtHeader;

};

#endif


