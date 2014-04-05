/*
 *  $Id: DmpCalBgoDataManager.cc, 2014-04-04 21:28:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#include "DmpCalBgoDataManager.h"

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


