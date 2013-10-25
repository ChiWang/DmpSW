/*=============================================================================
#       FileName :          DmpCalL0Stk.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-18   15:07:46
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-18   15:53:34
=============================================================================*/

#include <iostream>

#include "DmpCalL0Manager.hh"
#include "DmpEvtStk.hh"     // include DmpDcdRunMode.hh

void DmpCalL0Manager::ConstructorStk(){
  fEvtStk   = new DmpEvtStkRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpCalL0Manager::DestructorStk(){
  delete fEvtStk;
}


