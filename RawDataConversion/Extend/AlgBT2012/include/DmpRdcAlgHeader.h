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
 *  if, we re-write DmpEvtHeader, or
 *  want to write a new Alg. for Header, write a class and override ProcessThisEvent()
 *
 */
public:
  DmpRdcAlgHeader(const std::string&);
  virtual ~DmpRdcAlgHeader(){}
  bool Initialize();
  bool Finalize() {return true;}
  virtual bool ProcessThisEvent();

protected:
  std::ifstream     *fFile;             // in data stream, for all Alg. of subDet
  DmpRdcSvcLog      *fLog;              // log status, for all Alg. of subDet

protected:
  DmpEvtHeader      *fEvtHeader;        //

};

#endif

