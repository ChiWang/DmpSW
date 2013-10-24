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

class TH1F;
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
  void FillPedestal(TString subDet);
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
  DmpEvtHeaderRaw*  fEvtHeader;
  // Psd
 private:
  DmpEvtPsdRaw*     fEvtPsd;
  // Stk
 private:
  DmpEvtStkRaw*     fEvtStk;
  // Bgo
 private:
  void BookHistBgo();
  TString GetHistNameBgo(Short_t planeID,Short_t quadrantID,Short_t barID,Short_t dyID);
  //TH1F* GetHist(Short_t p,Short_t quadrant,Short_t b,Short_t dy);
  void  FillPedestalBgo();
  void  UpdateHitOrder();        // return 4 dimentions array
  void  SavePedestalBgo();

  DmpEvtBgoRaw*             fEvtBgo;
  std::map<TString, Int_t>  fName2IDBgo;    //! key: HistName,  value:   hist ID
  std::vector<TH1F*>        *fHistBgo;      //! (*fHistBgo)[fName2IDBgo[GetHistNameBgo(p,q,b,dy)]]
  Short_t                   ****fHitOrder;  //! Hit order from max to min.  fHitOrder[Bgo::kPlaneNb][Bgo::kSideNb*2][Bgo::kDyNb][Bgo::kBarNum+Bgo::kRefBarNb]
  // Nud
 private:
  DmpEvtNudRaw*     fEvtNud;

};

#endif

