/*
 *  $Id: DmpBindingSimulation.cc, 2014-03-07 15:52:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpEntranceSimulation.h"

BOOST_PYTHON_MODULE(libDmpSimulation){
  using namespace boost::python;
  using namespace DmpCore;

  def("SetInDataPath",SimulationSetInDataPath);
  def("SetOutDataPath",SimulationSetOutDataPath);
  def("GetOutDataPath",SimulationGetOutDataPath);
  def("Initialize",SimulationInitialize);
  def("SetOutDataName",SimulationSetOutDataName);
  def("Execute",SimulationExecute);
  def("Clear",SimulationClear);
}

