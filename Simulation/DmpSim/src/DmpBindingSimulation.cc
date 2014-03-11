/*
 *  $Id: DmpBindingSimulation.cc, 2014-03-07 15:52:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpEntranceSimulation.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;
  using namespace DmpCore;

  def("SetOutDataPath",SimSetOutDataPath);
  def("GetOutDataPath",SimGetOutDataPath);
  def("SetOutDataName",SimSetOutDataName);
  def("Initialize",SimInitialize);
  def("Execute",SimExecute);
  def("Clear",SimClear);
}

