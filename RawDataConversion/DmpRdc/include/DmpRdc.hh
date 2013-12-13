/*=============================================================================
#       FileName :          DmpRdc.hh
#       Version  :          0.0.1
#       Author   :          USTC    (ylzhang1@mail.ustc.edu.cn chiwang@mail.ustc.edu.cn zhzhy@mail.ustc.edu.cn)
#       Time     :          2013-08-03   09:21:56
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-21   13:20:44
=============================================================================*/

#ifndef DmpRdc_H
#define DmpRdc_H

#include <map>
#include <fstream>      // Conversion(ifstream* HexData)

#include "DmpFileManager.hh"
#include "DmpEvtManager.hh"

class TTree;

class DmpEvtPsdRaw;
class DmpEvtStkRaw;
class DmpEvtBgoRaw;
class DmpEvtNudRaw;

class DmpRdc : public DmpFileManager, public DmpEvtManager{
/*
 *  DmpRdc
 *
 *  SetConnectorSub-DetX() and ConversionSub-DetX()    could have many versions, for cosmic; whole; Beam test 2012..
 *  
 *
*/

//  ------------------------------------------------>
 public:
  static DmpRdc*    GetInstance();
  static void   Clear();
  Bool_t Core();
  void  SetHexData(ifstream *p)  {fHexData = p;}

 private:
  DmpRdc();
  ~DmpRdc();
  Bool_t    TriggerMatch();

 private:
  static DmpRdc     *fInstance;
  static TString    fConnectorPath;         // connection files of FEE to Detector
  ifstream  *fHexData;
  TTree     *fTree;
  std::map<TString,Short_t> fTrigger;

//  ------------------------------------------------>
 public:
  Bool_t    SetConnectorPsd();
  Bool_t    SetConnectorStk();
  Bool_t    SetConnectorBgo();
  Bool_t    SetConnectorBgo2012BT(){return true;}
  Bool_t    SetConnectorNud();

  Bool_t    ConversionHeader();
  Bool_t    ConversionPsd();
  Bool_t    ConversionStk();
  Bool_t    ConversionBgo();
  Bool_t    ConversionBgo2012BT(){return true;}
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

  ClassDef(DmpRdc,0)

};

#endif

