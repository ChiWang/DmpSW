/*
 *  $Id: DmpEntranceRdc.h, 2014-03-08 15:07:36 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceRdc_H
#define DmpEntranceRdc_H

#include <string>
namespace DmpCore{
  void RawDataConversionInitialize();           // set connector
  void RawDataConversionExecute(std::string);   // run a raw data
  void RawDataConversionClear();
}

#endif
