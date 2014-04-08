/*
 *  $Id: DmpRdcAlgBgo.h, 2014-03-21 00:23:42 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgBgo_H
#define DmpRdcAlgBgo_H

#include "DmpRdcVAlgSubDet.h"

class DmpRdcAlgBgo : public DmpRdcVAlgSubDet{
public:
  //DmpRdcAlgBgo(){}
  DmpRdcAlgBgo(const std::string&);
  ~DmpRdcAlgBgo();
  bool Initialize();
  bool ProcessThisEvent();  // convert one event

private:
  void AppendThisSignal(const int&,const float&);

};

#endif


