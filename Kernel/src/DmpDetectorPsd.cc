/*
 *  $Id: DmpDetectorPsd.cc, 2014-03-12 11:29:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/03/2014
*/

#include "DmpDetectorPsd.h"

using namespace DmpDetector;

//-------------------------------------------------------------------
Psd::DmpEPsdPhase Psd::gPhase = Psd::kProduct;

void Psd::SetPhase(Psd::DmpEPsdPhase p){
  Psd::gPhase = p;
}

Psd::DmpEPsdPhase Psd::GetPhase(){
  return Psd::gPhase;
}


#include <boost/python.hpp>
#include "DmpBindingCore.h"
//-------------------------------------------------------------------
void DmpBindingEntrance::Core::Psd(){
  using namespace boost::python;

  enum_<Psd::DmpEPsdPhase>("DmpEPsdPhase")
    .value("kQuarter",  Psd::kQuarter)
    .value("kPrototype",Psd::kPrototype)
    .value("kProduct",  Psd::kProduct)
  ;
  def("SetPsdPhase",Psd::SetPhase);
  def("GetPsdPhase",Psd::GetPhase);
}


