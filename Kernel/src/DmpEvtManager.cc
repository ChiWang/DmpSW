/*=============================================================================
#       FileName :          DmpEvtManager.cc
#       Version  :          0.0.1
#       Author   :          Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-12-12   16:50:00
#------------------------------------------------------------------------------
#       Description  :
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-12-12   16:50:00
=============================================================================*/

#include "TString.h"

#include "DmpEvtManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpEvtSubDet.hh"

ClassImp(DmpEvtManager)

//------------------------------------------------------------------------------
DmpEvtManager::DmpEvtManager(){
  fHeader = new DmpEvtHeader();
  DmpEvtSubDet::SetEventHeader(fHeader);
}

//------------------------------------------------------------------------------
DmpEvtManager::~DmpEvtManager(){
  delete fHeader;
}

//------------------------------------------------------------------------------
DmpEvtSubDet*  DmpEvtManager::GetEventPointer(TString subDet){
  return 0;
}

