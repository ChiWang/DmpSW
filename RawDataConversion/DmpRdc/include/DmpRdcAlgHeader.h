/*
 *  $Id: DmpRdcAlgHeader.h, 2014-04-02 13:11:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include "DmpVAlgorithm.h"

class DmpEvtHeader;

class DmpRdcAlgHeader : public DmpVAlgorithm{
public:
  DmpRdcAlgHeader(const std::string&);
  ~DmpRdcAlgHeader(){}
  bool  Initialize(){}
  bool  Finialize(){}
  bool  ProcessThisEvent();

private:
  DmpEvtHeader      *fEvtHeader;
};

#endif

