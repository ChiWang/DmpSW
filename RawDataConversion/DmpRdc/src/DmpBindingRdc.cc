/*
 *  $Id: DmpBindingRdc.cc, 2014-03-07 16:05:04 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>
#include "DmpEntranceRdc.h"

BOOST_PYTHON_MODULE(libDmpRawDataConversion){
  using namespace boost::python;

  def("RawDataConversion",DmpCore::EntranceRawDataConversion);
}
