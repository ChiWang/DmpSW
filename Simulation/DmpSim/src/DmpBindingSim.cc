/*
 *  $Id: DmpBindingSim.cc, 2014-03-15 15:27:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimDataManager.h"
#include "DmpSimDetectorInterface.h"
#include "DmpSimEntrance.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;
  // DmpSimDataManager
  class_<DmpSimDataManager,boost::noncopyable,bases<DmpVDataManager> >("DmpSimDataManager",no_init)
    .def("GetInstance",&DmpSimDataManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("SetOutDataName",&DmpSimDataManager::SetOutDataName)
  ;

  // DmpSimDetectorInterface
  class_<DmpSimDetectorInterface,boost::noncopyable>("DmpSimDetectorInterface",no_init)
    .def("GetInstance",&DmpSimDetectorInterface::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("SetGdmlPath",&DmpSimDetectorInterface::SetGdmlPath)
    .def("SetOffset",&DmpSimDetectorInterface::SetOffset)
  ;

  // DmpSimEntrance
  def("Initialize",     DmpCore::SimInitialize);
  def("Execute",        DmpCore::SimExecute);
  def("Clear",          DmpCore::SimClear);

}


