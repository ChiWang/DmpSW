/*
 *  $Id: DmpSimPsdOpt.cc, 2014-04-14 13:23:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 14/04/2014
*/

#include <boost/lexical_cast.hpp>

#include "DmpSimSvcBoot.h"
#include "DmpSimDetector.h"

void DmpSimSvcBoot::SetPsd(const std::string &type,const std::string &argv){
  if(type == "Gdml"){
    fDetector->SetGdml(DmpDetector::kPsd,argv);
  }else if(type == "Offset"){
    float v = boost::lexical_cast<float>(argv);
    fDetector->SetOffset(DmpDetector::kPsd,v);
  }
}

