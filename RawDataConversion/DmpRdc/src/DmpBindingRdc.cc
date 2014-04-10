/*
 *  $Id: DmpBindingRdc.cc, 2014-04-10 11:01:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcOption.h"
#include "DmpRdcEntrance.h"
// default algorithm of Rdc
#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcOption
  class_<DmpRdcOption,boost::noncopyable,bases<DmpVOption> >("DmpRdcOption",no_init)
    .def("GetInstance",&DmpRdcOption::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
  ;

  // DmpRdcEntrance
  def("Execute",    DmpCore::RdcExecute);

  // default algorithm
  class_<DmpRdcAlgHeader,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgHeader",init<std::string>());
  class_<DmpRdcAlgPsd,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgPsd",init<std::string>());
  class_<DmpRdcAlgStk,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgStk",init<std::string>());
  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<std::string>());
  class_<DmpRdcAlgNud,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgNud",init<std::string>());
}


