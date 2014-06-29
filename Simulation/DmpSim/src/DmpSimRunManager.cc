/*
 *  $Id: DmpSimRunManager.cc, 2014-06-10 15:02:09 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#include "DmpSimRunManager.h"

//-------------------------------------------------------------------
DmpSimRunManager::DmpSimRunManager()
{
}

//-------------------------------------------------------------------
DmpSimRunManager::~DmpSimRunManager(){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
}

//-------------------------------------------------------------------
bool DmpSimRunManager::SimOneEvent(const int &id){
  ProcessOneEvent(id);
  TerminateOneEvent();
  if(runAborted){
    return false;
  }
  return true;
}


