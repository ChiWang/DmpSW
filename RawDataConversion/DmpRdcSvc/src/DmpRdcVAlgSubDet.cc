/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-04-06 20:13:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "DmpRdcVAlgSubDet.h"
#include "DmpRdcLog.h"

//-------------------------------------------------------------------
DmpRdcVAlgSubDet::DmpRdcVAlgSubDet(const std::string &n)
 :DmpVAlg(n),
  fRunMe(false),
  fMSDSet(0)
{
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::ProcessThisEvent(){
  if(not fRunMe) return true;
  //std::cout<<"\t"<<__PRETTY_FUNCTION__;
  gRdcLog->StatusLog(0);
//-------------------------------------------------------------------
// set ProcessThisEvention method here
//-------------------------------------------------------------------
  gRdcLog->StatusLog(1);
  return true;
}

