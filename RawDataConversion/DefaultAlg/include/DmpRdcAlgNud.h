/*
 *  $Id: DmpRdcAlgNud.h, 2014-03-21 00:15:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgNud_H
#define DmpRdcAlgNud_H

#include "DmpRdcVAlgSubDet.h"

class DmpRdcAlgNud : public DmpRdcVAlgSubDet{
public:
  DmpRdcAlgNud(const std::string&);
  ~DmpRdcAlgNud();
  bool Initialize();
  bool ProcessThisEvent();  // convert one event
  
private:
  void AppendThisSignal(const int&,const float&);

};

#endif


