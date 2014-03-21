/*
 *  $Id: DmpRdcVAlg.h, 2014-03-20 23:59:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlg_H
#define DmpRdcVAlg_H

#include <fstream>

class DmpEvtHeader;

class DmpRdcVAlg{
public:
  DmpRdcVAlg();
  virtual ~DmpRdcVAlg();
  virtual bool Convert()=0;         // convert one event
  static void  SetFileStream(std::ifstream *p)   {fFile = p;}

protected:
  void StatusLog(short)const;

private:
  void PrintLocation()const;

protected:
  static std::ifstream  *fFile;     // pointer of file stream (update it evry input data)
  static DmpEvtHeader   *fHeader;   // to print time, set run mode

};

#endif


