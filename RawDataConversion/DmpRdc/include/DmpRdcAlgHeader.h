/*
 *  $Id: DmpRdcAlgHeader.h, 2014-04-08 15:29:53 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include "DmpVAlg.h"

class DmpEvtHeader;

class DmpRdcAlgHeader : public DmpVAlg{
public:
  DmpRdcAlgHeader(const std::string&);
  ~DmpRdcAlgHeader(){}
  bool  Initialize() {return true;}
  bool  Finialize()  {return true;}
  bool  ProcessThisEvent();

private:
  DmpEvtHeader      *fEvtHeader;
};

#endif

