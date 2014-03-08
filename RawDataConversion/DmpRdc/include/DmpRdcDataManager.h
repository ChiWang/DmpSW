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
  static std::map<int,int>  sConnectorPsd;
  static std::map<int,int>  sConnectorStk;
  static std::map<int,int>  sConnectorBgo;     // FEE 2 Detector
    // ConnectorBgo[FEEID*1000+ChannelID][LBSD_ID]
    // LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  static std::map<int,int>  sConnectorNud;

public:
  bool OpenInputData(std::string);
  void BookBranch();
  void CreateOutDataName();
  bool Execute();

private:
  bool TriggerMatch();
  bool ConversionHeader();
  bool ConversionPsd();
  bool ConversionStk();
  bool ConversionBgo();
  bool ConversionNud();

private:
  DmpEventRaw   *fEvtRaw;
  std::string   fConnectorPath;     // connection files of FEE to Detector. Top path, include all directories of subDet
  std::string   fInDataName;        // input raw data from detector(format binary)
  ifstream      *fHexData;          // pointer of input data
  std::vector<short>    fTrigger;      // size = number of SubDet + 1
};

#endif

