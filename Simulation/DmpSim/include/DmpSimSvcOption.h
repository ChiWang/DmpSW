/*
 *  $Id: DmpSimSvcOption.h, 2014-04-10 21:09:30 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

#ifndef DmpSimSvcOption_H
#define DmpSimSvcOption_H

#include "DmpVOptionSvc.h"

class DmpSimSvcOption : public DmpVOptionSvc{
/*
 *  DmpSimSvcOption
 *
 */
public:
  static DmpSimSvcOption*  GetInstance(){
    static DmpSimSvcOption instance;
    return &instance;
  }
  ~DmpSimSvcOption();
  void Set(const std::string&,DmpDetector::DmpEDetectorID,const std::string&);
  std::string Get(const std::string&){}

private:
  DmpSimSvcOption();

public:
  std::string GetGdmlPath(DmpDetector::DmpEDetectorID id) const {return fGdmlPath[id];}
  float GetOffset(DmpDetector::DmpEDetectorID id) const {return fOffset[id];}

private:
  std::string    fGdmlPath[DmpDetector::gSubDetNo + 1];
  float fOffset[DmpDetector::gSubDetNo];        // sudDet center --> Sat center

};

//-------------------------------------------------------------------
extern DmpSimSvcOption *gSimOpt;

#endif


