/*
 *  $Id: DmpBindingSim.cc, 2014-05-15 00:21:01 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimAlgRunManager.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;

  // DmpSimAlgRunManager
  class_<DmpSimAlgRunManager,boost::noncopyable,bases<DmpVAlg> >("DmpSimAlgRunManager",init<>());

}


