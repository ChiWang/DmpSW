/*
 *  $Id: DmpSimDetectorInterface.h, 2014-03-17 17:12:00 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

/*
 * split static variables  into this class
 *
 */

#ifndef DmpSimDetectorInterface_H
#define DmpSimDetectorInterface_H

#include <string>

#include "DmpCore.h"

class DmpSimDetectorInterface{
public:
  static DmpSimDetectorInterface*  GetInstance();
  ~DmpSimDetectorInterface();
  void SetGdmlPath(DmpCore::DmpEDetectorID id,const std::string &p) {fGdmlPath[id] = p;}
  void SetOffset(DmpCore::DmpEDetectorID id,const float &off)       {fOffset[id]=off;}
  std::string GetGdmlPath(DmpCore::DmpEDetectorID id) const         {return fGdmlPath[id];}
  float GetOffset(DmpCore::DmpEDetectorID id) const                 {return fOffset[id];}

private:
  DmpSimDetectorInterface();

private:
  std::string    fGdmlPath[DmpCore::gSubDetNo + 1];
  float fOffset[DmpCore::gSubDetNo];        // sudDet center --> Sat center

};

#endif


