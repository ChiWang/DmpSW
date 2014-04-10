/*
 *  $Id: DmpVOption.h, 2014-04-08 12:35:26 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/04/2014
*/

#ifndef DmpVOption_H
#define DmpVOption_H

#include <string>

#include "DmpDetectorID.h"

class DmpVOption{
/*
 * DmpVOption
 *
 *  control some job options in run time through this class
 *
 */
public:
  DmpVOption(){}
  virtual ~DmpVOption(){}

  virtual void Set(const std::string&,DmpDetector::DmpEDetectorID, const std::string&)=0;
  virtual std::string Get(const std::string&)=0;

};

#endif


