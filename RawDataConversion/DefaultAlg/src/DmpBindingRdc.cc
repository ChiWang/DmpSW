/*
 *  $Id: DmpBindingRdc.cc, 2014-04-18 14:33:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

// default service of Rdc
#include "DmpRdcSvcLog.h"
#include "DmpRdcSvcDataMgr.h"
// default algorithm of Rdc
#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"

#include "DmpRdcEntrance.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcSvcLog
  class_<DmpRdcSvcLog,boost::noncopyable,bases<DmpVSvc> >("DmpRdcSvcLog",init<>());
  // DmpRdcSvcDataMgr
  class_<DmpRdcSvcDataMgr,boost::noncopyable,bases<DmpVSvc> >("DmpRdcSvcDataMgr",init<>());
  // default algorithm
  class_<DmpRdcAlgHeader,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgHeader",init<std::string>());
  class_<DmpRdcAlgPsd,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgPsd",init<>());
  class_<DmpRdcAlgStk,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgStk",init<>());
  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<>());
  class_<DmpRdcAlgNud,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgNud",init<>());
  // DmpRdcEntrance
  def("Execute",    DmpCore::RdcExecute);

}


