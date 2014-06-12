/*
 *  $Id: DmpEvtBgoShower.h, 2014-06-11 21:56:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtBgoShower_H
#define DmpEvtBgoShower_H

#include "TObject.h"

class DmpEvtBgoShower : public TObject{
/*
 *  DmpEvtBgoShower
 *
 *
*/

 public:
  DmpEvtBgoShower();
  ~DmpEvtBgoShower();
  void  Reset();
  void  PrintEvent() const;

 private:

  ClassDef(DmpEvtBgoShower,1)

};

#endif

