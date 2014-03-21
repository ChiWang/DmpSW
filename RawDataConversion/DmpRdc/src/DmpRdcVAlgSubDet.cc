/*
 *  $Id: DmpRdcVAlgSubDet.cc, 2014-03-21 00:07:10 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpRdcVAlgSubDet.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"


DmpRdcVAlgSubDet::DmpRdcVAlgSubDet()
 :fRunMe(false),
  fHits(0)
{
}

//-------------------------------------------------------------------
DmpRdcVAlgSubDet::~DmpRdcVAlgSubDet(){
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::SetupConnector(){
  /*
   *  Set connector fConnector
   *
   *    1. should include "DmpRdcConnectorInterface.h"
   *    2. if (connector path == "default") return true, else: set fRunMe = true, then setup connector
   *
   */
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcVAlgSubDet::Convert(){
  if(not fRunMe) return true;
#ifdef DmpDebug
static bool noFrom=true;
if(noFrom){
  std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\tfrom "<<fFile->tellg();
  noFrom = false;
}
#endif
//-------------------------------------------------------------------
// set Convertion method here

//-------------------------------------------------------------------
#ifdef DmpDebug
std::cout<<" to "<<fFile->tellg()<<std::endl;
noFrom = true;
#endif
  return true;
}

