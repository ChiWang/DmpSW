/*
 *  $Id: DmpBindingCore.cc, 2014-03-08 21:57:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpCore.h"
#include "DmpVDataManager.h"

BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;
  using namespace DmpCore::Phase;
  using namespace DmpCore::RunMode;
  enum_<DmpPhase>("DmpEPhase")
    .value("kQuarter",kQuarter)
    .value("kPrototype",kPrototype)
    .value("kProduct",kProduct)
  ;
  enum_<DmpRunMode>("DmpERunMode")
    .value("kUnknow",kUnknow)
    .value("kCompress",kCompress)
    .value("kCalPed",kCalPed)
    .value("kCalADC",kCalADC)
  ;

  using namespace DmpParameter::Detector;
  enum_<DmpDetectorID>("DmpEDetectorID")
    .value("kWhole",kWhole)
    .value("kPsd",kPsd)
    .value("kStk",kStk)
    .value("kBgo",kBgo)
    .value("kNud",kNud)
  ;

  class_<DmpVDataManager,boost::noncopyable>("PhaseManager",no_init)
    .def("SetPhase",&DmpVDataManager::SetPhase)
    .staticmethod("SetPhase")
    .def("GetPhase",&DmpVDataManager::GetPhase)
    .staticmethod("GetPhase")
  ;
}


