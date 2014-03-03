/*
 *  $Id: DmpEvtBgoShower.h, 2014-03-02 23:15:09 chi $
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

