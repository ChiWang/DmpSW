/*=============================================================================
#       FileName :          DmpEvtAbsSubDetSubDet.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   22:01:24
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-04   09:08:49
=============================================================================*/

#include <iostream>

#include "DmpEvtAbsSubDet.hh"

ClassImp(DmpEvtAbsSubDet)

//______________________________________________________________________________
DmpEvtHeader* DmpEvtAbsSubDet::fHeader=0;

//______________________________________________________________________________
DmpEvtAbsSubDet::DmpEvtAbsSubDet()
 :fMode(kMixed)
{}


//______________________________________________________________________________
DmpEvtAbsSubDet::~DmpEvtAbsSubDet()
{}

DmpEvtHeader* DmpEvtAbsSubDet::GetEventHeader(){
  if(fHeader){
    std::cout<<"Error:  DmpEvtAbsSubDet::GetEventHeader(). Not set event header. Please use DmpEvtSubDet::SetEventHeader(DmpEvtHeader*) firstly"<<std::endl;
  }
  return fHeader;
}
