/*
 *  $Id: DmpBindingRdc.cc, 2014-04-26 22:37:05 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcEntrance.h"
// default service of Rdc
#include "DmpRdcSvcLog.h"
#include "DmpRdcSvcDataMgr.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;

  // DmpRdcSvcLog
  class_<DmpRdcSvcLog,boost::noncopyable,bases<DmpVSvc> >("DmpRdcSvcLog",init<>());
  // DmpRdcSvcDataMgr
  class_<DmpRdcSvcDataMgr,boost::noncopyable,bases<DmpVSvc> >("DmpRdcSvcDataMgr",init<>());
  // DmpRdcEntrance
  def("Execute",    DmpCore::RdcExecute);

}


