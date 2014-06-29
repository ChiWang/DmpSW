/*
 *  $Id: DmpBindingRdcAlg.cc, 2014-05-28 20:58:25 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRdcAlgEQM.h"

BOOST_PYTHON_MODULE(libDmpRdcAlg){
  using namespace boost::python;

  class_<DmpRdcAlgEQM,boost::noncopyable,bases<DmpVAlg> >("DmpRdcAlgEQM",init<>());

}


