/*
 *  $Id: DmpVAlgorithm.cc, 2014-03-25 12:50:03 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/03/2014
*/

#include "DmpVAlgorithm.h"
#include "DmpServiceManager.h"

DmpVService* DmpVAlgorithm::Service(const std::string &name)const {
  return (DmpServiceManager::GetInstance()->GetService(name)); 
}


