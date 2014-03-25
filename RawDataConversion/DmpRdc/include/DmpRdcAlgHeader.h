/*
 *  $Id: DmpRdcAlgHeader.h, 2014-03-25 19:02:48 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include "DmpRdcVAlg.h"

class DmpRdcAlgHeader : public DmpRdcVAlg{
public:
  DmpRdcAlgHeader(const std::string&);
  ~DmpRdcAlgHeader();
// *
// *  TODO: how to get sFile and sHeader in Initialize() if delete DmpRdcVAlg (using DmpServiceManager instead)
// *
  bool  Initialize(){}
  bool  Finialize(){}
  bool  ProcessThisEvent();

};

#endif

