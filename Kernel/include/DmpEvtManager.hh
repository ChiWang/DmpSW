/*=============================================================================
#       FileName :          DmpEvtManager.hh
#       Version  :          0.0.1
#       Author   :          Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-12-12   14:38:32
#------------------------------------------------------------------------------
#       Description  :
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-12-12   14:38:32
=============================================================================*/

#ifndef DmpEvtManager_H
#define DmpEvtManager_H

#include "TObject.h"

class DmpEvtHeader;
class DmpEvtSubDet;

class DmpEvtManager : virtual public TObject{
/*
 *  DmpEvtManager
 *
 *  only defined fHeader, and attach the fHeader to DmpEvtSubDet::SetHeader();
 *
 *  So, any class inherit from this class, must declare and define fPsd, fStk, fBgo, fNud in it own constructor.
 *
 *
*/
 public:
  DmpEvtManager();
  virtual ~DmpEvtManager();
  virtual DmpEvtSubDet*  GetEventPointer(TString);

 protected:
  DmpEvtHeader  *fHeader;

  ClassDef(DmpEvtManager,0)

};

#endif

