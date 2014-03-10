/*
 *  $Id: DmpEntranceRdcAlgorithm.cc, 2014-03-10 01:35:54 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

//#include <iostream>

#include "DmpRdcAlgorithm.h"
#include "DmpEntranceRdc.h"

using namespace DmpRdcAlg;

void DmpCore::RdcSetConnectorPsd(std::string path){
   Psd::SetConnector(path);
}

void DmpCore::RdcSetConnectorStk(std::string path){
   Stk::SetConnector(path);
}

void DmpCore::RdcSetConnectorBgo(std::string path){
   Bgo::SetConnector(path);
}

void DmpCore::RdcSetConnectorNud(std::string path){
   Nud::SetConnector(path);
}

