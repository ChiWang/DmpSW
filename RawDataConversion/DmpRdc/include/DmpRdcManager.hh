/*=============================================================================
#       FileName :          DmpRdcManager.hh
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

#ifndef DmpRdcManager_H
#define DmpRdcManager_H

#include <map>
#include <fstream>      // Conversion(ifstream* HexData)

#include "DmpVManager.hh"

class DmpEvtHeaderRaw;
class DmpEvtPsdRaw;
class DmpEvtStkRaw;
class DmpEvtBgoRaw;
class DmpEvtNudRaw;

class DmpRdcManager : public DmpVManager{

//  ---------------->   manager general
 public:
  static DmpRdcManager*  GetInstance();     // get Manager
  void Clear();                             // delete Manager
  Bool_t BookBranch();

 private:
  DmpRdcManager();
  ~DmpRdcManager();

 private:
  static DmpRdcManager      *fInstance;
  std::map<TString,Short_t> fTrigger;

//  ---------------->   manager special
 public:
  Bool_t    SetConnector(TString subDet);           // set FEE <-> detector connector. Default for whole dampe. subDet = {Psd | Stk | Bgo | Nud}
  Bool_t    Conversion(ifstream *HexData,TString subDet);
  template <typename TDmpEvt>
  TDmpEvt*  GetEventPointer(TString subDet);
  void      FillAnEvent();           // fill current event
  void      SaveRootFile();          // save all TTree of sub-detectors into fOutRootFile

 private:
  Bool_t    TriggerCheck();

 private:
  TString   fConnectorPath;         // connection files of FEE to Detector

//  ---------------->   sub-detector
  // Header
 private:
  Bool_t    ConversionHeader(ifstream *HexData);

  DmpEvtHeaderRaw   *fEvtHeader;

  // Psd
 private:
  void ConstructorPsd();
  void DestructorPsd();
  Bool_t    SetConnectorPsd();
  Bool_t    ConversionPsd(ifstream *HexData);

  DmpEvtPsdRaw      *fEvtPsd;
  std::map<Int_t, Short_t*>  ConnectorPsd;

  // Stk
 private:
  void ConstructorStk();
  void DestructorStk();
  Bool_t    SetConnectorStk();
  Bool_t    ConversionStk(ifstream *HexData);

  DmpEvtStkRaw      *fEvtStk;
  std::map<Int_t, Short_t*>  ConnectorStk;

  // Bgo
 private:
  void ConstructorBgo();
  void DestructorBgo();
  Bool_t    SetConnectorBgo();
  Bool_t    ConversionBgo(ifstream *HexData);

  DmpEvtBgoRaw      *fEvtBgo;
  std::map<Int_t, Short_t*>  ConnectorBgo;     //! FEE 2 Detector       
    //Connector[FEEID*1000+ChannelID][0]    Layer ID                 
    //Connector[FEEID*1000+ChannelID][2]    Quadrant ID                  
    //Connector[FEEID*1000+ChannelID][1]    Bar ID                   
    //Connector[FEEID*1000+ChannelID][3]    Dy ID 

  // Nud
 private:
  void ConstructorNud();
  void DestructorNud();
  Bool_t    SetConnectorNud();
  Bool_t    ConversionNud(ifstream *HexData);

  DmpEvtNudRaw      *fEvtNud;
  std::map<Int_t, Short_t*>  ConnectorNud;

};

#endif


