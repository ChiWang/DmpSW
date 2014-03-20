/*
 *  $Id: DmpRdcAlgHeader.h, 2014-03-19 18:41:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcAlgHeader_H
#define DmpRdcAlgHeader_H

#include <fstream>

class DmpEvtHeader;

class DmpRdcAlgHeader{
public:
  DmpRdcAlgHeader();
  virtual ~DmpRdcAlgHeader();
  virtual bool Convert();
  void  SetFileStream(std::ifstream *p)     {fFile = p;}
  short GetTrigger() const {return fTrigger;}

private:
  DmpEvtHeader  *fHeader;
  std::ifstream      *fFile;     // pointer of file stream
  short     fTrigger;   // trigger in event header

};

#endif

