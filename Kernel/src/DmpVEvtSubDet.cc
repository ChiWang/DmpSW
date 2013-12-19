/*=====================================================================
 *   File:   DmpVEvtSubDet.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:10:18
=====================================================================*/

#include <iostream>

#include "DmpVEvtSubDet.hh"

ClassImp(DmpVEvtSubDet)

//------------------------------------------------------------------------------
DmpEvtHeader* DmpVEvtSubDet::fHeader=0;

//------------------------------------------------------------------------------
DmpVEvtSubDet::DmpVEvtSubDet()
 :fMode(kMixed)
{}

//------------------------------------------------------------------------------
DmpVEvtSubDet::~DmpVEvtSubDet()
{}

//------------------------------------------------------------------------------
DmpEvtHeader* DmpVEvtSubDet::GetEventHeader(){
  if(!fHeader){
    std::cerr<<"Error:  DmpVEvtSubDet::GetEventHeader(). Not set event header. Please use DmpEvt::SetEventHeader(DmpEvtHeader*) firstly"<<std::endl;
  }
  return fHeader;
}


