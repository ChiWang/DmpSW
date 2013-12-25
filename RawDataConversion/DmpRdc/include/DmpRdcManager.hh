/*=====================================================================
 *   File:   DmpRdcManager.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   15:20:26
=====================================================================*/

#ifndef DmpRdcManager_H
#define DmpRdcManager_H

#include <map>
#include <fstream>      // Conversion(ifstream* HexData)

#include "DmpVManager.hh"

class DmpEvtPsdRaw;
class DmpEvtStkRaw;
class DmpEvtBgoRaw;
class DmpEvtNudRaw;

class DmpRdcManager : public DmpVManager{
/*
 *  DmpRdcManager
 *
 *  SetConnectorSub-DetX() and ConversionSub-DetX()    could have many versions, for cosmic; whole; Beam test 2012..
 *  
 *
*/

//------------------------------------------------------------------------------
 public:
  static DmpRdcManager*    GetInstance();
  static void   Clear();
  Bool_t Core();
  DmpVEvtSubDet*  GetEventPointer(TString det) const {return 0;}
  void  SetHexData(ifstream *p)  {fHexData = p;}

 private:
  DmpRdcManager();
  ~DmpRdcManager();
  Bool_t    TriggerMatch();

 private:
  static DmpRdcManager  *fInstance;         // singleton
  static TString        fConnectorPath;     // connection files of FEE to Detector
  ifstream  *fHexData;                      // hex data
  std::map<TString,Short_t> fTrigger;       // 5 key: {Header|Psd|Stk|Bgo|Nud}

//------------------------------------------------------------------------------
 public:
  Bool_t    SetConnectorPsd();
  Bool_t    SetConnectorStk();
  Bool_t    SetConnectorBgo(){return true;}
  Bool_t    SetConnectorBgo_BT2012();
  Bool_t    SetConnectorBgo_CT2013(){return true;}
  Bool_t    SetConnectorNud();

  Bool_t    ConversionHeader();
  Bool_t    ConversionPsd();
  Bool_t    ConversionStk();
  Bool_t    ConversionBgo(){return true;}
  Bool_t    ConversionBgo_BT2012();
  Bool_t    ConversionBgo_CT2013(){return true;}
  Bool_t    ConversionNud();

 private:
  DmpEvtPsdRaw  *fPsd;
  DmpEvtStkRaw  *fStk;
  DmpEvtBgoRaw  *fBgo;
  DmpEvtNudRaw  *fNud;
  std::map<Int_t, Int_t>  ConnectorPsd;
  std::map<Int_t, Int_t>  ConnectorStk;
  std::map<Int_t, Int_t>  ConnectorBgo;     // FEE 2 Detector
    //ConnectorBgo[FEEID*1000+ChannelID][LBSD_ID]
    //LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  std::map<Int_t, Int_t>  ConnectorNud;

  ClassDef(DmpRdcManager,0)

};

#endif

