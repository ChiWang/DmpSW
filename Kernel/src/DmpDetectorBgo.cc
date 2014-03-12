/*
 *  $Id: DmpDetectorBgo.cc, 2014-03-12 11:56:24 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/03/2014
*/

#include "DmpDetectorBgo.h"

using namespace DmpDetector;

//-------------------------------------------------------------------
Bgo::DmpEBgoPhase Bgo::gPhase = Bgo::kProduct;

void Bgo::SetPhase(Bgo::DmpEBgoPhase p){
  Bgo::gPhase = p;
}

Bgo::DmpEBgoPhase Bgo::GetPhase(){
  return Bgo::gPhase;
}


#include <boost/python.hpp>
#include "DmpBindingCore.h"
//-------------------------------------------------------------------
void DmpBindingEntrance::Core::Bgo(){
  using namespace boost::python;

  enum_<Bgo::DmpEBgoPhase>("DmpEBgoPhase")
    .value("kQuarter",  Bgo::kQuarter)
    .value("kPrototype",Bgo::kPrototype)
    .value("kProduct",  Bgo::kProduct)
  ;
  def("SetBgoPhase",Bgo::SetPhase);
  def("GetBgoPhase",Bgo::GetPhase);
}


