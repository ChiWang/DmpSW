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


