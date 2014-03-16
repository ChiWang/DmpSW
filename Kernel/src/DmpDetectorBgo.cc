/*
 *  $Id: DmpDetectorBgo.cc, 2014-03-16 15:59:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/03/2014
*/

#include <boost/python.hpp>

#include "DmpDetectorBgo.h"
#include "DmpBindingCore.h"

using namespace DmpDetector;

//-------------------------------------------------------------------
Bgo::DmpEBgoPhase Bgo::gPhase = Bgo::kProduct;

//-------------------------------------------------------------------
void DmpBindingEntrance::Core::Bgo(){
  using namespace boost::python;

  enum_<Bgo::DmpEBgoPhase>("DmpEBgoPhase")
    .value("kQuarter",  Bgo::kQuarter)
    .value("kPrototype",Bgo::kPrototype)
    .value("kProduct",  Bgo::kProduct)
  ;
  scope().attr("gPhaseBgo")=Bgo::gPhase;
}


