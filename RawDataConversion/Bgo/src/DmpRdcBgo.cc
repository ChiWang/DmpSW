/*
 *  $Id: DmpRdcBgo.cc, 2014-03-10 01:28:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

/*
 *  NOTE:
 *
 *  bool DmpRdcAlgorithm::SetConnectorBgo(), update fConnectorBgo, will use cnct files in fConnectorPath
 *
 *  bool DmpRdcAlgorithm::ConvertEventBgo(), Process one event of this subDet, will use fConnectorBgo, and fInputData. Then update DmpRdcDataManager::fEvtRaw::fBgoHits
 *
 */

#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpRdcAlgorithm.h"
#include "DmpRdcAlgorithmBgo.h"

//-------------------------------------------------------------------
bool DmpRdcAlgorithm::SetConnectorBgo(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl; 
#endif
  bool done = false;
  if(gPhase == DmpCore::Phase::kQuarter){
    done = DmpAlgBgoRdc::Quarter::SetConnector();
  }else if(gPhase == DmpCore::Phase::kPrototype){
    done = DmpAlgBgoRdc::Prototype::SetConnector();
  }else{
    done = DmpAlgBgoRdc::Product::SetConnector();
  }
  return done;
}

//-------------------------------------------------------------------
bool DmpRdcAlgorithm::ConvertEventBgo(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl; 
#endif
  bool done = false;
  if(gPhase == DmpCore::Phase::kQuarter){
    done = DmpAlgBgo::Quarter::ConvertOneEvent();
  }else if(gPhase == DmpCore::Phase::kPrototype){
    done = DmpAlgBgo::Prototype::ConvertOneEvent();
  }else{
    done = DmpAlgBgo::Product::ConvertOneEvent();
  }
  return done;
}


