/*=============================================================================
#       FileName :          DmpCalL0Psd.cc
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
#include "DmpEvtPsd.hh"     // include DmpDcdRunMode.hh

void DmpCalL0Manager::ConstructorPsd(){
  fEvtPsd   = new DmpEvtPsdRaw((DmpEvtVHeader*)fEvtHeader);
}

void DmpCalL0Manager::DestructorPsd(){
  delete fEvtPsd;
}


