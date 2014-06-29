#include <boost/python.hpp>
#include "DmpAlgBgoRdcEQM.h"

BOOST_PYTHON_MODULE(libDmpAlgBgoRdcEQM){
  using namespace boost::python;

  class_<DmpAlgBgoRdcEQM,boost::noncopyable,bases<DmpVAlg> >("DmpAlgBgoRdcEQM",init<>());
}

