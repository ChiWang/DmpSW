/*
 *  $Id: DmpRdcAlgPsd.h, 2014-03-21 00:15:46 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgPsd_H
#define DmpRdcAlgPsd_H

#include "DmpRdcVAlgSubDet.h"

class DmpRdcAlgPsd : public DmpRdcVAlgSubDet{
public:
  DmpRdcAlgPsd();
  ~DmpRdcAlgPsd();
  bool SetupConnector();
  bool Convert();           // convert one event

};

#endif


