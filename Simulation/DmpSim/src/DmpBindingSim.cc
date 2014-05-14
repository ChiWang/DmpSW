/*
 *  $Id: DmpBindingSim.cc, 2014-05-15 00:21:01 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimSvcBoot.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpSimEntrance.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;

  // DmpSimSvcBoot
  class_<DmpSimSvcBoot,boost::noncopyable,bases<DmpVSvc> >("DmpSimSvcBoot",init<>());
  // DmpSimSvcDataMgr
  class_<DmpSimSvcDataMgr,boost::noncopyable,bases<DmpVSvc> >("DmpSimSvcDataMgr",init<>());
  // DmpSimEntrance
  def("Execute",        DmpEntrance::SimExecute);

}


