/*
 *  $Id: DmpRdcCnctPath.h, 2014-04-07 20:51:13 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcCnctPath_H
#define DmpRdcCnctPath_H

#include <string>

#include "DmpDetectorID.h"

class DmpRdcCnctPath{
public:
  static DmpRdcCnctPath*  GetInstance(){
    static DmpRdcCnctPath  instance;
    return &instance;
  }
  ~DmpRdcCnctPath(){}
  void SetConnectorPath(DmpDetector::DmpEDetectorID id,const std::string &p) {fConnectorPath[id] = p;}
  std::string GetConnectorPath(DmpDetector::DmpEDetectorID id) const {return fConnectorPath[id];}

private:
  DmpRdcCnctPath(){
    for(short i=0;i<DmpDetector::gSubDetNo;++i){
      fConnectorPath[i]="default";
    }
  }

private:
  std::string    fConnectorPath[DmpDetector::gSubDetNo];

};

//-------------------------------------------------------------------
extern DmpRdcCnctPath     *gCnctPathMgr;

#endif

