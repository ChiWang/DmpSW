/*
 *  $Id: DmpRdcAlgHeader.h, 2014-04-16 17:20:15 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include <fstream>

#include "DmpVAlg.h"

class DmpRdcSvcLog;
class DmpEvtHeader;

class DmpRdcAlgHeader : public DmpVAlg{
/*
 *  DmpRdcAlgHeader
 *
 *  This is the default algorithm of DmpRdcHeader.
 *
 *
 */
public:
  DmpRdcAlgHeader(const std::string&);
  virtual ~DmpRdcAlgHeader(){}
  virtual bool Initialize();
  virtual bool ProcessThisEvent();
  virtual bool Finalize() {return true;}

protected:
  std::ifstream     *fFile;
  DmpRdcSvcLog      *fLog;

protected:
  DmpEvtHeader      *fEvtHeader;

};

#endif

