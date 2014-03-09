/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-08 20:06:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

//#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

DmpRdcDataManager *dataManager = 0;

//-------------------------------------------------------------------
bool DmpCore::RdcInitialize(){
  if (not DmpRdcManager::SetConnectorPsd()) return false;
  if (not DmpRdcManager::SetConnectorStk()) return false;
  if (not DmpRdcManager::SetConnectorBgo()) return false;
  if (not DmpRdcManager::SetConnectorNud()) return false;
  dataManager = DmpRdcDataManager::GetInstance();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetInDataPath(std::string p){
  dataManager->SetInDataPath(p);
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  dataManager->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  dataManager->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  dataManager->SetOutDataName();
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  if(not dataManager->OpenInputData(dataName))  return;
  dataManager->BookBranch();
  dataManager->CreateOutDataName();
  dataManager->Convert();
// *
// *  TODO:   for the next raw data, what's in fOutDataTree before next BookBranch() ??
// *
  dataManager->SaveOutput();
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  DmpRdcDataManager::Vanish();
}

