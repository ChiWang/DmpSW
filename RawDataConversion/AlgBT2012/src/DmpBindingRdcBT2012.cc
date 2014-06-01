/*
 *  $Id: DmpBindingRdcBT2012.cc, 2014-05-28 10:38:43 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcAlgBT2012.h"


BOOST_PYTHON_MODULE(libDmpRdcBT2012){
  using namespace boost::python;

  // default algorithm
  class_<DmpRdcAlgBT2012,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgBT2012",init<>());
}


