/*
 *  $Id: DmpCalAlgBgoPed.h, 2014-04-03 16:30:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/04/2014
*/

#ifndef DmpCalAlgBgoPed_H
#define DmpCalAlgBgoPed_H

#include "DmpVAlgorithm.h"

class TClonesArray;

class DmpCalAlgBgoPed : public DmpVAlgorithm{
public:
  DmpCalAlgBgoPed(const std::string &n)
   :DmpVAlgorithm(n),
   fHitCollection(0){}
  ~DmpCalAlgBgoPed(){}
  bool Initialize();    // book file
  bool Finialize();     // save out constant data
  bool ProcessThisEvent();  // get entry and fill

private:
  TClonesArray  *fHitCollection;    // rawEvt

};

#endif


