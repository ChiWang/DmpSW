/*
 *  $Id: DmpDetectorPsd.cc, 2014-03-16 16:02:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/03/2014
*/

#include <boost/python.hpp>

#include "DmpDetectorPsd.h"
#include "DmpBindingCore.h"

using namespace DmpDetector;

//-------------------------------------------------------------------
Psd::DmpEPsdPhase Psd::gPhase = Psd::kProduct;

//-------------------------------------------------------------------
void DmpBindingEntrance::Core::Psd(){
  using namespace boost::python;

  enum_<Psd::DmpEPsdPhase>("DmpEPsdPhase")
    .value("kQuarter",  Psd::kQuarter)
    .value("kPrototype",Psd::kPrototype)
    .value("kProduct",  Psd::kProduct)
  ;
  scope().attr("gPhasePsd")=Psd::gPhase;
}


