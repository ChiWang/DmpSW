/*
 *  $Id: DmpCalBgoDataManager.cc, 2014-04-04 21:28:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#include "DmpCalBgoDataManager.h"

//-------------------------------------------------------------------
bool DmpCalBgoDataManager::InputData(const std::string &n){
  fInDataName = n;
  //gInDataTree = ;
}

//-------------------------------------------------------------------
void DmpCalBgoDataManager::Initialize(){
}

//-------------------------------------------------------------------
void DmpCalBgoDataManager::BookBranch(){

}

//-------------------------------------------------------------------
DmpCalBgoDataManager::~DmpCalBgoDataManager(){
  delete fMetaData;
}

//-------------------------------------------------------------------
DmpCalBgoDataManager::DmpCalBgoDataManager()
 :gInDataTree(0)
{
  fMetaData = new DmpCalBgoMetaData();
}

//-------------------------------------------------------------------
DmpCalBgoDataManager*  gDataMgr = DmpCalBgoDataManager::GetInstance();


