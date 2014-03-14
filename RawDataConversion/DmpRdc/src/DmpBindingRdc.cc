/*
 *  $Id: DmpBindingRdc.cc, 2014-03-14 11:16:57 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>
#include "DmpRdcEntrance.h"

BOOST_PYTHON_MODULE(libDmpRdc){
  using namespace boost::python;
  using namespace DmpCore;

  def("SetConnectorNud",RdcSetConnector);

  def("SetOutDataPath",RdcSetOutDataPath);
  def("GetOutDataPath",RdcGetOutDataPath);
  def("SetOutDataName",RdcSetOutDataName);
  def("Initialize",RdcInitialize);
  def("Execute",RdcExecute);
  def("Clear",RdcClear);
}


