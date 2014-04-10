/*
 *  $Id: DmpSimOption.h, 2014-04-08 13:19:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

#ifndef DmpSimOption_H
#define DmpSimOption_H

#include "DmpVOption.h"

class DmpSimOption : public DmpVOption{
/*
 *  DmpSimOption
 *
 */
public:
  static DmpSimOption*  GetInstance(){
    static DmpSimOption instance;
    return &instance;
  }
  ~DmpSimOption();
  void Set(const std::string&,DmpDetector::DmpEDetectorID,const std::string&);
  std::string Get(const std::string&){}

private:
  DmpSimOption();

public:
  std::string GetGdmlPath(DmpDetector::DmpEDetectorID id) const {return fGdmlPath[id];}
  float GetOffset(DmpDetector::DmpEDetectorID id) const {return fOffset[id];}

private:
  std::string    fGdmlPath[DmpDetector::gSubDetNo + 1];
  float fOffset[DmpDetector::gSubDetNo];        // sudDet center --> Sat center

};

//-------------------------------------------------------------------
extern DmpSimOption *gSimOpt;

#endif


