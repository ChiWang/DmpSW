/*
 *  $Id: DmpEntranceSimulation.h, 2014-03-08 10:26:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceSimulation_H
#define DmpEntranceSimulation_H

#include <string>

namespace DmpCore{
  void SimulationInitialize();
  void SimulationExecute(std::string);      // simulation main
  void SimulationClear();
}

#endif
