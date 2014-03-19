/*
 *  $Id: DmpRdcAlgHeader.h, 2014-03-19 12:46:42 chi $
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
  void  SetFileStream(ifstream *p)   {fFile = p;}
  short GetTrigger() const {return fTrigger;}

private:
  DmpEvtHeader  *fEvtHeader;
  ifstream      *fFile;     // pointer of file stream
  short     fTrigger;   // trigger in event header

};

#endif

