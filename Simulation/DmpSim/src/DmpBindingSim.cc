/*
 *  $Id: DmpBindingSim.cc, 2014-03-12 14:57:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpSimEntrance.h"

BOOST_PYTHON_MODULE(libDmpSim){
  using namespace boost::python;

  // DmpSimEntrance
  def("SetGdmlPath",    DmpCore::SimSetGdmlPath);
  def("GetGdmlPath",    DmpCore::SimGetGdmlPath);
  def("SetOutDataPath", DmpCore::SimSetOutDataPath);
  def("GetOutDataPath", DmpCore::SimGetOutDataPath);
  def("SetOutDataName", DmpCore::SimSetOutDataName);
  def("Initialize",     DmpCore::SimInitialize);
  def("Execute",        DmpCore::SimExecute);
  def("Clear",          DmpCore::SimClear);

}

