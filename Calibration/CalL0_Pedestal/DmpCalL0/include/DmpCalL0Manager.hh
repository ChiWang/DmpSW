/*=============================================================================
#       FileName :          DmpCalL0Manager.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-18   14:36:14
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-23   01:10:50
=============================================================================*/

#ifndef DmpCalL0Manager_H
#define DmpCalL0Manager_H

#include <map>
#include <vector>

#include "DmpVManager.hh"

class RooDataSet;
class RooRealVar;
class DmpEvtHeaderRaw;
class DmpEvtPsdRaw;
class DmpEvtStkRaw;
class DmpEvtBgoRaw;
class DmpEvtNudRaw;

class DmpCalL0Manager : public DmpVManager{

//  ---------------->   manager general
 public:
  static DmpCalL0Manager* GetInstance();    // get Manager
  void Clear();                             // delete Manager
  Bool_t BookBranch();
  void   SavePedestal(TString subDet);

 private:
  DmpCalL0Manager();
  ~DmpCalL0Manager();

 private:
  static DmpCalL0Manager*    fInstance;

//  ---------------->   manager special
 public:
  void FindPedetsalEevent(TString subDet);
  template <typename TDmpEvt>               // Why could not find this function if we implment it in src/*.cc?
  TDmpEvt*  GetEvent(TString subDet) {
  if (subDet == "Header") {
    return (TDmpEvt*)fEvtHeader;
  } else if (subDet == "Psd") {
    return (TDmpEvt*)fEvtPsd;
  } else if (subDet == "Stk") {
    return (TDmpEvt*)fEvtStk;
  } else if (subDet == "Bgo") {
    return (TDmpEvt*)fEvtBgo;
  } else if (subDet == "Nud") {
    return (TDmpEvt*)fEvtNud;
  } else {
    return 0;
  }
}

//  ---------------->   sub-detector
  // Header
 private:
  DmpEvtHeaderRaw   *fEvtHeader;
  // Psd
 private:
  void ConstructorPsd();
  void DestructorPsd();
  DmpEvtPsdRaw      *fEvtPsd;
  // Stk
 private:
  void ConstructorStk();
  void DestructorStk();
  DmpEvtStkRaw      *fEvtStk;
  // Bgo
 private:
  void ConstructorBgo();
  void DestructorBgo();
  void BookMapBgo();
  TString GetMapNameBgo(Short_t planeID,Short_t quadrantID,Short_t barID);
  void  FindPedetsalEeventBgo();
  void  UpdateHitOrder();        // return 4 dimentions array
  void  SavePedestalBgo();

  DmpEvtBgoRaw                  *fEvtBgo;   //! interface to input root file
  RooRealVar                    *fDy2;      //! 3 RooRealVar are used in RooDataSet
  RooRealVar                    *fDy5;
  RooRealVar                    *fDy8;
  std::map<TString,RooDataSet*> *fMapBgo;   //! fMapBgo[GetMapNameBgo(p,q,b)]
  
  Short_t                   ****fHitOrder;  //! Hit order from max to min.  fHitOrder[Bgo::kPlaneNb][Bgo::kSideNb*2][Bgo::kDyNb][Bgo::kBarNum+Bgo::kRefBarNb]
  // Nud
 private:
  void ConstructorNud();
  void DestructorNud();
  DmpEvtNudRaw      *fEvtNud;

};

#endif


