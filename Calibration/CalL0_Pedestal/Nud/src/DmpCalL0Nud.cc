/*=============================================================================
#       FileName :          DmpCalL0Nud.cc
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
#                                          Update:  2013-10-21   22:21:11
=============================================================================*/

#include <iostream>

#include "DmpCalL0Manager.hh"
#include "DmpEvtNud.hh"     // include DmpDcdRunMode.hh

void DmpCalL0Manager::ConstructorNud(){
  fEvtNud   = new DmpEvtNudRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpCalL0Manager::DestructorNud(){
  delete fEvtNud;
}


