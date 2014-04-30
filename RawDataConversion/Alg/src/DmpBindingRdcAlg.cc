/*
 *  $Id: DmpBindingRdcAlg.cc, 2014-04-27 10:09:52 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

// default algorithm of Rdc
#include "DmpRdcAlgHeader.h"
#include "DmpRdcAlgBgo.h"
//#include "DmpRdcAlgPsd.h"

BOOST_PYTHON_MODULE(libDmpRdcAlg){
  using namespace boost::python;

  class_<DmpRdcAlgHeader,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgHeader",init<>());
  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<>());
  //class_<DmpRdcAlgPsd,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgPsd",init<>());

}


