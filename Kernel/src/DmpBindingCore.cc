/*
 *  $Id: DmpBindingCore.cc, 2014-03-08 10:22:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpCore.h"
#include "DmpVDataManager.h"

BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;
  using namespace DmpCore;
  enum_<DmpPhase>("DmpPhase")
    .value("kBT2012",kBT2012)
    .value("kCT2013",kCT2013)
    .value("kFinal",kFinal)
  ;

  class_<DmpVDataManager,boost::noncopyable>("PhaseManager",no_init)
    .def("SetPhase",&DmpVDataManager::SetPhase)
    .staticmethod("SetPhase")
    .def("GetPhase",&DmpVDataManager::GetPhase)
    .staticmethod("GetPhase")
  ;
}
