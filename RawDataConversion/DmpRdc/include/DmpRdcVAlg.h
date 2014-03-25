/*
 *  $Id: DmpRdcVAlg.h, 2014-03-25 19:00:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlg_H
#define DmpRdcVAlg_H

#include <fstream>
#include "DmpVAlgorithm.h"

class DmpEvtHeader;

class DmpRdcVAlg : public DmpVAlgorithm{
public:
  DmpRdcVAlg(const std::string&);
  virtual ~DmpRdcVAlg();
  static void  SetFileStream(std::ifstream *p)   {sFile = p;}

protected:
  void StatusLog(short)const;

private:
  void PrintLocation()const;

protected:
  static std::ifstream  *sFile;     // pointer of file stream (update it evry input data)
  static DmpEvtHeader   *sHeader;   // to print time, set run mode

};

#endif


