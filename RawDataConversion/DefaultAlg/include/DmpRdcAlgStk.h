/*
 *  $Id: DmpRdcAlgStk.h, 2014-03-19 18:40:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgStk_H
#define DmpRdcAlgStk_H

#include "DmpRdcVAlgSubDet.h"

class DmpRdcAlgStk : public DmpRdcVAlgSubDet{
public:
  DmpRdcAlgStk(const std::string&);
  ~DmpRdcAlgStk();
  bool Initialize();
  bool ProcessThisEvent();           // convert one event

private:
  bool SetupConnector();
  void AppendThisSignal(const int&,const float&);

};

#endif


