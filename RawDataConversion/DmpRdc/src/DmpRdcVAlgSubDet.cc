/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-03-21 00:07:10 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpRdcVAlgSubDet.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"


DmpRdcVAlgSubDet::DmpRdcVAlgSubDet(const std::string &name)
 :DmpRdcVAlg(name),
  fRunMe(false),
  fHitCollection(0)
{
}

//-------------------------------------------------------------------
DmpRdcVAlgSubDet::~DmpRdcVAlgSubDet(){
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::ProcessThisEvent(){
  if(not fRunMe) return true;
  std::cout<<"\t"<<__PRETTY_FUNCTION__;
  StatusLog(0);
//-------------------------------------------------------------------
// set ProcessThisEvention method here

//-------------------------------------------------------------------
  StatusLog(1);
  return true;
}

