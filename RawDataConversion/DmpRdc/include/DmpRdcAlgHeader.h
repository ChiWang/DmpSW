/*
 *  $Id: DmpRdcAlgHeader.h, 2014-03-20 23:41:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include "DmpRdcVAlg.h"

class DmpRdcAlgHeader : public DmpRdcVAlg{
public:
  DmpRdcAlgHeader();
  ~DmpRdcAlgHeader();
  bool  Convert();
  short GetTrigger() const {return fTrigger;}

private:
  short     fTrigger;   // trigger in event header

};

#endif

