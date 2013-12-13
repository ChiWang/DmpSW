/*=====================================================================
 *   File:   DmpEvtSubDet.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:10:18
=====================================================================*/

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
    std::cerr<<"Error:  DmpEvtSubDet::GetEventHeader(). Not set event header. Please use DmpEvt::SetEventHeader(DmpEvtHeader*) firstly"<<std::endl;
  }
  return fHeader;
}


