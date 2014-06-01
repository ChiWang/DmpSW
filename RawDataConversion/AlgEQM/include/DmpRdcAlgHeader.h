/*
 *  $Id: DmpRdcAlgHeader.h, 2014-04-28 16:16:47 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include <fstream>

#include "DmpVAlg.h"

class DmpEvtRdcHeader;

class DmpRdcAlgHeader : public DmpVAlg{
/*
 *  DmpRdcAlgHeader
 *
 *  This is the default algorithm of DmpRdcHeader.
 *
 */
public:
  DmpRdcAlgHeader();
  virtual ~DmpRdcAlgHeader(){}
  bool Initialize();
  bool Finalize() {return true;}
  virtual bool ProcessThisEvent();

protected:
  std::ifstream     *fFile;             // in data stream, for all Alg. of subDet

protected:
  DmpEvtRdcHeader   *fEvtHeader;        //

};

#endif

