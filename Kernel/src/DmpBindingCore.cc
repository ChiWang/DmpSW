/*
 *  $Id: DmpBindingCore.cc, 2014-03-07 15:52:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>
#include "DmpVDataManager.h"

BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;

  class_<DmpVDataManager,boost::noncopyable>("PathManager",no_init)
    .def("SetInDataPath",&DmpVDataManager::SetInDataPath)
    .staticmethod("SetInDataPath")
    .def("SetOutDataPath",&DmpVDataManager::SetOutDataPath)
    .staticmethod("SetOutDataPath")
    ;
}
