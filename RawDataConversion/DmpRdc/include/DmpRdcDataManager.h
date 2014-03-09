/*
 *  $Id: DmpRdcDataManager.h, 2014-03-08 21:20:04 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <map>
#include <vector>
#include <fstream>      // ifstream*

#include "DmpVDataManager.h"

class DmpEventRaw;

class DmpRdcDataManager : public DmpVDataManager{
/*
 *  DmpRdcDataManager
 *
 *  SetConnectorSub-DetX() and ConversionSub-DetX()    could have many versions, for cosmic; whole; Beam test 2012..
 *  
 *
*/
public:
  static DmpRdcDataManager*     GetInstance();
  static void Vanish();
  static bool SetConnectorPsd();
  static bool SetConnectorStk();
  static bool SetConnectorBgo();
  static bool SetConnectorNud();

private:
  DmpRdcDataManager();
  ~DmpRdcDataManager();
  static DmpRdcDataManager  *sInstance;
  // Connector: FEE channel <----> Detector
  static std::map<int,int>  sConnectorPsd;
  static std::map<int,int>  sConnectorStk;
  static std::map<int,int>  sConnectorBgo;      // sConnectorBgo[FEEID*1000+ChannelID][LBSD_ID].    LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  static std::map<int,int>  sConnectorNud;

public:
  bool OpenInputData(std::string);
  void BookBranch();
  void CreateOutDataName();
  void Convert();

private:
  bool ConvertEventHeader();
  bool ConvertPsdEvent();
  bool ConvertStkEvent();
  bool ConvertBgoEvent();
  bool ConvertNudEvent();
  bool TriggerMatch();
  std::vector<short>    fTrigger;   // size = number of SubDet + 1

private:
  std::string   fConnectorPath;     // default is prefix/share/Connector
  std::string   fInDataName;        // raw data from detector(format binary)
  ifstream      *fInputData;        // pointer of input data
  DmpEventRaw   *fEvtRaw;

};

#endif

