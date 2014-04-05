/*
 *  $Id: DmpCalAlgBgoPed.h, 2014-04-04 21:27:08 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/04/2014
*/

#ifndef DmpCalAlgBgoPed_H
#define DmpCalAlgBgoPed_H

#include "DmpVAlgorithm.h"

class DmpCalAlgBgoPed : public DmpVAlgorithm{
public:
  DmpCalAlgBgoPed(const std::string&);
  ~DmpCalAlgBgoPed();
  bool Initialize();
  bool Finialize();
  bool ProcessThisEvent();  // get entry and fill

};

#endif


