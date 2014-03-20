/*
 *  $Id: DmpEntranceSimulation.h, 2014-03-08 19:38:27 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceSimulation_H
#define DmpEntranceSimulation_H

#include <string>

namespace DmpCore{
  void SimInitialize();     // set physics list, detector, user actions and visualization.
  void SimExecute(const std::string&);        // run a macro file and save result into root file
  void SimClear();
}

#endif
