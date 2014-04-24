/*
 *  $Id: DmpEvtRdcBgoMSD.h, 2014-04-24 10:23:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcBgoMSD_H
#define DmpEvtRdcBgoMSD_H

#include "TObject.h"

class DmpEvtRdcBgoMSD : public TObject{
/*
*  DmpEvtRdcBgoMSD
*
*      this class is used to save output of Rdc of Bgo
*
*/
public:
  DmpEvtRdcBgoMSD();
  ~DmpEvtRdcBgoMSD();
  int   GetSDID() const {return fSDID;}
  void  SetSDID(const int &id) {fSDID = id;}
  void  SetSignal(const int &value,const short &sideID,const short &dyID); 
  int   GetSignal(const short &sideID,const short &dyID);

private:
  int   fSDID;          // unique sensitive detector(minimum detector unit) ID. For Bgo, fSDID =  layerID*100 + barID. layerID = {0~13}, barID = {0~21}
  
  std::vector<short>    fDyID;      // fDyID = sideID*10 + dynodeID
  std::vector<int>      fDyValue;   // dynode signal (ADC)

  ClassDef(DmpEvtRdcBgoMSD,1)

};

#endif

