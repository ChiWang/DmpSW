/*=============================================================================
#       FileName :          DmpEvtSubDet.cc
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

#include "DmpEvtSubDet.hh"

ClassImp(DmpEvtSubDet)

//------------------------------------------------------------------------------
DmpEvtHeader* DmpEvtSubDet::fHeader=0;

//------------------------------------------------------------------------------
DmpEvtSubDet::DmpEvtSubDet()
 :fMode(kMixed)
{}

//------------------------------------------------------------------------------
DmpEvtSubDet::~DmpEvtSubDet()
{}

DmpEvtHeader* DmpEvtSubDet::GetEventHeader(){
  if(fHeader){
    std::cout<<"Error:  DmpEvtSubDet::GetEventHeader(). Not set event header. Please use DmpEvt::SetEventHeader(DmpEvtHeader*) firstly"<<std::endl;
  }
  return fHeader;
}


