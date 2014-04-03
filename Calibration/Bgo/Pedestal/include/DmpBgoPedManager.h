/*
 *  $Id: DmpBgoPedManager.h, 2014-04-03 16:12:16 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/04/2014
*/

/*=====================================================================
 *   File:   DmpBgoPedManager.h
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    18/10/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   14:38:40
=====================================================================*/

#ifndef DmpBgoPedManager_H
#define DmpBgoPedManager_H

#include <map>

#include "DmpVManager.h"

class TTree;
class RooRealVar;
class RooDataSet;
class DmpEvtBgoRaw;
class DmpRecordBgoPed;

class DmpBgoPedManager : public DmpVManager{

//------------------------------------------------------------------------------
 public:
  static DmpBgoPedManager* GetInstance();
  static void Clear();
  Bool_t Core();
  DmpVEvtSubDet*  GetEventPointer(TString det) const {return 0;}

 private:
  DmpBgoPedManager();
  ~DmpBgoPedManager();
  void SetupPMTCollection();
  void SetupPMTCollection_BT2012();
  void SetupPMTCollection_CT2013(){return true;}
  void SetupPMTCollection_Final(){return true;}

 private:
  static DmpBgoPedManager  *fInstance;   //singleton
  TTree     *fTree;
  
  DmpEvtBgoRaw      *fEvt;
  DmpRecordBgoPed   *fRecord;
  RooRealVar        *fDy2ADC;       // Adc of Dy2
  RooRealVar        *fDy5ADC;
  RooRealVar        *fDy8ADC;
  std::map<Int_t, RooDataSet*>  fPMTCollection;

};

#endif


