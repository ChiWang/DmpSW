/*
 *  $Id: DmpBindingCore.cc, 2014-03-11 19:43:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpCore.h"
#include "DmpDetectorPsd.h"
#include "DmpDetectorStk.h"
#include "DmpDetectorBgo.h"
#include "DmpDetectorNud.h"

//-------------------------------------------------------------------
/*
void DmpDetector::Psd::SetPhase(DmpEPsdPhase p){
  DmpDetector::Psd::gPhase = p;
}
DmpEPsdPhase DmpDetector::Psd::GetPhase(){
  return DmpDetector::Psd::gPhase;
}
*/

// *
// *  TODO: add Stk
// *
//-------------------------------------------------------------------
/*
void DmpDetector::Stk::SetPhase(DmpEStkPhase p){
  DmpDetector::Stk::gPhase = p;
}
DmpEStkPhase DmpDetector::Stk::GetPhase(){
  return DmpDetector::Stk::gPhase;
}
*/

//-------------------------------------------------------------------
//DmpDetector::Bgo::gPhase = DmpDetector::Bgo::kProduct;
/*
void DmpDetector::Bgo::SetPhase(DmpEBgoPhase p){
  DmpDetector::Bgo::gPhase = p;
}
DmpEBgoPhase DmpDetector::Bgo::GetPhase(){
  return DmpDetector::Bgo::gPhase;
}
*/

// *
// *  TODO: add Nud
// *
//-------------------------------------------------------------------
/*
DmpDetector::Nud::gPhase = DmpDetector::Nud::kProduct;
void DmpDetector::Nud::SetPhase(DmpENudPhase p){
  DmpDetector::Nud::gPhase = p;
}
DmpENudPhase DmpDetector::Nud::GetPhase(){
  return DmpDetector::Nud::gPhase;
}
*/

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;

  // DmpCore
  enum_<DmpEPhase>("DmpEPhase")
    .value("kQuarter",  DmpCore::kQuarter)
    .value("kPrototype",DmpCore::kPrototype)
    .value("kProduct",  DmpCore::kProduct)
  ;

  enum_<DmpERunMode>("DmpERunMode")
    .value("kUnknow",   DmpCore::kUnknow)
    .value("kCompress", DmpCore::kCompress)
    .value("kCalPed",   DmpCore::kCalPed)
    .value("kCalADC",   DmpCore::kCalADC)
  ;

  enum_<DmpEDetectorID>("DmpEDetectorID")
    .value("kPsd",  DmpCore::kPsd)
    .value("kStk",  DmpCore::kStk)
    .value("kBgo",  DmpCore::kBgo)
    .value("kNud",  DmpCore::kNud)
    .value("kWhole",DmpCore::kWhole)
  ;

  // DmpDetectorPsd
  enum_<DmpEPsdPhase>("DmpEPsdPhase")
    .value("kQuarter",  DmpDetector::Psd::kQuarter)
    .value("kPrototype",DmpDetector::Psd::kPrototype)
    .value("kProduct",  DmpDetector::Psd::kProduct)
  ;
  /*
  def("SetPsdPhase",DmpDetector::Psd::SetPhase);
  def("GetPsdPhase",DmpDetector::Psd::GetPhase);
  */

  // DmpDetectorStk
  /*
// *
// *  TODO:  add Stk
// *
  */

  // DmpDetectorBgo
  enum_<DmpEBgoPhase>("DmpEBgoPhase")
    .value("kQuarter",  DmpDetector::Bgo::kQuarter)
    .value("kPrototype",DmpDetector::Bgo::kPrototype)
    .value("kProduct",  DmpDetector::Bgo::kProduct)
  ;
  def("SetBgoPhase",DmpDetector::Bgo::SetPhase);
  /*
  def("GetBgoPhase",DmpDetector::Bgo::GetPhase);
  */

  // DmpDetectorNud
  /*
// *
// *  TODO:  add Nud
// *
  */

}


