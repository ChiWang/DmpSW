/*
 *  $Id: DmpBindingSim.cc, 2014-06-10 15:00:21 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimAlg.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;

  // DmpSimAlg
  class_<DmpSimAlg,boost::noncopyable,bases<DmpVAlg> >("DmpSimAlg",init<>());

}


