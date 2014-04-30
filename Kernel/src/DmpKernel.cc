/*
 *  $Id: DmpKernel.cc, 2014-04-30 10:35:21 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include "DmpKernel.h"

//-------------------------------------------------------------------
DmpKernel::DmpKernel()
 :fAlgMgr(0),
  fSvcMgr(0),
  fLogLevel(6)
{
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
}

//-------------------------------------------------------------------
DmpKernel::~DmpKernel(){
}

//-------------------------------------------------------------------
bool DmpKernel::Initialize(){
  if(not fSvcMgr->Initialize()){
    return false;
  }
  if(not fAlgMgr->Initialize()){
    return false;
  }
}

//-------------------------------------------------------------------
bool DmpKernel::Run(){
// *
// *  TODO:  how to
// *

}

//-------------------------------------------------------------------
bool DmpKernel::Finalize(){
  if(not fSvcMgr->Finalize()){
    return false;
  }
  if(not fAlgMgr->Finalize()){
    return false;
  }
}

//-------------------------------------------------------------------
bool DmpKernel::OutErrorInfor() const {
  if((fLogLevel%8)/4 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpKernel::OutWarningInfor() const {
  if((fLogLevel%4)/2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpKernel::OutDebugInfor() const {
  if(fLogLevel%2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
DmpKernel *gKernel = DmpKernel::GetInstance();


