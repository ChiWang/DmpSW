/*
 *  $Id: DmpBindingSim.cc, 2014-04-08 13:44:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimOption.h"
#include "DmpSimEntrance.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;

  // DmpSimOption
  class_<DmpSimOption,boost::noncopyable,bases<DmpVOption> >("DmpSimOption",no_init)
    .def("GetInstance",&DmpSimOption::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
  ;

  // DmpSimEntrance
  def("Initialize",     DmpCore::SimInitialize);
  def("Execute",        DmpCore::SimExecute);
  def("Clear",          DmpCore::SimClear);

}


