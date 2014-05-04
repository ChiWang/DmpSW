/*
 *  $Id: DmpBindingRdcSvc.cc, 2014-04-27 10:12:46 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

// *
// *  TODO: delete Entrance
// *
#include "DmpRdcEntrance.h"
// default service of Rdc
#include "DmpRdcSvcDataMgr.h"

BOOST_PYTHON_MODULE(libDmpRdcSvc){
  using namespace boost::python;

  // DmpRdcEntrance
  def("Execute",    DmpEntrance::RdcExecute);

  // DmpRdcSvcDataMgr
  class_<DmpRdcSvcDataMgr,boost::noncopyable,bases<DmpVSvc> >("DmpRdcSvcDataMgr",init<>());

}


