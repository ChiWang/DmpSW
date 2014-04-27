/*
 *  $Id: DmpBindingRdcAlg.cc, 2014-04-27 10:09:52 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

// default algorithm of Rdc
#include "DmpRdcAlgBgo.h"

BOOST_PYTHON_MODULE(libDmpRdcAlg){
  using namespace boost::python;

  class_<DmpRdcAlgBgo,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBgo",init<>());

}


