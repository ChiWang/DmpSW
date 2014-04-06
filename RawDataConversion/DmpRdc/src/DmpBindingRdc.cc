/*
 *  $Id: DmpBindingRdc.cc, 2014-03-14 11:16:57 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcDataManager.h"
#include "DmpRdcCnctPath.h"
#include "DmpRdcEntrance.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcDataManager
  class_<DmpRdcDataManager,boost::noncopyable,bases<DmpVIOSvc> >("DmpRdcDataManager",no_init)
    .def("GetInstance",&DmpRdcDataManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
  ;

  // DmpRdcCnctPath
  class_<DmpRdcCnctPath,boost::noncopyable>("DmpRdcCnctPath",no_init)
    .def("GetInstance",&DmpRdcCnctPath::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("SetConnectorPath",&DmpRdcCnctPath::SetConnectorPath)
  ;

  // DmpRdcEntrance
  def("Initialize", DmpCore::RdcInitialize);
  def("Execute",    DmpCore::RdcExecute);
  def("Clear",      DmpCore::RdcClear);
}


