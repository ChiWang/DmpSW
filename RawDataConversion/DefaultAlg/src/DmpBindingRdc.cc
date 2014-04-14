/*
 *  $Id: DmpBindingRdc.cc, 2014-04-10 11:01:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

// default service of Rdc
#include "DmpRdcSvcOption.h"
//#include "DmpRdcSvcLog.h"
#include "DmpRdcEntrance.h"
// default algorithm of Rdc
#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcSvcOption
  class_<DmpRdcSvcOption,boost::noncopyable,bases<DmpVOptionSvc> >("DmpRdcSvcOption",init<>());

  // DmpRdcEntrance
  def("Execute",    DmpCore::RdcExecute);

  // default algorithm
  class_<DmpRdcAlgHeader,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgHeader",init<std::string>());
  class_<DmpRdcAlgPsd,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgPsd",init<std::string>());
  class_<DmpRdcAlgStk,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgStk",init<std::string>());
  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<std::string>());
  class_<DmpRdcAlgNud,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgNud",init<std::string>());
}


