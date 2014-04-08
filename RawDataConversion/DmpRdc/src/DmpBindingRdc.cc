/*
 *  $Id: DmpBindingRdc.cc, 2014-03-14 11:16:57 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcDataManager.h"
#include "DmpRdcOption.h"
#include "DmpRdcEntrance.h"
// default algorithm of Rdc
/*#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"*/

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcDataManager
  class_<DmpRdcDataManager,boost::noncopyable,bases<DmpVIO> >("DmpRdcDataManager",no_init)
    .def("GetInstance",&DmpRdcDataManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
  ;

  // DmpRdcOption
  class_<DmpRdcOption,boost::noncopyable,bases<DmpVOption> >("DmpRdcOption",no_init)
    .def("GetInstance",&DmpRdcOption::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
  ;

  // default algorithm
    /*
  class_<DmpRdcAlgHeader,boost::noncopyable>("DmpRdcAlgHeader");
  class_<DmpRdcAlgPsd,boost::noncopyable>("DmpRdcAlgPsd");
  class_<DmpRdcAlgStk,boost::noncopyable>("DmpRdcAlgStk");
  class_<DmpRdcAlgBgo,boost::noncopyable>("DmpRdcAlgBgo");
  class_<DmpRdcAlgNud,boost::noncopyable>("DmpRdcAlgNud");
*/
  // DmpRdcEntrance
  def("Initialize", DmpCore::RdcInitialize);
  def("Execute",    DmpCore::RdcExecute);
}


