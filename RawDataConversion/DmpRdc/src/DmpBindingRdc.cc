/*
 *  $Id: DmpBindingRdc.cc, 2014-03-08 19:56:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>
#include "DmpEntranceRdc.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;
  using namespace DmpCore;

  def("SetInDataPath",RdcSetInDataPath);
  def("SetOutDataPath",RdcSetOutDataPath);
  def("GetOutDataPath",RdcGetOutDataPath);
  def("Initialize",RdcInitialize);
  def("SetOutDataName",RdcSetOutDataName);
  def("Execute",RdcExecute);
  def("Clear",RdcClear);
}


