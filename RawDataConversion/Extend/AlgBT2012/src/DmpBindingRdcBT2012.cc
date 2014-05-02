/*
 *  $Id: DmpBindingRdcBT2012.cc, 2014-05-02 12:22:02 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcAlgBgo.h"
#include "DmpRdcAlgNud.h"


BOOST_PYTHON_MODULE(libDmpRdcBT2012){
  using namespace boost::python;

  // default algorithm
  class_<DmpRdcAlgHeader,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgHeader",init<>());
  class_<DmpRdcAlgPsd,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgPsd",init<>());
  class_<DmpRdcAlgStk,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgStk",init<>());
  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<>());
  class_<DmpRdcAlgNud,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgNud",init<>());
}


