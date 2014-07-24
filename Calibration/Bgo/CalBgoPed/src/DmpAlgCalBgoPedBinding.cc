#include <boost/python.hpp>
#include "DmpAlgCalBgoPed.h"

BOOST_PYTHON_MODULE(libDmpAlgCalBgoPed){
  using namespace boost::python;

  class_<DmpAlgCalBgoPed,boost::noncopyable,bases<DmpVAlg> >("DmpAlgCalBgoPed",init<>());
}

